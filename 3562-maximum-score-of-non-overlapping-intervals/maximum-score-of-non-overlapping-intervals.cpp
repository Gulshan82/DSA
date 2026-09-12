#include <vector>
#include <algorithm>

class Solution {
    struct Interval {
        int l, r, w, id;
    };
    
    struct State {
        long long score = -1;
        std::vector<int> ids;
    };

public:
    std::vector<int> maximumWeight(std::vector<std::vector<int>>& intervals) {
        int n = intervals.size();
        std::vector<Interval> A(n);
        for (int i = 0; i < n; ++i) {
            A[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }
        
        std::sort(A.begin(), A.end(), [](const Interval& a, const Interval& b) {
            if (a.l != b.l) return a.l < b.l;
            return a.r < b.r;
        });
        
        std::vector<int> next_j(n);
        for (int i = 0; i < n; ++i) {
            next_j[i] = std::upper_bound(A.begin() + i + 1, A.end(), A[i].r,
                [](int val, const Interval& inter) {
                    return val < inter.l;
                }) - A.begin();
        }
        
        std::vector<std::vector<State>> dp(n + 1, std::vector<State>(5));
        for (int i = 0; i <= n; ++i) {
            dp[i][0].score = 0;
        }
        
        for (int i = n - 1; i >= 0; --i) {
            for (int c = 1; c <= 4; ++c) {
                State best = dp[i + 1][c];
                
                int nxt = next_j[i];
                if (dp[nxt][c - 1].score != -1) {
                    State cand;
                    cand.score = (long long)A[i].w + dp[nxt][c - 1].score;
                    cand.ids = dp[nxt][c - 1].ids;
                    cand.ids.push_back(A[i].id);
                    std::sort(cand.ids.begin(), cand.ids.end());
                    
                    if (cand.score > best.score) {
                        best = cand;
                    } else if (cand.score == best.score) {
                        if (cand.ids < best.ids) {
                            best = cand;
                        }
                    }
                }
                
                dp[i][c] = best;
            }
        }
        
        State best_overall;
        for (int c = 1; c <= 4; ++c) {
            if (dp[0][c].score > best_overall.score) {
                best_overall = dp[0][c];
            } else if (dp[0][c].score == best_overall.score && dp[0][c].score != -1) {
                if (dp[0][c].ids < best_overall.ids) {
                    best_overall = dp[0][c];
                }
            }
        }
        
        return best_overall.ids;
    }
};