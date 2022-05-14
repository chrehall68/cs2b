#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string operator*(string a, size_t times) {
    string ret;
    for (int i = 0; i < times; i++) {
        ret += a;
    }
    return ret;
}

template <typename K, typename V>
class AVL {
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

        // printing util
        friend ostream &operator<<(ostream &os, const Node &n) {
            if (n._left != nullptr)
                os << *n._left;
            os << n._key << ": " << n._val << endl;
            if (n._right != nullptr)
                os << *n._right;
            return os;
        }
        // this only returns the key:value pair
        string to_string() const {
            ostringstream ret;
            ret << _key << ": " << _val;
            return ret.str();
        }

        // height of 1 is the current generation
        int height() const {
            if (_left == nullptr && _right == nullptr) {
                return 1;
            }
            if (_left != nullptr && _right != nullptr) {
                return 1 + max(_left->height(), _right->height());
            }
            if (_left != nullptr) return 1 + _left->height();
            return 1 + _right->height();
        }
        int balance() const {
            int left_h = 0;
            if (_left != nullptr) {
                left_h = _left->height();
            }
            int right_h = 0;
            if (_right != nullptr) {
                right_h = _right->height();
            }
            return right_h - left_h;
        }

        // generation 1 is the current generation
        vector<Node *> get_nth_gen(int n, vector<Node *> &v) {
            if (n == 1) {
                v.push_back(this);
            } else {
                if (_left != nullptr)
                    _left->get_nth_gen(n - 1, v);
                else {
                    for (int i = 0; i < (1 << (n - 2)); i++) v.push_back(nullptr);
                }
                if (_right != nullptr)
                    _right->get_nth_gen(n - 1, v);
                else {
                    for (int i = 0; i < (1 << (n - 2)); i++) v.push_back(nullptr);
                }
            }
            return v;
        }
        // generation 1 is the current generation
        vector<Node *> get_nth_gen(int n) {
            vector<Node *> ret;
            return get_nth_gen(n, ret);
        }
    };

    class KeyNotFoundException : public logic_error {
       public:
        KeyNotFoundException(const char *what) : logic_error(what){};
    };

    Node *_root;
    V _default_val;

    Node *left_rotate(Node *cur) {
        Node *ret = cur->_right;
        Node *orphaned_tree = cur->_right->_left;
        ret->_left = cur;
        cur->_right = orphaned_tree;
        return ret;
    }
    Node *right_rotate(Node *cur) {
        Node *ret = cur->_left;
        Node *orphaned_tree = cur->_left->_right;
        ret->_right = cur;
        cur->_left = orphaned_tree;
        return ret;
    }

    Node *set_or_insert(K key, V value, Node *&cur) {
        if (cur == nullptr) {
            cur = new Node(key, value);
            return cur;
        }

        if (cur->_key == key) {
            cur->_val = value;
            return cur;
        } else if (key < cur->_key) {
            set_or_insert(key, value, cur->_left);
        } else {
            set_or_insert(key, value, cur->_right);
        }

        int balance = cur->balance();
        if (abs(balance) > 1) {
            // left cases
            if (balance > 1) {
                int child_balance = cur->_right->balance();

                // left left case
                if (child_balance > 0) {
                    cur = left_rotate(cur);
                }

                // right left case
                if (child_balance < 0) {
                    cur->_right = right_rotate(cur->_right);
                    cur = left_rotate(cur);
                }
            }

            // right cases
            if (balance < 1) {
                int child_balance = cur->_left->balance();

                // right right case
                if (child_balance < 0) {
                    cur = right_rotate(cur);
                }

                // left right case
                if (child_balance > 0) {
                    cur->_left = left_rotate(cur->_left);
                    cur = right_rotate(cur);
                }
            }
        }

        return cur;
    }

    V &get(K key, Node *cur) {
        if (cur == nullptr) {
            throw KeyNotFoundException("No matching key found!!");
        }
        if (cur->_key == key)
            return cur->_val;
        if (key < cur->_key)
            return get(key, cur->_left);
        return get(key, cur->_right);
    }
    Node *set_or_insert(K key) {
        return set_or_insert(key, _default_val, _root);
    }

   public:
    AVL() : _root(nullptr) { _default_val = K(); };
    AVL(V default_val) : _root(nullptr), _default_val(default_val){};
    AVL(const AVL &other) : _root(nullptr) {
        if (other._root != nullptr) _root = new Node(*other._root);
    }
    ~AVL() {
        delete _root;
    }

    // will throw errors if key not found
    V operator[](K key) const {
        return get(key, _root);
    }

    // guaranteed to not throw errors
    V &operator[](K key) {
        return set_or_insert(key)->_val;
    }

    // printing util
    friend ostream &operator<<(ostream &os, AVL &AVL) {
        if (AVL._root != nullptr)
            return os << "{\n"
                      << *AVL._root << "}";
        return os << "{}";
    }
    void print_structure() {
        if (_root == nullptr) {
            cout << "{}" << endl;
            return;
        }
        int spacing = 6;
        int width = spacing * (1 << _root->height());

        cout << string("-") * width << endl;
        for (int i = 1; i <= _root->height(); i++) {
            // calculate margin between
            int margin_between = (width - spacing * (1 << (i - 1))) / ((1 << (i - 1)) + 1);
            string spacer = string(" ") * margin_between;

            // print the layer
            for (Node *n : _root->get_nth_gen(i)) {
                cout << spacer;
                if (n == nullptr)
                    cout << setw(spacing) << "null";
                else
                    cout << setw(spacing) << n->to_string();
            }
            cout << "\n\n";
        }
        cout << string("-") * width << endl;
    }
};

int main() {
    AVL<int, int> leftRightRotateTest(0);
    leftRightRotateTest[13] = 0;
    leftRightRotateTest[10] = 0;
    leftRightRotateTest[15] = 0;
    leftRightRotateTest[16] = 0;
    leftRightRotateTest[5] = 0;
    leftRightRotateTest[11] = 0;
    leftRightRotateTest[4] = 0;
    leftRightRotateTest[6] = 0;
    leftRightRotateTest.print_structure();

    leftRightRotateTest[7] = 0;
    leftRightRotateTest.print_structure();

    AVL<int, int> rightLeftRotateTest(0);
    rightLeftRotateTest[20] = 0;
    rightLeftRotateTest[25] = 0;
    rightLeftRotateTest[15] = 0;
    rightLeftRotateTest[13] = 0;
    rightLeftRotateTest[30] = 0;
    rightLeftRotateTest[22] = 0;
    rightLeftRotateTest[27] = 0;
    rightLeftRotateTest[31] = 0;
    rightLeftRotateTest.print_structure();
    rightLeftRotateTest[28] = 0;
    rightLeftRotateTest.print_structure();
    cout << rightLeftRotateTest[13] << endl;
    rightLeftRotateTest[13] = 22;
    cout << rightLeftRotateTest[13] << endl;
}