class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> counts(26, 0);
        for (char c : s) {
            counts[c - 'a']++;
        }
        
        int odd_count = 0;
        char mid_char = 0;
        vector<int> half_counts(26, 0);
        
        for (int i = 0; i < 26; ++i) {
            if (counts[i] % 2 != 0) {
                odd_count++;
                mid_char = i + 'a';
            }
            half_counts[i] = counts[i] / 2;
        }
        
        if (odd_count > 1) {
            return "";
        }
        
        int m = n / 2;
        string t_left = target.substr(0, m);
        
        bool can_form_exact = true;
        vector<int> temp_counts = half_counts;
        for (char c : t_left) {
            if (temp_counts[c - 'a'] > 0) {
                temp_counts[c - 'a']--;
            } else {
                can_form_exact = false;
                break;
            }
        }
        
        if (can_form_exact) {
            string pal = t_left;
            if (odd_count == 1) pal += mid_char;
            string right_half = t_left;
            reverse(right_half.begin(), right_half.end());
            pal += right_half;
            
            if (pal > target) {
                return pal;
            }
        }
        
        int best_i = -1;
        char best_c = 0;
        temp_counts = half_counts;
        
        for (int i = 0; i < m; ++i) {
            for (int c = t_left[i] - 'a' + 1; c < 26; ++c) {
                if (temp_counts[c] > 0) {
                    best_i = i;
                    best_c = c + 'a';
                    break;
                }
            }
            if (temp_counts[t_left[i] - 'a'] > 0) {
                temp_counts[t_left[i] - 'a']--;
            } else {
                break;
            }
        }
        
        if (best_i == -1) {
            return "";
        }
        
        string ans_left = t_left.substr(0, best_i);
        ans_left += best_c;
        
        vector<int> rem_counts = half_counts;
        for (char c : ans_left) {
            rem_counts[c - 'a']--;
        }
        
        for (int c = 0; c < 26; ++c) {
            if (rem_counts[c] > 0) {
                ans_left.append(rem_counts[c], c + 'a');
            }
        }
        
        string final_pal = ans_left;
        if (odd_count == 1) final_pal += mid_char;
        string ans_right = ans_left;
        reverse(ans_right.begin(), ans_right.end());
        final_pal += ans_right;
        
        return final_pal;
    }
};