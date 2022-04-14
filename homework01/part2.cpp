#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char *argv[])
{
    if (argc < 3)
    {
        cout << "too few arguments" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in)
    {
        cout << "unable to open \"" << string(argv[1]) << "\"" << endl;
        return -2;
    }
    ofstream out(argv[2]);
    if (!out)
    {
        cout << "unable to open\"" << string(argv[2]) << "\"" << endl;
        return -3;
    }
    return 0;
}