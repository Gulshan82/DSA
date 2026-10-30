#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <string>
#include <queue>
#include <tuple>

class Solution {
public:
    int shortestPath(int n, std::vector<std::vector<int>>& edges, std::string labels, int k) {
        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        std::vector<std::vector<long long>> dist(n, std::vector<long long>(k + 1, -1));
        std::priority_queue<std::tuple<long long, int, int>, std::vector<std::tuple<long long, int, int>>, std::greater<>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, c] = pq.top();
            pq.pop();

            if (d > dist[u][c]) continue;
            if (u == n - 1) return d;

            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                long long w = neighbor.second;
                
                int next_c;
                if (labels[u] == labels[v]) {
                    next_c = c + 1;
                } else {
                    next_c = 1;
                }

                if (next_c <= k) {
                    if (dist[v][next_c] == -1 || d + w < dist[v][next_c]) {
                        dist[v][next_c] = d + w;
                        pq.push({d + w, v, next_c});
                    }
                }
            }
        }

        long long ans = -1;
        for (int i = 1; i <= k; ++i) {
            if (dist[n - 1][i] != -1) {
                if (ans == -1 || dist[n - 1][i] < ans) {
                    ans = dist[n - 1][i];
                }
            }
        }

        return ans;
    }
};