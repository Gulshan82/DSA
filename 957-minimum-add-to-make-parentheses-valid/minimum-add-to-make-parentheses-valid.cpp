#include <string>

class Solution {
public:
    int minAddToMakeValid(std::string s) {
        int open_needed = 0;
        int close_needed = 0;
        
        for (char c : s) {
            if (c == '(') {
                close_needed++;
            } else if (c == ')') {
                if (close_needed > 0) {
                    close_needed--;
                } else {
                    open_needed++;
                }
            }
        }
        
        return open_needed + close_needed;
    }
};