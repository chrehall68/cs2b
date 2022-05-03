#ifndef _UTF8_STRING_
#define _UTF8_STRING_

#include <uchar.h>  // char32_t

#include <iostream>
#include <map>
#include <vector>

#include "utf8_codepoint.h"  // char32_t

using std::istream;
using std::map;
using std::ostream;
using std::string;
using std::vector;

class UTF8String {
    vector<UTF8CodePoint> data;

   public:
    // Since we created other constructors, we have to use " = default" to get
    // the default constructor (or define our own default constructor).
    UTF8String() = default;
    UTF8String(const char* c_string);
    UTF8String(const char32_t* c_string);

    template <typename Iterable>
    UTF8String(const Iterable& data) {
        for (char32_t c : data) {
            // for (char32_t* c = std::begin(data); c != std::end(data); ++c) {
            this->data.emplace_back(c);
        }
    }

    int size() const;
    void push_back(const UTF8CodePoint& c);

    // TODO: Make it so I can index into a UTF8String to get a UTF8CodePoint&...
    // like how I can index into an std::string and get back a char&.
    // So UTF8String(U"🍎🍌🥥")[1] == UTF8CodePoint(U'🍌')
    UTF8CodePoint operator[](size_t idx) const;

    UTF8String& operator+=(const UTF8String& other);
    UTF8String operator+(const UTF8String& other) const;

    // TODO: Make if so I can output a UTF8String and it will output it...
    // So `cout << UTF8String(U"🍎🍌🥥") << endl;` works
    friend ostream& operator<<(ostream& os, const UTF8String& utf8_str);
};

// TODO: Make it so we can add two UTF8CodePoint's and get a UTF8String...
// So UTF8CodePoint(U'🆗') + UTF8CodePoint(U'🐕') == UTF8String(U"🆗🐕");
UTF8String operator+(UTF8CodePoint a, UTF8CodePoint b);

istream& getline(istream& is, UTF8String& utf8_str);

vector<string> get_code_point_names(const UTF8String& utf8_str, const map<char32_t, string>& code_point_names);

#endif  // _UTF8_STRING_