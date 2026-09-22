class Solution {
    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int k;
    vector<Node> tree;

    Node merge(Node &a, Node &b) {
        Node res;

        // Product of whole segment
        res.prod = (a.prod * b.prod) % k;

        // Prefixes completely inside left segment
        for (int r = 0; r < k; r++) {
            res.cnt[r] += a.cnt[r];
        }

        // Prefixes that cross into right segment
        for (int r = 0; r < k; r++) {
            int newRem = (a.prod * r) % k;
            res.cnt[newRem] += b.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % k;

            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    void update(int node, int l, int r,
                int idx, int value) {

        if (l == r) {
            int rem = value % k;

            tree[node] = Node();
            tree[node].prod = rem;
            tree[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, value);
        } else {
            update(node * 2 + 1, mid + 1, r,
                   idx, value);
        }

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    Node query(int node, int l, int r,
               int ql, int qr) {

        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        if (qr <= mid) {
            return query(node * 2, l, mid,
                         ql, qr);
        }

        if (ql > mid) {
            return query(node * 2 + 1,
                         mid + 1, r,
                         ql, qr);
        }

        Node left = query(node * 2,
                          l, mid,
                          ql, qr);

        Node right = query(node * 2 + 1,
                           mid + 1, r,
                           ql, qr);

        return merge(left, right);
    }

public:
    vector<int> resultArray(vector<int>& nums,
                            int K,
                            vector<vector<int>>& queries) {

        k = K;

        int n = nums.size();

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1,
                   index, value);

            // Query [start ... n-1]
            Node res = query(1, 0, n - 1,
                             start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};