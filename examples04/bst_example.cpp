#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
using namespace std;

template <typename K, typename V>
class BST {
   private:
    struct Node {
        K _key;
        V _val;
        Node *_left, *_right;
        Node(K key, V val) : _key(key), _val(val), _left(nullptr), _right(nullptr){};
        Node(const Node &other) : _key(other._key), _val(other._val), _left(nullptr), _right(nullptr) {
            if (other._left != nullptr) _left = new Node(*other._left);
            if (other._right != nullptr) _right = new Node(*other._right);
        }
        ~Node() {
            delete _left;
            delete _right;
        }
        friend ostream &operator<<(ostream &os, Node &n) {
            if (n._left != nullptr)
                os << *n._left;
            os << n._key << ": " << n._val << endl;
            if (n._right != nullptr)
                os << *n._right;
            return os;
        }
    };
    Node *_root;
    V _default_val;

    V &get_or_insert(K key, Node *&cur) {
        if (cur == nullptr) {
            cur = new Node(key, _default_val);
            return cur->_val;
        }
        if (cur->_key == key)
            return cur->_val;
        if (key < cur->_key)
            return get_or_insert(key, cur->_left);
        return get_or_insert(key, cur->_right);
    }

   public:
    BST(V default_val) : _root(nullptr), _default_val(default_val){};
    BST(const BST &other) : _root(nullptr) {
        if (other._root != nullptr) _root = new Node(*other._root);
    }
    V &get_or_insert(K key) {
        return get_or_insert(key, _root);
    }
    ~BST() {
        delete _root;
    }

    friend ostream &operator<<(ostream &os, BST &bst) {
        if (bst._root != nullptr)
            return os << "{\n"
                      << *bst._root << "}";
        return os << "{}";
    }
};

int main() {
    // BST<string, int> mymap(0);
    // ifstream inp("./macbeth.txt");
    // string word;
    // while (inp >> word)
    //     mymap.get_or_insert(word)++;

    // cout << mymap.get_or_insert("the") << endl;
    // return 0;

    BST<int, int> myMap(0);
    for (int i = 0; i < 1000; i++) {
        myMap.get_or_insert(rand() % 100)++;
    }
    cout << myMap << endl;

    BST<int, int> myOtherMap(myMap);
    cout << myOtherMap << endl;
}