#include <string>

class Solution {
public:
    int scoreOfParentheses(std::string s) {
        int score = 0;
        int depth = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                // Agar pichla character '(' tha, toh ye ek "()" pair hai
                if (s[i - 1] == '(') {
                    score += 1 << depth; // 1 ko left shift karna mtlb 2^depth add karna
                }
            }
        }
        
        return score;
    }
};