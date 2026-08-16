class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int c0 = 0, c1 = 0, c2 = 0;
        
        for (int x : stones) {
            int mod = x % 3;
            if (mod == 0) c0++;
            else if (mod == 1) c1++;
            else c2++;
        }
        
        if (c0 % 2 == 0) {
            return c1 > 0 && c2 > 0;
        } else {
            return abs(c1 - c2) > 2;
        }
    }
};