#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxPalindromes(std::string s, int k) {
        int n = s.length();
        std::vector<std::vector<bool>> isPal(n, std::vector<bool>(n, false));
        
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (s[i] == s[j] && (j - i <= 2 || isPal[i + 1][j - 1])) {
                    isPal[i][j] = true;
                }
            }
        }
        
        std::vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1];
            for (int j = i - k; j >= 0; --j) {
                if (isPal[j][i - 1]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return dp[n];
    }
};