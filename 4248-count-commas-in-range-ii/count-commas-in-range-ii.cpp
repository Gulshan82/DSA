#include <climits>

class Solution {
public:
    long long countCommas(long long n) {
        long long commas = 0;
        long long base = 1000;
        
        while (n >= base) {
            commas += (n - base + 1);
            if (LLONG_MAX / 1000 < base) {
                break;
            }
            base *= 1000;
        }
        
        return commas;
    }
};