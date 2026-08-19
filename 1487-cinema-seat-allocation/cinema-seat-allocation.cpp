class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> reserved;
        
        for (const auto& seat : reservedSeats) {
            reserved[seat[0]] |= (1 << seat[1]);
        }
        
        int ans = (n - reserved.size()) * 2;
        
        for (auto const& [row, mask] : reserved) {
            bool left = !(mask & 60);
            bool right = !(mask & 960);
            bool mid = !(mask & 240);
            
            if (left && right) {
                ans += 2;
            } else if (left || right || mid) {
                ans += 1;
            }
        }
        
        return ans;
    }
};