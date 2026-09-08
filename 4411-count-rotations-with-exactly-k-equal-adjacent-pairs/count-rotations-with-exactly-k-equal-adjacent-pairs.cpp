#include <string>

class Solution {
public:
    int countRotations(std::string s, int k) {
        int n = s.length();
        if (n <= 1) return (k == 0) ? 1 : 0;
        
        int current_score = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == s[i + 1]) {
                current_score++;
            }
        }
        
        int ans = 0;
        if (current_score == k) {
            ans++;
        }
        
        for (int i = 1; i < n; ++i) {
            if (s[i - 1] == s[i]) {
                current_score--;
            }
            if (s[(i + n - 2) % n] == s[(i + n - 1) % n]) {
                current_score++;
            }
            if (current_score == k) {
                ans++;
            }
        }
        
        return ans;
    }
};