#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

class Solution {
public:
    std::vector<int> busiestServers(int k, std::vector<int>& arrival, std::vector<int>& load) {
        std::set<int> available;
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }
        
        std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> busy;
        std::vector<int> count(k, 0);
        
        int n = arrival.size();
        for (int i = 0; i < n; ++i) {
            long long arr_time = arrival[i];
            long long duration = load[i];
            
            while (!busy.empty() && busy.top().first <= arr_time) {
                available.insert(busy.top().second);
                busy.pop();
            }
            
            if (available.empty()) {
                continue;
            }
            
            auto it = available.lower_bound(i % k);
            if (it == available.end()) {
                it = available.begin();
            }
            
            int server = *it;
            count[server]++;
            available.erase(it);
            busy.push({arr_time + duration, server});
        }
        
        int max_req = *std::max_element(count.begin(), count.end());
        std::vector<int> ans;
        for (int i = 0; i < k; ++i) {
            if (count[i] == max_req) {
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};