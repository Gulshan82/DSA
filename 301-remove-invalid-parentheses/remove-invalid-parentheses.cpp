#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        int left_rem = 0, right_rem = 0;
        
        // Pehle count karte hain ki kitne extra '(' aur ')' remove karne ki zaroorat hai
        for (char c : s) {
            if (c == '(') {
                left_rem++;
            } else if (c == ')') {
                if (left_rem == 0) {
                    right_rem++;
                } else {
                    left_rem--;
                }
            }
        }
        
        std::vector<std::string> result;
        dfs(s, 0, left_rem, right_rem, result);
        return result;
    }
    
private:
    bool isValid(const std::string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') count++;
            else if (c == ')') count--;
            if (count < 0) return false;
        }
        return count == 0;
    }
    
    void dfs(std::string s, int start, int l, int r, std::vector<std::string>& result) {
        // Agar koi aur brackets remove nahi karne hain, toh validity check karo
        if (l == 0 && r == 0) {
            if (isValid(s)) {
                result.push_back(s);
            }
            return;
        }
        
        for (int i = start; i < s.length(); ++i) {
            // Duplicate results avoid karne ke liye consecutive same characters ko skip karo
            if (i != start && s[i] == s[i - 1]) continue;
            
            if (s[i] == '(' || s[i] == ')') {
                std::string current = s.substr(0, i) + s.substr(i + 1);
                
                // Hamesha pehle ')' remove karne ki koshish karte hain, phir '('
                if (r > 0 && s[i] == ')') {
                    dfs(current, i, l, r - 1, result);
                } else if (l > 0 && s[i] == '(') {
                    dfs(current, i, l - 1, r, result);
                }
            }
        }
    }
};