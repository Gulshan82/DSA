class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }
        
        vector<bool> suspicious(n, false);
        queue<int> q;
        
        q.push(k);
        suspicious[k] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (!suspicious[v]) {
                    suspicious[v] = true;
                    q.push(v);
                }
            }
        }
        
        bool canRemove = true;
        for (const auto& edge : invocations) {
            int u = edge[0];
            int v = edge[1];
            
            if (!suspicious[u] && suspicious[v]) {
                canRemove = false;
                break;
            }
        }
        
        vector<int> ans;
        if (canRemove) {
            for (int i = 0; i < n; ++i) {
                if (!suspicious[i]) {
                    ans.push_back(i);
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};