class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> lastIndex(26, 0);
        for (int i = 0; i < s.length(); ++i) {
            lastIndex[s[i] - 'a'] = i;
        }
        
        vector<bool> seen(26, false);
        string st = "";
        
        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];
            
            if (seen[c - 'a']) {
                continue;
            }
            
            while (!st.empty() && st.back() > c && lastIndex[st.back() - 'a'] > i) {
                seen[st.back() - 'a'] = false;
                st.pop_back();
            }
            
            st.push_back(c);
            seen[c - 'a'] = true;
        }
        
        return st;
    }
};