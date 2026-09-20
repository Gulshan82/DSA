#include <string>

class Solution {
public:
    int reverseDegree(std::string s) {
        int total = 0;
        for (int i = 0; i < s.length(); ++i) {
            int reverse_pos = 26 - (s[i] - 'a');
            total += reverse_pos * (i + 1);
        }
        return total;
    }
};