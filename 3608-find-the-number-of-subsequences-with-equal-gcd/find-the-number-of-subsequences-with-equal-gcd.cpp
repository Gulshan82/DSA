class Solution {
   
    int getGcd(int a, int b) {
        if (b == 0) return a;
        return getGcd(b, a % b);
    }
    
public:
    int subsequencePairCount(vector<int>& nums) {
        int MOD = 1e9 + 7;
        
      
        int max_val = 0;
        for (int num : nums) {
            if (num > max_val) max_val = num;
        }
        
        
        vector<vector<int>> dp(max_val + 1, vector<int>(max_val + 1, 0));
        
      
        dp[0][0] = 1;
        
        for (int x : nums) {
            
            vector<vector<int>> next_dp = dp;
            
            for (int g1 = 0; g1 <= max_val; ++g1) {
                for (int g2 = 0; g2 <= max_val; ++g2) {
                    if (dp[g1][g2] == 0) continue;
                    
                   
                    int next_g1 = (g1 == 0) ? x : getGcd(g1, x);
                    next_dp[next_g1][g2] = (next_dp[next_g1][g2] + dp[g1][g2]) % MOD;
                    
                    
                    int next_g2 = (g2 == 0) ? x : getGcd(g2, x);
                    next_dp[g1][next_g2] = (next_dp[g1][next_g2] + dp[g1][g2]) % MOD;
                    
                    
                }
            }
          
            dp = next_dp;
        }
        
        int ans = 0;
       
        for (int i = 1; i <= max_val; ++i) {
            ans = (ans + dp[i][i]) % MOD;
        }
        
        return ans;
    }
};