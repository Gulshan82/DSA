#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <string>

class Solution {
    int timer;
    int n_nodes;
    std::vector<int> in, out, depth, bit;
    std::vector<std::vector<int>> up, adj;
    
    void add(int idx, int val) {
        for (; idx <= n_nodes + 1; idx += idx & -idx) bit[idx] ^= val;
    }
    
    int query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res ^= bit[idx];
        return res;
    }
    
    void dfs(int u, int p, int d, int current_xor, std::string& s) {
        in[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;
        
        for (int i = 1; i < 20; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        
        current_xor ^= (1 << (s[u] - 'a'));
        
        add(in[u], current_xor);
        add(in[u] + 1, current_xor);
        
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, current_xor, s);
            }
        }
        out[u] = timer;
    }
    
    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) std::swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < 20; ++i) {
            if ((diff >> i) & 1) u = up[u][i];
        }
        if (u == v) return u;
        for (int i = 19; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

public:
    std::vector<bool> palindromePath(int n, std::vector<std::vector<int>>& edges, std::string s, std::vector<std::string>& queries) {
        timer = 0;
        n_nodes = n;
        adj.assign(n, std::vector<int>());
        in.assign(n, 0);
        out.assign(n, 0);
        depth.assign(n, 0);
        bit.assign(n + 2, 0);
        up.assign(n, std::vector<int>(20, 0));
        
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        dfs(0, 0, 0, 0, s);
        
        std::vector<bool> ans;
        ans.reserve(queries.size());
        
        for (const std::string& q : queries) {
            if (q[0] == 'u') {
                int space1 = q.find(' ');
                int space2 = q.find(' ', space1 + 1);
                int u = std::stoi(q.substr(space1 + 1, space2 - space1 - 1));
                char new_c = q.back();
                
                char old_c = s[u];
                if (old_c != new_c) {
                    int diff = (1 << (old_c - 'a')) ^ (1 << (new_c - 'a'));
                    s[u] = new_c;
                    add(in[u], diff);
                    add(out[u] + 1, diff);
                }
            } else {
                int space1 = q.find(' ');
                int space2 = q.find(' ', space1 + 1);
                int u = std::stoi(q.substr(space1 + 1, space2 - space1 - 1));
                int v = std::stoi(q.substr(space2 + 1));
                
                int lca = get_lca(u, v);
                int x_u = query(in[u]);
                int x_v = query(in[v]);
                int path_xor = x_u ^ x_v ^ (1 << (s[lca] - 'a'));
                
                ans.push_back(__builtin_popcount(path_xor) <= 1);
            }
        }
        
        return ans;
    }
};