class Solution {
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r > n / 2) r = n - r;
        long long ans = 1;
        for (int i = 1; i <= r; ++i) {
            ans = ans * (n - i + 1) / i;
            if (ans > 2000000000LL) return 2000000001LL;
        }
        return ans;
    }

    long long getPermutations(vector<int>& freq) {
        long long total = 1;
        int sum = 0;
        for (int f : freq) {
            if (f > 0) {
                sum += f;
                total *= nCr(sum, f);
                if (total > 2000000000LL) return 2000000001LL;
            }
        }
        return total;
    }

public:
    string smallestPalindrome(string s, int k) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        string mid = "";
        vector<int> half_freq(26, 0);
        int half_len = 0;

        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                mid += (char)(i + 'a');
            }
            half_freq[i] = count[i] / 2;
            half_len += half_freq[i];
        }

        long long total_perms = getPermutations(half_freq);
        if (k > total_perms) {
            return "";
        }

        string left_half = "";
        for (int i = 0; i < half_len; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (half_freq[j] > 0) {
                    half_freq[j]--;
                    long long perms = getPermutations(half_freq);
                    
                    if (k <= perms) {
                        left_half += (char)(j + 'a');
                        break;
                    } else {
                        k -= perms;
                        half_freq[j]++;
                    }
                }
            }
        }

        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());
        
        return left_half + mid + right_half;
    }
};