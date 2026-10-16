#include <vector>
#include <unordered_map>

class Solution {
    long long mod = 1e9 + 7;
    
    struct Node {
        long long sum_a = 0;
        long long sum_sq = 0;
        long long lazy = 0;
    };
    
    std::vector<Node> tree;

    void push_down(int node, int start, int end) {
        if (tree[node].lazy != 0) {
            int mid = start + (end - start) / 2;
            long long v = tree[node].lazy;
            
            long long len_left = mid - start + 1;
            tree[2 * node].sum_sq = (tree[2 * node].sum_sq + 2 * v * tree[2 * node].sum_a + v * v % mod * len_left) % mod;
            tree[2 * node].sum_a = (tree[2 * node].sum_a + v * len_left) % mod;
            tree[2 * node].lazy = (tree[2 * node].lazy + v) % mod;

            long long len_right = end - mid;
            tree[2 * node + 1].sum_sq = (tree[2 * node + 1].sum_sq + 2 * v * tree[2 * node + 1].sum_a + v * v % mod * len_right) % mod;
            tree[2 * node + 1].sum_a = (tree[2 * node + 1].sum_a + v * len_right) % mod;
            tree[2 * node + 1].lazy = (tree[2 * node + 1].lazy + v) % mod;

            tree[node].lazy = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, long long v) {
        if (start > end || start > r || end < l) return;
        
        if (start >= l && end <= r) {
            long long len = end - start + 1;
            tree[node].sum_sq = (tree[node].sum_sq + 2 * v * tree[node].sum_a + v * v % mod * len) % mod;
            tree[node].sum_a = (tree[node].sum_a + v * len) % mod;
            tree[node].lazy = (tree[node].lazy + v) % mod;
            return;
        }
        
        push_down(node, start, end);
        int mid = start + (end - start) / 2;
        update(2 * node, start, mid, l, r, v);
        update(2 * node + 1, mid + 1, end, l, r, v);
        
        tree[node].sum_a = (tree[2 * node].sum_a + tree[2 * node + 1].sum_a) % mod;
        tree[node].sum_sq = (tree[2 * node].sum_sq + tree[2 * node + 1].sum_sq) % mod;
    }

public:
    int sumCounts(std::vector<int>& nums) {
        int n = nums.size();
        tree.assign(4 * n + 1, Node());
        std::unordered_map<int, int> last_seen;
        long long ans = 0;

        for (int i = 0; i < n; ++i) {
            int l = last_seen.count(nums[i]) ? last_seen[nums[i]] + 1 : 0;
            
            // Update the segment tree for range [l, i]
            update(1, 0, n - 1, l, i, 1);
            
            // Add the current total sum of squares to the answer
            ans = (ans + tree[1].sum_sq) % mod;
            
            last_seen[nums[i]] = i;
        }

        return ans;
    }
};