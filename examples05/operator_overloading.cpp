#include <iostream>

using namespace std;

class Cool {
   private:
    int test;

   public:
    Cool(int a) : test(a){};

    Cool(const Cool& o) : test(o.test){};

    // do something to allow casting
};

int main()
{
    cout << "hello world" << endl;
    Cool c(22);
    cout << (int)c << endl;
}