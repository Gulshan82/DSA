#include <vector>

class Solution {
public:
    int countGroups(std::vector<int>& position, std::vector<int>& speed, int distance) {
        int n = position.size();
        if (n == 0) return 0;
        
        int groups = 0;
        int top = -1;
        
        for (int i = n - 1; i >= 0; --i) {
            if (top == -1) {
                top = i;
                groups++;
            } else {
                if (position[i + 1] - position[i] <= distance || speed[i] > speed[top]) {
                    // Merges with the group represented by 'top'. 
                    // 'top' remains the rightmost robot of this group.
                } else {
                    // Does not merge, forms a new group.
                    top = i;
                    groups++;
                }
            }
        }
        
        return groups;
    }
};