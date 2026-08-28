class Solution {
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        sort(words.begin(), words.end());
        int n = words.size();
        
        vector<int> startWith[26];
        vector<int> startEnd[26][26];
        
        for (int i = 0; i < n; ++i) {
            int first = words[i][0] - 'a';
            int last = words[i][3] - 'a';
            startWith[first].push_back(i);
            startEnd[first][last].push_back(i);
        }
        
        vector<vector<string>> ans;
        
        for (int t = 0; t < n; ++t) {
            int t_first = words[t][0] - 'a';
            int t_last = words[t][3] - 'a';
            
            for (int l : startWith[t_first]) {
                if (l == t) continue;
                int l_last = words[l][3] - 'a';
                
                for (int r : startWith[t_last]) {
                    if (r == t || r == l) continue;
                    int r_last = words[r][3] - 'a';
                    
                    for (int b : startEnd[l_last][r_last]) {
                        if (b == t || b == l || b == r) continue;
                        
                        ans.push_back({words[t], words[l], words[r], words[b]});
                    }
                }
            }
        }
        
        return ans;
    }
};