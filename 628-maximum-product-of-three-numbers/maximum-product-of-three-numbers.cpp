class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int min1 = 10000, min2 = 10000;
        int max1 = -10000, max2 = -10000, max3 = -10000;
        
        for (int n : nums) {
            if (n <= min1) {
                min2 = min1;
                min1 = n;
            } else if (n <= min2) {
                min2 = n;
            }
            
            if (n >= max1) {
                max3 = max2;
                max2 = max1;
                max1 = n;
            } else if (n >= max2) {
                max3 = max2;
                max2 = n;
            } else if (n >= max3) {
                max3 = n;
            }
        }
        
        return max(min1 * min2 * max1, max1 * max2 * max3);
    }
};