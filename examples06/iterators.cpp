#include <iostream>
#include <vector>
using namespace std;

class Iterable {
    vector<int> myStuff;

   public:
    class Iterator {
        vector<int>& stuff;
        int index;

       public:
        Iterator(vector<int>& stuff, int index) : stuff(stuff), index(index){};
        bool operator!=(const Iterator& o) {
            return stuff != o.stuff || index != o.index;
        }
        int operator*() {
            return stuff[index];
        }
        Iterator& operator++() {
            ++index;
            return *this;
        }
    };

    Iterable() : myStuff({1, 2, 3, 4, 66, 77, 88, 99}){};
    Iterator begin() {
        return Iterator(myStuff, 0);
    }
    Iterator end() {
        return Iterator(myStuff, myStuff.size());
    }
};

int main() {
    Iterable myIter;
    for (auto it = myIter.begin(); it != myIter.end(); ++it) {
        cout << *it << endl;
    }
    cout << endl;
    for (int i : myIter) {
        cout << i << endl;
    }
}