#pragma GCC optimize("O3,unroll-loops")
#include <string>

class Solution {
public:
    int minChanges(std::string s) {
        int changes = 0;
        int n = s.length();
        
        for (int i = 0; i < n; i += 2) {
            if (s[i] != s[i + 1]) {
                changes++;
            }
        }
        
        return changes;
    }
};