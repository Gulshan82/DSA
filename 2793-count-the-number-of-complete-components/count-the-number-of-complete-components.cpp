class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n, false);
        int completeCount = 0;
        
       
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                int verticesCount = 0;
                int edgesCount = 0;
                
              
                queue<int> q;
                q.push(i);
                visited[i] = true;
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    verticesCount++;
                
                    edgesCount += adj[node].size();
                    
                    for (int neighbor : adj[node]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
                
               
                edgesCount /= 2;
                
                if (edgesCount == verticesCount * (verticesCount - 1) / 2) {
                    completeCount++;
                }
            }
        }
        
        return completeCount;
    }
};