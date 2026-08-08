class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        
        vector<int> last(m, -1);
        int j = m - 1;
        for (int i = n - 1; i >= 0 && j >= 0; --i) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
        }
        
        vector<int> result;
        bool changed = false;
        j = 0;
        
        for (int i = 0; i < n && j < m; ++i) {
            bool isMatch = (word1[i] == word2[j]);
            bool canChange = (!changed && (j == m - 1 || last[j + 1] > i));
            
            if (isMatch || canChange) {
                if (!isMatch) {
                    changed = true;
                }
                result.push_back(i);
                j++;
            }
        }
        
        if (result.size() == m) {
            return result;
        }
        return {};
    }
};