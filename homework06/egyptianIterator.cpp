#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// fraction class for doing fractions
class Fraction {
   private:
    int numerator;
    int denominator;

   public:
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) { simplify(); };
    Fraction(int o) : numerator(o), denominator(1){};
    Fraction() : numerator(0), denominator(1){};

    void simplify() {
        for (int i = min(denominator, numerator); i >= 2; i--) {
            if (numerator % i == 0 && denominator % i == 0) {
                numerator /= i;
                denominator /= i;
            }
        }
    }

    // comparison operators
    // unneeded here but still cool
    bool operator==(const Fraction& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }
    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }
    bool operator>(const Fraction& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }
    bool operator<=(const Fraction& other) const {
        return numerator * other.denominator <= other.numerator * denominator;
    }

    // arithmetic operators
    Fraction& operator+=(const Fraction& other) {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }
    Fraction operator/(const Fraction& other) const {
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }
    friend Fraction operator/(int o, const Fraction f) {
        return Fraction(o * f.denominator, f.numerator);
    }
    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
    }

    // getters
    int getNumerator() {
        return numerator;
    }
    int getDenominator() {
        return denominator;
    }

    friend ostream& operator<<(ostream& os, const Fraction f) {
        return os << f.numerator << "/" << f.denominator;
    }

    // may lose precision!!
    operator int() {
        return numerator / denominator;
    }
};

class EgyptianFractions {
   private:
    int num_terms;

   public:
    static int find_number_of_solutions(int n, Fraction remainder = 1, Fraction mn = 1) {
        // 1/x_1 + 1/x_2 + 1/x_n
        // x_1 <= x_2 <= ... <= x_n

        // oeis.org :
        // All denominators in the expansion 1 = 1/x_1 + ... + 1/x_n
        // are bounded by A000058(n-1), i.e., 0 < x_1 <= ... <= x_n < A000058(n-1).
        // Furthermore, for a fixed n, x_i <= (n+1-i)*(A000058(i-1)-1).
        // - Max Alekseyev, Oct 11 2012
        // (PARI) a(n, rem=1, mn=1)=if(n==1, return(numerator(rem)==1)); sum(k=max(1\rem+1, mn), n\rem, a(n-1, rem-1/k, k))

        if (n == 1) {
            return static_cast<int>(remainder.getNumerator() == 1);
        }

        Fraction sum = 0;
        for (int k = max(static_cast<int>(1 / remainder) + 1, static_cast<int>(mn)); k <= n / remainder; k += 1) {
            sum += find_number_of_solutions(n - 1, remainder - Fraction(1, k), k);
        }

        return sum;
    }
    class EgyptianIterator {
       private:
        int term;

       public:
        EgyptianIterator(int term) : term(term){};
        int operator*() {
            return EgyptianFractions::find_number_of_solutions(term);
        }
        EgyptianIterator& operator++() {
            ++term;
            return *this;
        }
        bool operator!=(const EgyptianIterator& o) {
            return term != o.term;
        }
    };

    EgyptianFractions(int num_terms) : num_terms(num_terms){};
    EgyptianIterator begin() {
        return EgyptianIterator(1);
    }
    EgyptianIterator end() {
        return EgyptianIterator(num_terms + 1);
    }

    int get_num_terms() {
        return num_terms;
    }
    void set_num_terms(int new_terms) {
        num_terms = new_terms;
    }
};

// http://oeis.org/A002966
// 1, 1, 3, 14, 147, 3462

class UnitTests {
   private:
    class AssertionError : public logic_error {
       public:
        AssertionError(const char* what) : logic_error(what){};
    };

    template <typename T, typename V>
    static void assert_equals(T desired, V given, string where = "main") {
        if (desired != given) {
            ostringstream temp;
            temp << "Error in " << where << ": " << desired << " is not equal to " << given;
            throw AssertionError(temp.str().c_str());
        }
    }
    template <typename T, typename V>
    static void assert_notequals(T not_desired, V given, string where = "main") {
        if (not_desired == given) {
            ostringstream temp;
            temp << "Error in " << where << ": " << not_desired << " is equal to " << given << " (it shouldn't be)";
            throw AssertionError(temp.str().c_str());
        }
    }

   public:
    // pass a copy since we will be modifying the copy
    // do not use 0 as an argument for terms since we are testing to make sure that
    // the iterable provides actual values
    static void test_foreach(EgyptianFractions iterable, int terms = 5) {
        assert_notequals(terms, 0);

        iterable.set_num_terms(terms);
        int n = 0;
        ostringstream temp;

        // if begin() and end() aren't defined, this test will fail
        for (int i : iterable) {
            temp << i;
            n++;
        }

        assert_equals(terms, n);  // make sure that it has `terms` number of terms
        assert_notequals(string(""), temp.str());
    }

    // pass a copy since we will be modifying the copy
    // do not use 0 as an argument for terms since we are testing to make sure that
    // the iterable provides actual values
    static void test_iterator_and_dereference(EgyptianFractions iterable, int terms = 5) {
        assert_notequals(terms, 0);

        iterable.set_num_terms(terms);
        int n = 0;
        ostringstream temp;

        // if this iterator isn't defined, then this will error and test will not pass.
        for (auto it = iterable.begin(); it != iterable.end(); ++it) {
            temp << *it << "\n";  // make sure that can dereference
            n++;
        }

        assert_equals(terms, n);  // make sure that it has `terms` number of terms
        assert_notequals(string(""), temp.str());
    }

    // pass a copy since we will be modifying the copy
    static void test_forloops_equal(EgyptianFractions iterable) {
        iterable.set_num_terms(5);
        ostringstream for_each;
        ostringstream iterator_and_dereference;

        for (auto it = iterable.begin(); it != iterable.end(); ++it) {
            iterator_and_dereference << *it << "\n";
        }
        for (int i : iterable) {
            for_each << i << "\n";
        }

        assert_equals(for_each.str(), iterator_and_dereference.str());
    }

    // 1, 1, 3, 14, 147, 3462 <- first 6 terms (note that it's really time consuming to get anything above the 6th term)
    // pass a copy since we will be modifying the copy
    static void test_vals(EgyptianFractions iterable) {
        iterable.set_num_terms(6);
        vector<int> solutions = {1, 1, 3, 14, 147, 3462};
        int idx = 0;
        for (int i : iterable) {
            assert_equals(solutions[idx], i);
            idx++;
        }
    }

    // pass a copy since we will be modifying the copy
    static void test_get_and_set(EgyptianFractions iterable) {
        for (int i = 0; i < 7; ++i) {
            iterable.set_num_terms(i);
            assert_equals(i, iterable.get_num_terms());
        }
    }
};

int main() {
    EgyptianFractions myFract(2);
    UnitTests::test_get_and_set(myFract);
    UnitTests::test_foreach(myFract);
    UnitTests::test_iterator_and_dereference(myFract);
    UnitTests::test_vals(myFract);
    cout << "all tests passed" << endl;
}