class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;

        // Find minimum and maximum positions
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }

        int left = min(minIndex, maxIndex);
        int right = max(minIndex, maxIndex);

        // 1. Remove both from front
        int front = right + 1;

        // 2. Remove both from back
        int back = n - left;

        // 3. Remove one from front and one from back
        int both = (left + 1) + (n - right);

        return min({front, back, both});
    }
};