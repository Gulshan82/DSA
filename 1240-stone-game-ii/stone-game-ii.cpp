class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));
        vector<int> suffixSum(n, 0);
        
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }
        
        function<int(int, int)> solve = [&](int i, int m) {
            if (i >= n) return 0;
            if (i + 2 * m >= n) return suffixSum[i];
            if (dp[i][m] != 0) return dp[i][m];
            
            int minOpponent = 1e9;
            for (int x = 1; x <= 2 * m; ++x) {
                minOpponent = min(minOpponent, solve(i + x, max(m, x)));
            }
            
            return dp[i][m] = suffixSum[i] - minOpponent;
        };
        
        return solve(0, 1);
    }
};