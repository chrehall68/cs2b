#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;

template <typename K, typename V>
class BST
{
private:
    struct Node
    {
        K _key;
        V _val;
        Node *_left, *_right;
        Node(K key, V val) : _key(key), _val(val), _left(nullptr), _right(nullptr){};
        ~Node()
        {
            delete _left;
            delete _right;
        }
    };
    Node *_root;
    V _default_val;

    V &get_or_insert(K key, Node *&cur)
    {
        if (cur == nullptr)
        {
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
    V &get_or_insert(K key)
    {
        return get_or_insert(key, _root);
    }
    ~BST()
    {
        delete _root;
    }
};

int main()
{
    BST<string, int> mymap(0);
    ifstream inp("./macbeth.txt");
    string word;
    while (inp >> word)
        mymap.get_or_insert(word)++;

    cout << mymap.get_or_insert("the") << endl;
    return 0;
}