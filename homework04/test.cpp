#include "bst_map.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    BSTMap<int, string> myMap;
    myMap.get_or_insert(11) = "no";
    myMap.get_or_insert(10) = "a";
    myMap.get_or_insert(12) = "b";
    myMap.get_or_insert(11) = "c";
    myMap.get_or_insert(15) = "11";
    myMap.print();

    // random string tests.
    // string myString = "hi";
    // myString.append(" there cutie!");
    // cout << myString << endl;
}