class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        vector<int> coords;
        coords.push_back(0);
        for (const auto& q : queries) {
            coords.push_back(q[1]);
        }
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        
        int m = coords.size();
        vector<int> tree(m + 1, 0);
        
        auto get_id = [&](int x) {
            return lower_bound(coords.begin(), coords.end(), x) - coords.begin() + 1;
        };
        
        auto update = [&](int i, int val) {
            for (; i <= m; i += i & -i) {
                tree[i] = max(tree[i], val);
            }
        };
        
        auto query_bit = [&](int i) {
            int mx = 0;
            for (; i > 0; i -= i & -i) {
                mx = max(mx, tree[i]);
            }
            return mx;
        };
        
        set<int> obstacles;
        obstacles.insert(0);
        
        for (const auto& q : queries) {
            if (q[0] == 1) {
                obstacles.insert(q[1]);
            }
        }
        
        int prev = 0;
        for (int x : obstacles) {
            if (x == 0) continue;
            update(get_id(x), x - prev);
            prev = x;
        }
        
        vector<bool> ans;
        for (int i = (int)queries.size() - 1; i >= 0; --i) {
            if (queries[i][0] == 2) {
                int x = queries[i][1];
                int sz = queries[i][2];
                auto it = obstacles.upper_bound(x);
                --it;
                int L = *it;
                int max_gap = max(query_bit(get_id(x)), x - L);
                ans.push_back(max_gap >= sz);
            } else {
                int x = queries[i][1];
                auto it = obstacles.find(x);
                auto prev_it = std::prev(it);
                auto next_it = std::next(it);
                
                if (next_it != obstacles.end()) {
                    update(get_id(*next_it), *next_it - *prev_it);
                }
                obstacles.erase(it);
            }
        }
        
        reverse(ans.begin(), ans.end());
        return ans;
    }
};