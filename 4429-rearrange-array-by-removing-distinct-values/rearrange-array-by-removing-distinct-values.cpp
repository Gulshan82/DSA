#include <vector>
#include <map>

class Solution {
public:
    std::vector<int> rearrangeArray(std::vector<int>& nums) {
        std::map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        std::vector<int> ans;
        while (!freq.empty()) {
            auto it = freq.begin();
            while (it != freq.end()) {
                ans.push_back(it->first);
                it->second--;
                if (it->second == 0) {
                    it = freq.erase(it);
                } else {
                    ++it;
                }
            }
        }
        
        return ans;
    }
};