#include <string>
#include <vector>

class Solution {
public:
    int distinctSubseqII(std::string s) {
        int MOD = 1e9 + 7;
        std::vector<int> endsWith(26, 0);
        int total = 0;
        
        for (char c : s) {
            int charIdx = c - 'a';
            
            // The new subsequences we can form ending with 'c'
            int added = (total + 1) % MOD;
            
            // The net increase in total subsequences
            int diff = (added - endsWith[charIdx] + MOD) % MOD;
            
            // Update total and endsWith for the current character
            total = (total + diff) % MOD;
            endsWith[charIdx] = added;
        }
        
        return total;
    }
};