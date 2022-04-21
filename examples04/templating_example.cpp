#include <iostream>
#include <string>
#include <limits>
using namespace std;

template <typename T>
struct myMax
{
    static constexpr T max = numeric_limits<T>::max();
};

// specialized template
// applies to only one type
template <>
struct myMax<unsigned char>
{
    static constexpr unsigned char max = 1; // just as a test
};

int main()
{
    cout << myMax<double>::max << endl;
    cout << myMax<int>::max << endl;
    cout << static_cast<int>(myMax<unsigned char>::max) << endl;
}
