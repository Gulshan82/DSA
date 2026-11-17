#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    int minimumChanges(std::string s, int k) {
        int n = s.length();
        
        std::vector<std::vector<int>> divs(n + 1);
        for (int d = 1; d < n; ++d) {
            for (int v = d * 2; v <= n; v += d) {
                divs[v].push_back(d);
            }
        }
        
        std::vector<std::vector<int>> cost(n, std::vector<int>(n, 1e9));
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int len = j - i + 1;
                int min_changes = 1e9;
                
                for (int d : divs[len]) {
                    int current_changes = 0;
                    for (int offset = 0; offset < d; ++offset) {
                        int l = i + offset;
                        int r = i + offset + ((len - 1 - offset) / d) * d;
                        
                        while (l < r) {
                            if (s[l] != s[r]) {
                                current_changes++;
                            }
                            l += d;
                            r -= d;
                        }
                    }
                    min_changes = std::min(min_changes, current_changes);
                }
                cost[i][j] = min_changes;
            }
        }
        
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n, 1e9));
        
        for (int i = 1; i < n; ++i) {
            dp[1][i] = cost[0][i];
        }
        
        for (int p = 2; p <= k; ++p) {
            for (int i = p * 2 - 1; i < n; ++i) {
                for (int j = (p - 1) * 2 - 1; j <= i - 2; ++j) {
                    if (dp[p - 1][j] != 1e9 && cost[j + 1][i] != 1e9) {
                        dp[p][i] = std::min(dp[p][i], dp[p - 1][j] + cost[j + 1][i]);
                    }
                }
            }
        }
        
        return dp[k][n - 1];
    }
};