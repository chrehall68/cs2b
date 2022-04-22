#ifndef _BST_MAP_
#define _BST_MAP_

#include <iostream>

using std::cout;
using std::endl;

template <typename Key, typename Value>
class BSTMap
{
private:
    // You may add functionality to the Node class if you want to, but you must
    // not remove any functionality or change any variable/method names!
    // Ask if you'd like to make a change and you're not sure if it is safe.
    struct Node
    {
        Key key;
        Value value;
        Node *left, *right;

        Node(Key key)
            : key(key), left(nullptr), right(nullptr) {}

        // try to not get any of the indirect leak warnings
        ~Node()
        {
            delete left;
            delete right;
        }
    };

    // This private root attribute is how you must store the root of your BST.
    Node *root;

    // prints nodes recursively in order of least to greatest
    void print(Node *cur) const
    {
        if (cur != nullptr)
        {
            print(cur->left);
            cout << cur->key << ": " << cur->value << endl;
            print(cur->right);
        }
    }

    // recursive solution
    Value &get_or_insert(const Key &key, Node *&cur)
    {
        if (cur == nullptr)
        {
            // create the new node and return its value
            cur = new Node(key);
            return cur->value;
        }

        // if we already are at destination
        if (cur->key == key)
            return cur->value;

        // if key is less, repeat on node to the left
        if (key < cur->key)
            return get_or_insert(key, cur->left);

        // if key is greater, repeat on node to the right
        return get_or_insert(key, cur->right);
    }

public:
    BSTMap() : root(nullptr) {}

    Value &get_or_insert(const Key &key)
    {
        return get_or_insert(key, root);
    }

    // You may change this method if you want.
    void print() const
    {
        print(root);
    }

    ~BSTMap() { delete root; }
};

#endif // _BST_MAP_