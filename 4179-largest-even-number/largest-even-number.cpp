class Solution {
public:
    string largestEven(string s) {
        int last_two_idx = -1;
        
        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] == '2') {
                last_two_idx = i;
                break;
            }
        }
        
        if (last_two_idx == -1) {
            return "";
        }
        
        return s.substr(0, last_two_idx + 1);
    }
};