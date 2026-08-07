class Solution {
    int dp[60][40];
    
    int get_min(int r2, int r3) {
        // Clamp to 0
        r2 = max(0, r2);
        r3 = max(0, r3);
        
        // Base case: both requirements met
        if (r2 == 0 && r3 == 0) return 0;
        
        // Memoization lookup
        if (dp[r2][r3] != -1) return dp[r2][r3];
        
        int res = 1e9;
        
        // Only try 2, 4, 8 if we actually need power of 2
        if (r2 > 0) {
            res = min(res, 1 + get_min(r2 - 1, r3));     // digit 2
            res = min(res, 1 + get_min(r2 - 2, r3));     // digit 4
            res = min(res, 1 + get_min(r2 - 3, r3));     // digit 8
        }
        
        // Only try 3, 9 if we actually need power of 3
        if (r3 > 0) {
            res = min(res, 1 + get_min(r2, r3 - 1));     // digit 3
            res = min(res, 1 + get_min(r2, r3 - 2));     // digit 9
        }
        
        // Digit 6 provides both, safe to call as long as we aren't at (0,0)
        res = min(res, 1 + get_min(r2 - 1, r3 - 1));     // digit 6
        
        return dp[r2][r3] = res;
    }

    struct State {
        int r2, r3, r5, r7;
        
        State apply(int d) const {
            State res = *this;
            if (d == 2) res.r2--;
            else if (d == 3) res.r3--;
            else if (d == 4) res.r2 -= 2;
            else if (d == 5) res.r5--;
            else if (d == 6) { res.r2--; res.r3--; }
            else if (d == 7) res.r7--;
            else if (d == 8) res.r2 -= 3;
            else if (d == 9) res.r3 -= 2;
            
            res.r2 = max(0, res.r2);
            res.r3 = max(0, res.r3);
            res.r5 = max(0, res.r5);
            res.r7 = max(0, res.r7);
            return res;
        }
        
        int min_len(Solution* sol) const {
            return r5 + r7 + sol->get_min(r2, r3);
        }
    };

public:
    string smallestNumber(string num, long long t) {
        long long temp = t;
        State initial = {0, 0, 0, 0};
        
        while (temp % 2 == 0) { initial.r2++; temp /= 2; }
        while (temp % 3 == 0) { initial.r3++; temp /= 3; }
        while (temp % 5 == 0) { initial.r5++; temp /= 5; }
        while (temp % 7 == 0) { initial.r7++; temp /= 7; }
        if (temp > 1) return "-1";
        
        memset(dp, -1, sizeof(dp));
        
        int n = num.length();
        int z_idx = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                z_idx = i;
                break;
            }
        }
        
        vector<State> pref(n + 1);
        pref[0] = initial;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') break;
            pref[i + 1] = pref[i].apply(num[i] - '0');
        }
        
        for (int i = min(n, z_idx); i >= 0; --i) {
            if (i == n) {
                if (pref[n].r2 == 0 && pref[n].r3 == 0 && 
                    pref[n].r5 == 0 && pref[n].r7 == 0) {
                    return num;
                }
                continue;
            }
            
            int start_d = num[i] - '0' + 1;
            for (int d = start_d; d <= 9; ++d) {
                State st = pref[i].apply(d);
                int avail = n - 1 - i;
                
                if (st.min_len(this) <= avail) {
                    string ans = num.substr(0, i);
                    ans.push_back(d + '0');
                    
                    for (int k = 0; k < avail; ++k) {
                        for (int nxt = 1; nxt <= 9; ++nxt) {
                            State nxt_st = st.apply(nxt);
                            if (nxt_st.min_len(this) <= avail - 1 - k) {
                                ans.push_back(nxt + '0');
                                st = nxt_st;
                                break;
                            }
                        }
                    }
                    return ans;
                }
            }
        }
        
        int req_len = initial.min_len(this);
        int final_len = max(n + 1, req_len);
        string ans = "";
        State st = initial;
        
        for (int k = 0; k < final_len; ++k) {
            for (int nxt = 1; nxt <= 9; ++nxt) {
                State nxt_st = st.apply(nxt);
                if (nxt_st.min_len(this) <= final_len - 1 - k) {
                    ans.push_back(nxt + '0');
                    st = nxt_st;
                    break;
                }
            }
        }
        
        return ans;
    }
};