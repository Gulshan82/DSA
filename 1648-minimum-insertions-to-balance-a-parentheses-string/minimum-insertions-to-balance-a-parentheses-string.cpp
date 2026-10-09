#include <string>

class Solution {
public:
    int minInsertions(std::string s) {
        int insertions = 0;
        int req_right = 0;
        
        for (char c : s) {
            if (c == '(') {
                if (req_right % 2 != 0) {
                    insertions++;
                    req_right--;
                }
                req_right += 2;
            } else {
                req_right--;
                if (req_right < 0) {
                    insertions++;
                    req_right = 1;
                }
            }
        }
        
        return insertions + req_right;
    }
};