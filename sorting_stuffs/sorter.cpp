#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

ifstream in("./Wordle.csv");

void insert_word(map<char, vector<string>>& m, string str, int idx = 0) {
    if (m.find(str[idx]) == m.end()) {
        m.insert(std::pair<char, vector<string>>(str[0], vector<string>()));
    }
    m[str[idx]].push_back(str);
}

int main() {
    ifstream in("./Wordle.csv");
    ofstream out("./out.csv");

    map<char, vector<string>> maps[5];
    char* reader = new char[50];
    int executions = 0;
    while (in.getline(reader, 50, '\n')) {
        if (executions != 0) {
            string buf(reader);
            buf = buf.substr(buf.find(',') + 1);

            string word1 = buf.substr(0, buf.find(','));
            string word2 = buf.substr(buf.find(',') + 1);

            for (int i = 0; i < 5; i++) {
                if (word1 != "null") {
                    insert_word(maps[i], word1, i);
                }
                if (word2 != "null") {
                    insert_word(maps[i], word2, i);
                }
            }
        }

        executions++;
    }

    in.close();

    // sorting
    size_t max_len = 0;
    for (int x = 0; x < 5; x++) {
        for (int i = 0; i < 26; i++) {
            sort(maps[x]['a' + i].begin(), maps[x]['a' + i].end());
            max_len = max(max_len, maps[x]['a' + i].size());
        }
    }

    // headers
    out.write("id,", 3);
    for (int i = 0; i < 5; i++) {
        for (int x = 0; x < 26; x++) {
            ostringstream temp;
            temp << "letter" << i << "_" << static_cast<char>(('a' + x));
            out.write(temp.str().c_str(), temp.str().size());

            // separators
            if (!(i == 4 && x == 25)) {
                out.put(',');
            } else {
                out.put('\n');
            }
        }
    }

    // main columns
    for (size_t i = 0; i < max_len; i++) {
        for (int j = 0; j < 5; j++) {
            for (int x = 0; x < 26; x++) {
                if (j == 0 && x == 0) {
                    ostringstream temp;
                    temp << i << ",";
                    out.write(temp.str().c_str(), temp.str().size());
                }
                // main
                if (i < maps[j]['a' + x].size()) {
                    string& temp = maps[j]['a' + x][i];
                    out.write(temp.c_str(), temp.size());
                } else {
                    out.write("null", 4);
                }

                // separators
                if (!(j == 4 && x == 25)) {
                    out.put(',');
                } else {
                    out.put('\n');
                }
            }
        }
    }

    out.close();
}