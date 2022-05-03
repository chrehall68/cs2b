#include <iostream>

using namespace std;

class Cool
{
private:
    int test;

public:
    Cool(int a) : test(a){};

    Cool(const Cool &o) : test(o.test){};

    // allow casting to an int
    operator int() { return test; }
};

int main()
{
    cout << "hello world" << endl;
    Cool c(22);
    cout << static_cast<int>(c) << endl;
}