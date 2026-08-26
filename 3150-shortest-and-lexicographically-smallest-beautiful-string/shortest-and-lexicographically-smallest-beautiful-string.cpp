class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int left = 0;
        int ones = 0;
        string best = "";
        
        for (int right = 0; right < s.length(); ++right) {
            if (s[right] == '1') {
                ones++;
            }
            
            while (ones > k || (ones == k && s[left] == '0')) {
                if (s[left] == '1') {
                    ones--;
                }
                left++;
            }
            
            if (ones == k) {
                string curr = s.substr(left, right - left + 1);
                if (best == "" || curr.length() < best.length() || 
                   (curr.length() == best.length() && curr < best)) {
                    best = curr;
                }
            }
        }
        
        return best;
    }
};