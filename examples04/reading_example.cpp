#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    // how to read words in c++ (looks for next whitespace)
    ifstream a("test.txt");
    string word;
    while (a >> word)
    {
        cout << word << endl;
    }
    return 0;
}