#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <string>

class Solution {
    std::vector<std::vector<int>> adj;
    std::vector<int> ans;
    int last_seen[26];

    void dfs(int u, const std::vector<int>& parent, const std::string& s) {
        int c = s[u] - 'a';
        int prev = last_seen[c];
        int new_p = (prev != -1) ? prev : parent[u];
        
        last_seen[c] = u;
        for (int v : adj[u]) {
            dfs(v, parent, s);
        }
        last_seen[c] = prev;
        
        if (new_p != -1) {
            ans[new_p] += ans[u];
        }
    }

public:
    std::vector<int> findSubtreeSizes(std::vector<int>& parent, std::string s) {
        int n = parent.size();
        adj.assign(n, std::vector<int>());
        ans.assign(n, 1);
        
        for (int i = 0; i < 26; ++i) {
            last_seen[i] = -1;
        }
        
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }
        
        dfs(0, parent, s);
        return ans;
    }
};