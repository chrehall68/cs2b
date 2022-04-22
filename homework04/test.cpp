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

    cout << sizeof(BSTMap<int, int>::Node) << endl;

    myMap = BSTMap<int, string>();
    myMap.get_or_insert(11) = "new stuff";
    myMap.get_or_insert(13) = "cool";
    myMap.print();

    // random string tests.
    // string myString = "hi";
    // myString.append(" there cutie!");
    // cout << myString << endl;
    // to add just 1 char to end, use myString.push_back(char)  // it's faster.
}