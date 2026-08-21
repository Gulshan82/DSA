class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();
        long long low = 1;
        long long high = (long long)*min_element(coins.begin(), coins.end()) * k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            long long cnt = 0;

            for (int mask = 1; mask < (1 << n); ++mask) {
                long long l = 1;
                int set_bits = 0;
                
                for (int i = 0; i < n; ++i) {
                    if ((mask >> i) & 1) {
                        set_bits++;
                        long long g = std::gcd(l, (long long)coins[i]);
                        
                        if (l / g > mid / coins[i]) {
                            l = mid + 1; 
                            break;
                        }
                        l = (l / g) * coins[i];
                    }
                }
                
                if (set_bits % 2 == 1) {
                    cnt += (mid / l);
                } else {
                    cnt -= (mid / l);
                }
            }

            if (cnt >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};