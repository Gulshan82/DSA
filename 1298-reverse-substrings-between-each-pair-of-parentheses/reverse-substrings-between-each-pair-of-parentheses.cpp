#include <string>
#include <vector>
#include <stack>

class Solution {
public:
    std::string reverseParentheses(std::string s) {
        int n = s.length();
        std::vector<int> pair(n);
        std::stack<int> st;
        
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }
        
        std::string result;
        int i = 0, d = 1;
        
        while (i < n) {
            if (s[i] == '(' || s[i] == ')') {
                i = pair[i];
                d = -d;
            } else {
                result += s[i];
            }
            i += d;
        }
        
        return result;
    }
};