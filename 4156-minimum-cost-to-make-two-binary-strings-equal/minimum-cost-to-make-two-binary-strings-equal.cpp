class Solution {
public:
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost) {
        long long diff01 = 0, diff10 = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '0' && t[i] == '1') {
                diff01++;
            } else if (s[i] == '1' && t[i] == '0') {
                diff10++;
            }
        }
        
        long long op_cost = min(2LL * flipCost, (long long)swapCost);
        long long same_cost = min(2LL * flipCost, (long long)swapCost + crossCost);
        
        long long pairs = min(diff01, diff10);
        long long rem = abs(diff01 - diff10);
        
        long long total_cost = (pairs * op_cost) + ((rem / 2) * same_cost) + ((rem % 2) * flipCost);
        
        return total_cost;
    }
};