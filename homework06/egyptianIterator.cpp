#include <iostream>
using namespace std;

// fraction class for doing fractions
class Fraction {
   private:
    unsigned long long numerator;
    unsigned long long denominator;

   public:
    Fraction(unsigned long long numerator, unsigned long long denominator) : numerator(numerator), denominator(denominator) { simplify(); };
    Fraction(int o) : numerator(o), denominator(1){};
    Fraction() : numerator(0), denominator(1){};

    void simplify() {
        for (unsigned long long i = min(denominator, numerator); i >= 2; i--) {
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
    unsigned long long getNumerator() {
        return numerator;
    }
    unsigned long long getDenominator() {
        return denominator;
    }

    friend ostream& operator<<(ostream& os, const Fraction f) {
        return os << f.numerator << "/" << f.denominator;
    }

    // may lose precision!!
    operator unsigned long long() {
        return numerator / denominator;
    }
};

class EgyptianFractions {
   private:
    int max;
};

// http://oeis.org/A002966
// 1, 1, 3, 4
unsigned long long find_number_of_solutions(int n, Fraction remainder = 1, Fraction mn = 1) {
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

int main() {
    cout << find_number_of_solutions(6) << endl;
}