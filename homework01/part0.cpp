#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

char get_unique_char(char a, char b, char c, char d)
{
    int total = 0;
    map<char, int> m;
    char items[] = {a, b, c, d};
    for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++)
    {
        if (m.find(items[i]) != m.end())
            m[items[i]]++;
        else
            m.insert(std::make_pair(items[i], 1));
    }
    for (map<char, int>::iterator iter = m.begin(); iter != m.end(); iter++) // iterate over the map
    {
        if (iter->second > 1)
        {
            // if the occurences > 1
            return iter->first;
        }
    }

    // this should only happen if a, b, c, and d are all distinct.
    // In that case, we already violate precondition, but in order to return something we return this
    return a;
}
int main(int argc, const char *argv[])
{
    // write all 256 bytes

    // cout << argc << endl;
    // ofstream bin_out;
    // if (argc > 1)
    //     bin_out = ofstream(argv[1], ofstream::binary);
    // else
    // {
    //     cerr << "NO OUTPUT FILE!!!" << endl;
    //     return -1;
    // }
    // cout << "trying write" << endl;
    // cout << "size of short int is" << sizeof(int) << endl;
    // for (int i = 0; i < 256; i++)
    // {
    //     bin_out.write(reinterpret_cast<const char *>(&i), sizeof(char));
    // }
    // bin_out.close();

    // get the unique character
    // cout << get_unique_char('x', 'a', 'a', 'a') << endl;

    ifstream bin_in;
    if (argc > 1)
        bin_in = ifstream(argv[1], ifstream::binary);
    else
        throw("NO OUTPUT FILE!!!");

    bin_in.seekg(0, ifstream::end);
    cout << "it has " << bin_in.tellg() << "bytes" << endl;
    bin_in.seekg(0, ifstream::beg);

    char a;
    while (bin_in.get(a))
    {
        cout << static_cast<int>(static_cast<unsigned char>(a)) << endl;
    }

    bin_in.close();
}
