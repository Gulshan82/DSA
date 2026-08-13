class Solution {
    struct Node {
        int max_len;
        int pref_len;
        char pref_char;
        int suff_len;
        char suff_char;
        int len;
    };
    
    vector<Node> tree;
    
    Node merge(const Node& l, const Node& r) {
        Node res;
        res.len = l.len + r.len;
        res.pref_char = l.pref_char;
        res.suff_char = r.suff_char;
        
        res.pref_len = l.pref_len;
        if (l.pref_len == l.len && l.pref_char == r.pref_char) {
            res.pref_len += r.pref_len;
        }
        
        res.suff_len = r.suff_len;
        if (r.suff_len == r.len && r.suff_char == l.suff_char) {
            res.suff_len += l.suff_len;
        }
        
        res.max_len = max(l.max_len, r.max_len);
        if (l.suff_char == r.pref_char) {
            res.max_len = max(res.max_len, l.suff_len + r.pref_len);
        }
        return res;
    }
    
    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node] = {1, 1, s[start], 1, s[start], 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, s);
        build(2 * node + 1, mid + 1, end, s);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
    
    void update(int node, int start, int end, int idx, char c) {
        if (start == end) {
            tree[node] = {1, 1, c, 1, c, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, c);
        } else {
            update(2 * node + 1, mid + 1, end, idx, c);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
    
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        tree.resize(4 * n);
        build(1, 0, n - 1, s);
        
        int k = queryCharacters.length();
        vector<int> ans(k);
        
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans[i] = tree[1].max_len;
        }
        
        return ans;
    }
};