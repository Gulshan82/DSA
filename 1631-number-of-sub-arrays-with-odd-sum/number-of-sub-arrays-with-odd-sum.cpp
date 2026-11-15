#pragma GCC optimize("O3,unroll-loops")
#include <vector>

class Solution {
public:
    int numOfSubarrays(std::vector<int>& arr) {
        int ans = 0;
        int odd_count = 0;
        int even_count = 1;
        int parity = 0;
        const int MOD = 1e9 + 7;
        
        for (int x : arr) {
            parity ^= (x & 1);
            if (parity == 0) {
                ans += odd_count;
                if (ans >= MOD) ans -= MOD;
                even_count++;
            } else {
                ans += even_count;
                if (ans >= MOD) ans -= MOD;
                odd_count++;
            }
        }
        
        return ans;
    }
};