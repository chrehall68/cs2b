#include <math.h>

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

using std::int64_t;
ofstream out("./a.txt");

// fraction class for doing fractions
class Fraction {
   private:
    int64_t numerator;
    int64_t denominator;

   public:
    Fraction(int64_t numerator, int64_t denominator) : numerator(numerator), denominator(denominator){};
    void simplify() {
        for (int64_t i = min(denominator, numerator); i >= 2; i--) {
            if (numerator % i == 0 && denominator & i == 0) {
                numerator /= i;
                denominator /= i;
            }
        }
    }
    bool operator==(const Fraction& other) const {
        return numerator * other.denominator == other.numerator * denominator;
    }
    Fraction& operator+=(const Fraction& other) {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }
    Fraction operator+(const Fraction& other) const {
        Fraction ret(*this);
        ret += other;
        return ret;
    }
    friend ostream& operator<<(ostream& os, const Fraction f) {
        return os << f.numerator << "/" << f.denominator;
    }
};

// for easy debugging and printing of vectors
template <typename T>
ostream& operator<<(ostream& os, vector<T> i) {
    os << "{";
    for (T x : i) {
        os << x << ", ";
    }
    os << "}";
    return os;
}

map<int, int64_t> cache{{0, 2}};
int64_t sylvester_seq(int n) {
    if (cache.find(n) != cache.end()) return cache[n];
    return sylvester_seq(n - 1) * sylvester_seq(n - 1) - sylvester_seq(n - 1) + 1;
}

// 1, 1, 3, 14
int find_number_of_solutions(int n) {
    if (n <= 2) return 1;

    // 1/x_1 + 1/x_2 + 1/x_n
    // x_1 <= x_2 <= ... <= x_n

    // oeis.org :
    // All denominators in the expansion 1 = 1/x_1 + ... + 1/x_n
    // are bounded by A000058(n-1), i.e., 0 < x_1 <= ... <= x_n < A000058(n-1).
    // Furthermore, for a fixed n, x_i <= (n+1-i)*(A000058(i-1)-1).
    // - Max Alekseyev, Oct 11 2012

    vector<int64_t> digits;
    Fraction one(1, 1);
    int count = 0;

    int64_t base = sylvester_seq(n - 1);
    for (int64_t i = 0; i < static_cast<int64_t>(pow(base, n)); i++) {
        bool ascending = true;
        for (int64_t dig = i, x = 0; x < n; x++, dig /= (base)) {
            int64_t temp = dig % base + 1;
            if (digits.size() == 0 || temp <= digits[0]) {
                digits.emplace(digits.begin(), temp);
            } else {
                ascending = false;
                break;
            }
        }
        if (!ascending) {
            digits.clear();
            continue;
        }

        out << digits << endl;

        Fraction total(0, 1);
        for (int64_t f : digits) {
            total += Fraction(1, f);
        }
        if (total == one) {
            count++;
            out << "yes ^" << endl;
        }

        digits.clear();
    }
    return count;
}

// http://oeis.org/A002966
int main() {
    out << sylvester_seq(4) << endl;
    // out << find_number_of_solutions(4) << endl;
}