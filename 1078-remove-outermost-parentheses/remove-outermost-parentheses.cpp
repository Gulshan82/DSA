#include <string>

class Solution {
public:
    std::string removeOuterParentheses(std::string s) {
        std::string result = "";
        int opened = 0;
        
        for (char c : s) {
            if (c == '(') {
                // Agar already open parentheses hain, toh ye outermost nahi hai
                if (opened > 0) {
                    result += c;
                }
                opened++;
            } else if (c == ')') {
                opened--;
                // Agar decrement karne ke baad bhi > 0 hai, toh ye outermost nahi hai
                if (opened > 0) {
                    result += c;
                }
            }
        }
        
        return result;
    }
};