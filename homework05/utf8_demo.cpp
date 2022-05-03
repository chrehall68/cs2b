#include <fstream>
#include <iostream>
#include <list>

#include "unicode_data.h"
#include "utf8_codepoint.h"
#include "utf8_string.h"

using std::cout;
using std::endl;
using std::list;

int main(int argc, const char* argv[])
{
    list<char32_t> animal_list = {0x1F431, 0x1F432, 0x1F434, 0x1F435, U'🐶'};
    UTF8String str(animal_list);

    map<char32_t, string> code_point_names = load_code_point_names("UnicodeData.txt");
    cout << str << " is composed of code points:\n";
    for (int i = 0; i < str.size(); ++i) {
        // Here, we static_cast str[i] from a UTF8CodePoint to a char32_t so we can
        // print it out as a number, like "127997".
        cout << "  " << static_cast<char32_t>(str[i]) << endl;
    }
    cout << endl;

    cout << str << " is composed of code points with names:\n";
    for (const string& name : get_code_point_names(str, code_point_names)) {
        cout << "  " << name << endl;
    }
    cout << endl;

    UTF8CodePoint raised_hand(0x270B);
    UTF8CodePoint medium_skin_tone(127997);
    // raised_hand with medium_skin_tone
    UTF8String rhwmst = raised_hand + medium_skin_tone;
    cout << raised_hand << " + " << medium_skin_tone << " == " << rhwmst << endl;
    return 0;
}