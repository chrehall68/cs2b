#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

string to_hexadecimal(int n)
{
    string ret = "";
    // hex is base 16
    int temp = n % 16;

    // take care of last digit
    if (temp >= 0 && temp <= 9)
        ret += to_string(temp);
    else
        ret += static_cast<char>(temp + 87); // 'a' is 97, so 10+87 == 'a'

    if (n / 16 != 0)
        return to_hexadecimal(n / 16) + ret; // ret goes at end since is last digit
    return ret;
}
string to_2digit_hexadecimal(int n)
{
    string ret = to_hexadecimal(n);
    if (ret.size() < 2)
        ret = "0" + ret;
    return ret;
}

string to_binary(int n)
{
    string ret = "";
    ret += to_string(n % 2); // binary is base 2
    return (n / 2 != 0 ? to_binary(n / 2) + ret : ret);
}
// adds 0s in front so that returned string will be 8 digits
// (or more if you input a large enough number)
string to_8b_binary(int n)
{
    string ret = to_binary(n);
    for (int i = ret.size(); i < 8; i++)
        ret = "0" + ret;
    return ret;
}

string get_printable(unsigned char a)
{
    int temp = static_cast<int>(a);
    ostringstream o;
    o << setw(5);
    if (temp == 10)
    {
        o << "\\n";
        return o.str();
    }
    if (temp == 0)
    {
        o << "\\0";
        return o.str();
    }
    if (a == ' ')
    {
        o << "' '";
        return o.str();
    }
    if (temp == 9)
    {
        o << "\\t";
        return o.str();
    }
    if (isprint(temp))
    {
        o << a;
        return o.str();
    }
    o << ("\\x" + to_2digit_hexadecimal(temp));
    return o.str();
}

// readers guaranteed to be 4 in length
string full_line(char readers[], int valid)
{
    ostringstream o;
    o << "|";
    for (int i = 0; i < 4; i++)
    {
        if (i < valid)
            o << get_printable(static_cast<unsigned char>(readers[i]));
        else
            o << "     ";
    }
    o << " |";
    for (int i = 0; i < 4; i++)
    {
        if (i < valid)
            o << setw(3) << to_2digit_hexadecimal(static_cast<int>(static_cast<unsigned char>(readers[i])));
        else
            o << "   ";
    }
    o << " | ";
    for (int i = 0; i < 4; i++)
    {
        if (i < valid)
            o << to_8b_binary(static_cast<int>(static_cast<unsigned char>(readers[i]))) + " ";
        else
            o << "         ";
    }
    o << "|";
    for (int i = 0; i < 4; i++)
    {
        if (i < valid)
            o << setw(4) << static_cast<int>(static_cast<unsigned char>(readers[i]));
        else
            o << "    ";
    }
    o << " |";
    return o.str();
}

int main(int argc, const char *argv[])
{
    if (argc < 3)
    {
        cout << "Usage: ./bytes_to_hex_table input_file output_file" << endl;
        return -1;
    }

    ifstream inp(argv[1], ifstream::binary);
    if (!inp)
    {
        cout << "Could not open input file \"" + string(argv[1]) + "\"" << endl;
        return -2;
    }
    ofstream out(argv[2]);
    if (!out)
    {
        cout << "Could not open output file \"" + string(argv[2]) + "\"" << endl;
        return -3;
    }

    // header of the table
    out << "| Printable           | Hexadecimal | Binary                              | Decimal         |\n|---------------------+-------------+-------------------------------------+-----------------|" << endl;
    int cur = 0;
    char readers[4];
    while (inp.read(&readers[cur % 4], 1))
    {
        cur++;
        if (cur % 4 == 0 && cur != 0)
        {
            out << full_line(readers, 4) << endl;
        }
    }
    if (cur % 4 != 0)
        out << full_line(readers, cur % 4) << endl;

    inp.close();
    out.close();
    return 0;
}