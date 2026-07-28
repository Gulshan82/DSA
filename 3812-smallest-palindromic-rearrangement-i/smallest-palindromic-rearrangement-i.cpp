class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        string left_half = "";
        string middle = "";
        
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                middle += (char)(i + 'a');
            }
            for (int j = 0; j < count[i] / 2; ++j) {
                left_half += (char)(i + 'a');
            }
        }
        
        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());
        
        return left_half + middle + right_half;
    }
};