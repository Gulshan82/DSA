#include <vector>
#include <algorithm>

class Solution {
public:
    int largestOverlap(std::vector<std::vector<int>>& img1, std::vector<std::vector<int>>& img2) {
        int n = img1.size();
        std::vector<std::pair<int, int>> ones1, ones2;
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (img1[r][c] == 1) ones1.push_back({r, c});
                if (img2[r][c] == 1) ones2.push_back({r, c});
            }
        }
        
        std::vector<std::vector<int>> count(2 * n + 1, std::vector<int>(2 * n + 1, 0));
        int max_overlap = 0;
        
        for (auto& p1 : ones1) {
            for (auto& p2 : ones2) {
                int dr = p2.first - p1.first + n;
                int dc = p2.second - p1.second + n;
                count[dr][dc]++;
                max_overlap = std::max(max_overlap, count[dr][dc]);
            }
        }
        
        return max_overlap;
    }
};