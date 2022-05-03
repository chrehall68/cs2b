#include <map>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <uchar.h>  // char32_t

using std::map;
using std::istream;
using std::string;
using std::getline;
using std::endl;
using std::cout;
using std::ifstream;
using std::runtime_error;

#include "unicode_data.h"

// Print out the code point names from a "UnicodeData.txt" file that you can
// download from https://www.unicode.org/Public/14.0.0/ucd/
// The file format is documented at https://www.unicode.org/L2/L1999/UnicodeData.html
void print_code_point_names(istream& is) {
  for (string hex_code, name, rest_of_line;
      getline(is, hex_code, ';') && getline(is, name, ';') && getline(is, rest_of_line); ) {
    cout << stoul(hex_code, nullptr, 16) << " code point name is \"" << name << '"' << endl;
  }
  if (is.bad()) {
    throw runtime_error("Unable to print all code point names from istream!");
  }
}

// Create a map from code point number to the string name
// e.g. load_code_point_names("UnicodeData.txt")[128049] == "CAT FACE"
map<char32_t, string> load_code_point_names(istream& is) {
  map<char32_t, string> code_point_names;
  for (string hex_code, name, rest_of_line;
      getline(is, hex_code, ';') && getline(is, name, ';') && getline(is, rest_of_line); ) {
    // TODO: Make the hex_code map to the name...
  }
  if (is.bad()) {
    throw runtime_error("Unable to load_code_point_names from istream!");
  }
  return code_point_names;
}

map<char32_t, string> load_code_point_names(const string& filename) {
  ifstream input_file(filename);
  return load_code_point_names(input_file);
}