#include "utf8_string.h"

#include <uchar.h>  // char32_t

#include <iostream>
#include <map>
#include <vector>

#include "utf8_codepoint.h"

using std::istream;
using std::map;
using std::ostream;
using std::string;
using std::to_string;
using std::vector;

UTF8String::UTF8String(const char* c_string) {
    for (int i = 0; c_string[i] != '\0'; ++i) {
        this->data.emplace_back(c_string[i]);
    }
}

UTF8String::UTF8String(const char32_t* c_string) {
    for (int i = 0; c_string[i] != U'\0'; ++i) {
        this->data.emplace_back(c_string[i]);
    }
}

int UTF8String::size() const {
    return data.size();
}

void UTF8String::push_back(const UTF8CodePoint& c) {
    data.push_back(c);
}

UTF8String& UTF8String::operator+=(const UTF8String& other) {
    data.insert(data.end(), other.data.begin(), other.data.end());
    return *this;
}

UTF8String UTF8String::operator+(const UTF8String& other) const {
    UTF8String copy(*this);
    copy += other;
    return copy;
}

UTF8String operator+(UTF8CodePoint a, UTF8CodePoint b) {
    UTF8String result;
    result.push_back(a);
    result.push_back(b);
    return result;
}

UTF8CodePoint& UTF8String::operator[](size_t idx) {
    return data[idx];
}
UTF8CodePoint UTF8String::operator[](size_t idx) const {
    return data[idx];
}

ostream& operator<<(ostream& os, const UTF8String& utf8_str) {
    for (const UTF8CodePoint& point : utf8_str.data) os << point;
    return os;
}

istream& getline(istream& is, UTF8String& utf8_str) {
    UTF8CodePoint c;
    while ((is >> c) && c != '\n') {
        utf8_str.push_back(c);
    }
    return is;
}

// TODO: Check code_point_names and put the code point name if it exists.
vector<string> get_code_point_names(const UTF8String& utf8_str, const map<char32_t, string>& code_point_names) {
    vector<string> result;
    for (int i = 0; i < utf8_str.size(); ++i) {
        if (code_point_names.find(static_cast<char32_t>(utf8_str[i])) == code_point_names.end()) {
            result.push_back("Code Point " + to_string(static_cast<char32_t>(utf8_str[i])));
        } else {
            result.push_back(code_point_names.at(static_cast<char32_t>(utf8_str[i])));
        }
    }
    return result;
}