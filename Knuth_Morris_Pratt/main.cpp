#include <iostream>
#include <vector>

using namespace std;

void magic_lines();

bool algorithm_Knuth_Morris_Pratt();

vector<int> construct_Lps(string &pattern);

bool match(char pattern, char character);

int main() {
    magic_lines();
    if (algorithm_Knuth_Morris_Pratt()) cout << 'T';
    else cout << 'N';
    return 0;
}

void magic_lines() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}

bool algorithm_Knuth_Morris_Pratt() {
    string pattern;
    getline(cin, pattern);
    int pattern_length = pattern.length();

    vector<int> lps = construct_Lps(pattern);

    int pattern_index = 0;
    char character;

    while (cin.get(character)) {
        if (character == '\n') break;

        while (!match(pattern[pattern_index], character) && pattern_index != 0)
            pattern_index = lps[pattern_index - 1];
        if (match(pattern[pattern_index], character)) {
            ++pattern_index;
            if (pattern_index == pattern_length) return true;
        }
    }

    return false;
}


/*
pattern_index = lps[pattern_index - 1]:
      patern: ABABAC; text: ABABABABACA;
                            ABABAx  change pattern_index
                              ABABAx
                                ABABAC = pattern = succeed
*/

vector<int> construct_Lps(string &pattern) {
    int pattern_length = pattern.length();
    vector<int> lps(pattern_length, 0);

    int len = 0;
    int i = 1;
    while (i < pattern_length) {
        if (pattern[len] == pattern[i]) {
            ++len;
            lps[i] = len;
            ++i;
        } else {
            if (len != 0) len = lps[len - 1];
            else {
                lps[i] = 0;
                ++i;
            }
        }
    }

    return lps;
}

bool match(char pattern, char character) {
    switch (pattern) {
        case 'a':
            return islower(character);
        case 'A':
            return isupper(character);
        case '.':
            return character == '.' || character == '?' || character == '!' || character == ',' ||
                   character == ';' || character == ':' || character == '-';
        case '0':
            return isdigit(character);
        case ' ':
            return character == ' ';
        default:
            return false;
    }
}
