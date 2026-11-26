class Solution {
public:
    bool canAliceWin(int n) {
        int take = 10;
        while (n >= take && take > 0) {
            n -= take;
            take--;
        }
        return (10 - take) & 1;
    }
};