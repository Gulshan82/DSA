#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Group {
        int start;
        int len;
    };

    struct SparseTable {
        vector<vector<int>> st;
        vector<int> lg;

        SparseTable(const vector<int>& a) {
            int n = a.size();

            lg.resize(n + 1);

            for (int i = 2; i <= n; i++) {
                lg[i] = lg[i / 2] + 1;
            }

            st.resize(lg[n] + 1);
            st[0] = a;

            for (int k = 1; k <= lg[n]; k++) {
                int len = 1 << k;
                int half = len >> 1;

                st[k].resize(n - len + 1);

                for (int i = 0; i + len <= n; i++) {
                    st[k][i] = max(
                        st[k - 1][i],
                        st[k - 1][i + half]
                    );
                }
            }
        }

        int query(int l, int r) {
            if (l > r)
                return 0;

            int k = lg[r - l + 1];

            return max(
                st[k][l],
                st[k][r - (1 << k) + 1]
            );
        }
    };

public:
    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries
    ) {
        int n = s.size();

        // Total 1s in the WHOLE string.
        int ones = count(s.begin(), s.end(), '1');

        // --------------------------------------------------
        // Build zero groups.
        // --------------------------------------------------

        vector<Group> groups;

        /*
            zeroGroupIndex[i] = index of the last zero group
            that has started at or before i.

            Example:

                s = 110001001

                zeroGroupIndex:
                    -1 -1  0  0  0  1  1  1  1

            Notice that for a '1', we keep the previous
            zero-group index.
        */
        vector<int> zeroGroupIndex(n);

        int lastGroup = -1;

        for (int i = 0; i < n; i++) {

            if (s[i] == '0') {

                if (i > 0 && s[i - 1] == '0') {
                    groups.back().len++;
                } else {
                    groups.push_back({i, 1});
                    lastGroup++;
                }
            }

            zeroGroupIndex[i] = lastGroup;
        }

        // Fewer than two zero groups => no trade possible.
        if (groups.size() < 2) {
            return vector<int>(queries.size(), ones);
        }

        // --------------------------------------------------
        // merge[i] =
        // length of zero group i + zero group i+1
        // --------------------------------------------------

        vector<int> merge(groups.size() - 1);

        for (int i = 1; i < (int)groups.size(); i++) {
            merge[i - 1] =
                groups[i - 1].len +
                groups[i].len;
        }

        SparseTable st(merge);

        vector<int> answer;

        // --------------------------------------------------
        // Process queries.
        // --------------------------------------------------

        for (auto &q : queries) {

            int l = q[0];
            int r = q[1];

            /*
                lIndex = zero group immediately before/at l.

                If s[l] == '0':
                    lIndex = its own zero group.

                If s[l] == '1':
                    lIndex = previous zero group.
            */
            int lIndex = zeroGroupIndex[l];

            int left = -1;

            if (lIndex != -1) {
                left =
                    groups[lIndex].start +
                    groups[lIndex].len -
                    l;
            }

            /*
                rIndex = zero group immediately before/at r.
            */
            int rIndex = zeroGroupIndex[r];

            int right = -1;

            if (rIndex != -1) {
                right =
                    r -
                    groups[rIndex].start +
                    1;
            }

            /*
                The first zero group that can be used as a
                COMPLETE group after the left boundary.

                If l is inside a zero group, that group is
                only partially available, so skip it.

                If l is a '1', the next zero group is the
                first usable one.
            */
            int startGroupIndex = lIndex + 1;

            /*
                Last complete zero group.

                If r is inside a zero group, that group is
                partial, so exclude it.

                If r is a '1', the zero group before it is
                completely available.
            */
            int endGroupIndex =
                (s[r] == '0')
                    ? rIndex - 1
                    : rIndex;

            int best = ones;

            // ------------------------------------------------
            // Case 1:
            // Both endpoints are inside zero groups and
            // they are consecutive zero groups.
            //
            // Example:
            //
            //  000  1  00
            //  left     right
            //
            // We can merge the partial pieces.
            // ------------------------------------------------

            if (s[l] == '0' &&
                s[r] == '0' &&
                startGroupIndex == rIndex) {

                best = max(
                    best,
                    ones + left + right
                );
            }

            // ------------------------------------------------
            // Case 2:
            // Two complete zero groups somewhere inside
            // the query.
            //
            // merge[i] represents groups i and i+1.
            // ------------------------------------------------

            else if (startGroupIndex <= endGroupIndex - 1) {

                int bestMerge =
                    st.query(
                        startGroupIndex,
                        endGroupIndex - 1
                    );

                best = max(
                    best,
                    ones + bestMerge
                );
            }

            // ------------------------------------------------
            // Case 3:
            // Partial left zero group + next complete group.
            // ------------------------------------------------

            if (s[l] == '0' &&
                startGroupIndex <= endGroupIndex) {

                int nextGroup =
                    startGroupIndex;

                best = max(
                    best,
                    ones +
                    left +
                    groups[nextGroup].len
                );
            }

            // ------------------------------------------------
            // Case 4:
            // Previous complete group + partial right group.
            // ------------------------------------------------

            if (s[r] == '0' &&
                startGroupIndex <= endGroupIndex) {

                int prevGroup =
                    endGroupIndex;

                best = max(
                    best,
                    ones +
                    right +
                    groups[prevGroup].len
                );
            }

            answer.push_back(best);
        }

        return answer;
    }
};