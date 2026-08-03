class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n + 1, -1000000000);
        dp[n] = 0;
        
        for (int i = n - 1; i >= 0; --i) {
            int take = 0;
            for (int j = 0; j < 3 && i + j < n; ++j) {
                take += stoneValue[i + j];
                dp[i] = max(dp[i], take - dp[i + j + 1]);
            }
        }
        
        if (dp[0] > 0) return "Alice";
        if (dp[0] < 0) return "Bob";
        return "Tie";
    }
};
