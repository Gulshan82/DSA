#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxActiveSectionsAfterTrade(std::string s) {
        int initial_ones = 0;
        for (char c : s) {
            if (c == '1') {
                initial_ones++;
            }
        }
        
        std::string t = "1" + s + "1";
        std::vector<int> O, Z;
        int n = t.length();
        int i = 0;
        
        while (i < n) {
            int ones = 0;
            while (i < n && t[i] == '1') {
                ones++;
                i++;
            }
            O.push_back(ones);
            
            if (i == n) break;
            
            int zeros = 0;
            while (i < n && t[i] == '0') {
                zeros++;
                i++;
            }
            Z.push_back(zeros);
        }
        
        int k = Z.size();
        if (k < 2) {
            return initial_ones;
        }
        
        std::vector<int> pref_max(k, 0), suff_max(k, 0);
        pref_max[0] = Z[0];
        for (int j = 1; j < k; j++) {
            pref_max[j] = std::max(pref_max[j-1], Z[j]);
        }
        suff_max[k-1] = Z[k-1];
        for (int j = k - 2; j >= 0; j--) {
            suff_max[j] = std::max(suff_max[j+1], Z[j]);
        }
        
        int max_gain = 0;
        
        for (int j = 1; j < k; j++) {
            int merged = Z[j-1] + O[j] + Z[j];
            int other_max = 0;
            
            if (j - 2 >= 0) {
                other_max = std::max(other_max, pref_max[j-2]);
            }
            if (j + 1 < k) {
                other_max = std::max(other_max, suff_max[j+1]);
            }
            
            int gain = std::max(merged, other_max) - O[j];
            max_gain = std::max(max_gain, gain);
        }
        
        return initial_ones + max_gain;
    }
};