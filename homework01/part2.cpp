#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <map>
using namespace std;

int SENTINEL = -1;

int hex_to_int(string l)
{
    if (l[l.size() - 1] == ' ')
        return SENTINEL; // completely empty string
    int ret = 0;
    for (int i = l.size() - 1; i > -1; i--)
    {
        if (l[i] != ' ')
        {
            if (l[i] - '0' <= 9 && l[i] - '0' >= 0)
                ret += static_cast<int>(pow(16, (l.size() - 1 - i))) * (l[i] - '0');
            else
                ret += static_cast<int>(pow(16, (l.size() - 1 - i))) * (l[i] - 'a' + 10);
        }
    }
    return ret;
}
int printable_to_int(string l)
{
    if (l[l.size() - 1] == ' ')
        return SENTINEL; // completely empty string
    if (l.find("' '") != string::npos)
        return static_cast<int>(' ');
    if (l.find("\\t") != string::npos)
        return static_cast<int>('\t');
    if (l.find("\\n") != string::npos)
        return static_cast<int>('\n');
    if (l.find("\\0") != string::npos)
        return static_cast<int>('\0');
    if (l.find("\\x") != string::npos)
        return hex_to_int(l.substr(l.find("\\x") + 2, 2));

    return static_cast<int>(l[l.size() - 1]);
}

int binary_to_int(string l)
{
    if (l[l.size() - 1] == ' ')
        return SENTINEL; // completely empty string
    int ret = 0;
    for (int i = l.size() - 1; i > -1; i--)
        if (l[i] == '1')
            ret += static_cast<int>(pow(2, l.size() - 1 - i));
    return ret;
}
int dec_to_int(string l)
{
    if (l[l.size() - 1] == ' ')
        return SENTINEL; // completely empty string
    stringstream converter(l);
    int ret;
    converter >> ret;
    return ret;
}

int get_unique(int a, int b, int c, int d)
{
    int total = 0;
    map<int, int> m;
    int items[] = {a, b, c, d};
    for (int i = 0; i < sizeof(items) / sizeof(items[0]); i++)
    {
        if (m.find(items[i]) != m.end())
            m[items[i]]++;
        else
            m.insert(std::make_pair(items[i], 1));
    }
    for (map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++) // iterate over the map
    {
        if (iter->second == 1)
        {
            // if the occurences == 1
            return iter->first;
        }
    }

    // this should only happen if each number appears more than once (ie a=b, c=d).
    // In that case, we already violate precondition, but in order to return something we return this
    return a;
}

void write_a_line(string line, ofstream &o)
{
    // if it's not one of the header lines
    if (line.find("Printable") == string::npos && line.find("|--------------") == string::npos)
    {
        int offsets[] = {1, 1, 1, 1};
        int to_read[] = {5, 3, 9, 4};
        size_t indexes[] = {0, 22, 36, 74}; // idx's of the '|' that mark the transitions between columns
        int vals[] = {-1, -1, -1, -1};
        for (int i = 0; i < 4; i++)
        {
            vals[0] = printable_to_int(line.substr(indexes[0] + offsets[0], to_read[0]));
            vals[1] = hex_to_int(line.substr(indexes[1] + offsets[1], to_read[1]));
            vals[2] = binary_to_int(line.substr(indexes[2] + offsets[2], to_read[2]));
            vals[3] = dec_to_int(line.substr(indexes[3] + offsets[3], to_read[3]));

            for (int x = 0; x < 4; x++)
                offsets[x] += to_read[x];

            int temp = get_unique(vals[0], vals[1], vals[2], vals[3]);
            if (temp != SENTINEL)
                o.write(reinterpret_cast<char *>(&temp), 1);
        }
    }
}

int main(int argc, const char *argv[])
{
    if (argc < 3)
    {
        cout << "Usage ./hex_table_to_bytes input_file output_file" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if (!in)
    {
        cout << "unable to open \"" << string(argv[1]) << "\"" << endl;
        return -2;
    }
    ofstream out(argv[2], ofstream::binary);
    if (!out)
    {
        cout << "unable to open\"" << string(argv[2]) << "\"" << endl;
        return -3;
    }

    // read in file to memory (buffer)
    in.seekg(0, in.end);
    int byte_length = in.tellg();
    char buffer[byte_length];
    in.seekg(in.beg);
    in.read(buffer, byte_length);
    in.close();

    // process the buffer
    string temp;
    for (int i = 0; i < byte_length; i++)
    {
        if (buffer[i] != '\n')
            temp += buffer[i];
        else
        {
            write_a_line(temp, out);
            temp = "";
        }
    }
    out.close();

    return 0;
}