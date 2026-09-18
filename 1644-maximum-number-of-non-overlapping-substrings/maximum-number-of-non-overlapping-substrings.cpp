#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int getRightPosition(const std::string& s, int i, const std::vector<int>& left, const std::vector<int>& right) {
        int right_end = right[s[i] - 'a'];
        for (int j = i; j <= right_end; ++j) {
            if (left[s[j] - 'a'] < i) {
                return -1;
            }
            right_end = std::max(right_end, right[s[j] - 'a']);
        }
        return right_end;
    }

    std::vector<std::string> maxNumOfSubstrings(std::string s) {
        std::vector<int> left(26, -1);
        std::vector<int> right(26, -1);
        
        for (int i = 0; i < s.length(); ++i) {
            if (left[s[i] - 'a'] == -1) {
                left[s[i] - 'a'] = i;
            }
            right[s[i] - 'a'] = i;
        }
        
        std::vector<std::string> result;
        int last_right = -1;
        
        for (int i = 0; i < s.length(); ++i) {
            if (i == left[s[i] - 'a']) {
                int new_right = getRightPosition(s, i, left, right);
                if (new_right != -1) {
                    if (i > last_right) {
                        result.push_back(s.substr(i, new_right - i + 1));
                    } else {
                        result.back() = s.substr(i, new_right - i + 1);
                    }
                    last_right = new_right;
                }
            }
        }
        
        return result;
    }
};