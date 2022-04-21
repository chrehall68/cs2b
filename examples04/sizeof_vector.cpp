#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> myv = {1, 2, 3, 4};

    // get the size of the vector
    // (includes sizeof vector's internals and sizeof the allocated memory)
    cout << sizeof(myv) + sizeof(int) * myv.capacity() << endl;
}