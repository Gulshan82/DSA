class Solution {
   
    int getGcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixGcd(n);
        int mx = nums[0];
        
       
        for (int i = 0; i < n; ++i) {
            if (nums[i] > mx) {
                mx = nums[i];
            }
            prefixGcd[i] = getGcd(nums[i], mx);
        }
        
       
        sort(prefixGcd.begin(), prefixGcd.end());
        
       
        long long total_sum = 0;
        int left = 0;
        int right = n - 1;
        
        while (left < right) {
            total_sum += getGcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }
        
        return total_sum;
    }
};