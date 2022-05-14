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

    template <typename K, typename V>
    static void assert_equals(K desired, V given, string where = "main") {
        if (desired != given) {
            ostringstream temp;
            temp << "Error in " << where << ": " << desired << " is not equal to " << given;
            throw AssertionError(temp.str().c_str());
        }
    }

   public:
    static void test_foreach(EgyptianFractions& iterable, int terms) {
        int n = 0;
        for (int i : iterable) {
            // just make sure that we can do this loop
            n++;
        }
        assert_equals(terms, n);
    }
    static void test_iterator(EgyptianFractions& iterable, int terms) {
        int n = 0;
        for (auto it = iterable.begin(); it != iterable.end(); ++it) {
            n++;
        }
        assert_equals(terms, n);
    }

    // 1, 1, 3, 14, 147, 3462
    // pass a copy since we will be changing the copy
    static void test_vals(EgyptianFractions iterable) {
        iterable.set_num_terms(6);
        vector<int> solutions = {1, 1, 3, 14, 147, 3462};
        int idx = 0;
        for (int i : iterable) {
            assert_equals(solutions[idx], i);
            idx++;
        }
    }
};
int main() {
    EgyptianFractions myFract(2);
    UnitTests::test_foreach(myFract, myFract.get_num_terms());
    UnitTests::test_iterator(myFract, myFract.get_num_terms());
    UnitTests::test_vals(myFract);
    cout << "all tests passed" << endl;
}