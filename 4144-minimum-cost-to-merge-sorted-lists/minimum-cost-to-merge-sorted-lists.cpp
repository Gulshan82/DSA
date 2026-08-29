class Solution {
public:
    long long minMergeCost(vector<vector<int>>& lists) {
        int n = lists.size();
        int total = 1 << n;

        vector<vector<int>> merged(total);
        vector<int> len(total);
        vector<long long> median(total);

        // Build merged sorted array for every subset
        for (int mask = 1; mask < total; mask++) {
            int bit = __builtin_ctz(mask);
            int prev = mask ^ (1 << bit);

            vector<int>& a = merged[prev];
            vector<int>& b = lists[bit];

            int i = 0, j = 0;

            while (i < a.size() && j < b.size()) {
                if (a[i] <= b[j])
                    merged[mask].push_back(a[i++]);
                else
                    merged[mask].push_back(b[j++]);
            }

            while (i < a.size())
                merged[mask].push_back(a[i++]);

            while (j < b.size())
                merged[mask].push_back(b[j++]);

            len[mask] = merged[mask].size();

            // Left middle element
            median[mask] = merged[mask][(len[mask] - 1) / 2];
        }

        const long long INF = 4e18;

        vector<long long> dp(total, INF);

        // A single list needs no merge
        for (int i = 0; i < n; i++) {
            dp[1 << i] = 0;
        }

        // DP over all subsets
        for (int mask = 1; mask < total; mask++) {

            // Single list
            if ((mask & (mask - 1)) == 0)
                continue;

            // Try every partition
            for (int sub = (mask - 1) & mask;
                 sub;
                 sub = (sub - 1) & mask) {

                int other = mask ^ sub;

                // Avoid checking A+B and B+A
                if (sub > other)
                    continue;

                long long cost =
                    dp[sub] +
                    dp[other] +
                    len[sub] +
                    len[other] +
                    llabs(median[sub] - median[other]);

                dp[mask] = min(dp[mask], cost);
            }
        }

        return dp[total - 1];
    }
};