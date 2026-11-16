#pragma GCC optimize("O3,unroll-loops")
#include <string>

class Solution {
public:
    std::string digitSum(std::string s, int k) {
        while (s.length() > k) {
            std::string next_s = "";
            int n = s.length();
            for (int i = 0; i < n; i += k) {
                int sum = 0;
                for (int j = i; j < i + k && j < n; ++j) {
                    sum += s[j] - '0';
                }
                next_s += std::to_string(sum);
            }
            s = next_s;
        }
        return s;
    }
};