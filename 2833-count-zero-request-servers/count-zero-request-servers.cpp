#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <algorithm>
#include <numeric>

class Solution {
public:
    std::vector<int> countServers(int n, std::vector<std::vector<int>>& logs, int x, std::vector<int>& queries) {
        int num_queries = queries.size();
        std::vector<int> q_indices(num_queries);
        std::iota(q_indices.begin(), q_indices.end(), 0);
        
        std::sort(q_indices.begin(), q_indices.end(), [&](int a, int b) {
            return queries[a] < queries[b];
        });
        
        std::sort(logs.begin(), logs.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[1] < b[1];
        });
        
        std::vector<int> ans(num_queries);
        std::vector<int> counts(n + 1, 0);
        int active_servers = 0;
        
        int left = 0;
        int right = 0;
        int num_logs = logs.size();
        
        for (int i = 0; i < num_queries; ++i) {
            int q_idx = q_indices[i];
            int end_time = queries[q_idx];
            int start_time = end_time - x;
            
            while (right < num_logs && logs[right][1] <= end_time) {
                int server_id = logs[right][0];
                if (counts[server_id] == 0) {
                    active_servers++;
                }
                counts[server_id]++;
                right++;
            }
            
            while (left < num_logs && logs[left][1] < start_time) {
                int server_id = logs[left][0];
                counts[server_id]--;
                if (counts[server_id] == 0) {
                    active_servers--;
                }
                left++;
            }
            
            ans[q_idx] = n - active_servers;
        }
        
        return ans;
    }
};