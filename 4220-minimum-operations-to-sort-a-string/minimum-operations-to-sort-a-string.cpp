#include <string>
#include <algorithm>

class Solution {
public:
    int minOperations(std::string s) {
        int n = s.length();
        if (std::is_sorted(s.begin(), s.end())) {
            return 0;
        }
        if (n == 2) {
            return -1;
        }
        
        std::string p = s;
        std::sort(p.begin(), p.begin() + n - 1);
        std::string suff = s;
        std::sort(suff.begin() + 1, suff.end());
        
        if (std::is_sorted(p.begin(), p.end()) || std::is_sorted(suff.begin(), suff.end())) {
            return 1;
        }
        
        std::string p_s = p;
        std::sort(p_s.begin() + 1, p_s.end());
        std::string s_p = suff;
        std::sort(s_p.begin(), s_p.begin() + n - 1);
        
        if (std::is_sorted(p_s.begin(), p_s.end()) || std::is_sorted(s_p.begin(), s_p.end())) {
            return 2;
        }
        
        return 3;
    }
};