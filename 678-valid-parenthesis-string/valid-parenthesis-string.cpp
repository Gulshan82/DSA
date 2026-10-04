#include <string>

class Solution {
public:
    bool checkValidString(std::string s) {
        int cmin = 0, cmax = 0;
        for (char c : s) {
            if (c == '(') {
                cmax++;
                cmin++;
            } else if (c == ')') {
                cmax--;
                cmin--;
            } else if (c == '*') {
                cmax++; // Treat '*' as '('
                cmin--; // Treat '*' as ')'
            }
            
            if (cmax < 0) return false; // Currently, don't have enough open parentheses
            if (cmin < 0) cmin = 0;     // It's invalid to have cmin < 0, so treat '*' as empty instead of ')'
        }
        
        return cmin == 0; // Return true if we can have exactly 0 open parentheses
    }
};