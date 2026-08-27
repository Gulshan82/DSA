class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        int best_i = -1;
        char best_c = 0;

        for (int i = 0; i < n; ++i) {
            for (int c = target[i] - 'a' + 1; c < 26; ++c) {
                if (count[c] > 0) {
                    best_i = i;
                    best_c = c + 'a';
                    break;
                }
            }
            if (count[target[i] - 'a'] > 0) {
                count[target[i] - 'a']--;
            } else {
                break;
            }
        }

        if (best_i == -1) {
            return "";
        }

        string ans = target.substr(0, best_i);
        ans += best_c;

        vector<int> rem(26, 0);
        for (char c : s) {
            rem[c - 'a']++;
        }
        for (int i = 0; i < best_i; ++i) {
            rem[target[i] - 'a']--;
        }
        rem[best_c - 'a']--;

        for (int c = 0; c < 26; ++c) {
            if (rem[c] > 0) {
                ans.append(rem[c], c + 'a');
            }
        }

        return ans;
    }
};