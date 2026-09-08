class Solution {
public:
    int countCommas(int n) {
        int commas = 0;
        long long base = 1000;
        
        while (n >= base) {
            commas += (n - base + 1);
            base *= 1000;
        }
        
        return commas;
    }
};