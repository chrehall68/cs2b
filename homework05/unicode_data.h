#ifndef _UNICODE_DATA_
#define _UNICODE_DATA_

#include <uchar.h>  // char32_t

#include <iostream>
#include <map>
#include <string>

using std::istream;
using std::map;
using std::string;

// Print out the code point names from a "UnicodeData.txt" file that you can
// download from https://www.unicode.org/Public/14.0.0/ucd/
// The file format is documented at https://www.unicode.org/L2/L1999/UnicodeData.html
void print_code_point_names(istream& is);
// Create a map from code point number to the string name
// e.g. 128049 -> "CAT FACE"
map<char32_t, string> load_code_point_names(istream& is);
map<char32_t, string> load_code_point_names(const string& filename);

#endif  // _UNICODE_DATA_