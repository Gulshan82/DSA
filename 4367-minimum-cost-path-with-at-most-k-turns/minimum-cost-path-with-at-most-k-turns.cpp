#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <algorithm>

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        
        if (m == 1 && n == 1) return grid[0][0];

        // Practical upper bound on k to avoid MLE if k is arbitrarily large.
        int max_k = std::min(k, m * n * 2);
        
        // dist[r][c][dir][turns]
        // dir: 0=Right, 1=Down, 2=Left, 3=Up, 4=Start
        std::vector<std::vector<std::vector<std::vector<int>>>> dist(
            m, std::vector<std::vector<std::vector<int>>>(
                n, std::vector<std::vector<int>>(
                    5, std::vector<int>(max_k + 1, INT_MAX)
                )
            )
        );

        // min-heap: {cost, r, c, dir, turns}
        std::priority_queue<
            std::tuple<int, int, int, int, int>, 
            std::vector<std::tuple<int, int, int, int, int>>, 
            std::greater<std::tuple<int, int, int, int, int>>
        > pq;

        dist[0][0][4][0] = grid[0][0];
        pq.push({grid[0][0], 0, 0, 4, 0});

        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};

        while (!pq.empty()) {
            auto [cost, r, c, dir, turns] = pq.top();
            pq.pop();

            if (r == m - 1 && c == n - 1) {
                return cost;
            }

            if (cost > dist[r][c][dir][turns]) {
                continue;
            }

            for (int nd = 0; nd < 4; ++nd) {
                int nr = r + dr[nd];
                int nc = c + dc[nd];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int nturns = turns;
                    
                    if (dir != 4 && dir != nd) {
                        nturns++;
                    }
                    
                    if (nturns <= max_k) {
                        int ncost = cost + grid[nr][nc];
                        
                        if (ncost < dist[nr][nc][nd][nturns]) {
                            dist[nr][nc][nd][nturns] = ncost;
                            pq.push({ncost, nr, nc, nd, nturns});
                        }
                    }
                }
            }
        }

        return -1;
    }
};