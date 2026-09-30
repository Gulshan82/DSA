#include <string>
#include <vector>

class Solution {
public:
    std::vector<int> maxDepthAfterSplit(std::string seq) {
        std::vector<int> result(seq.length());
        int depth = 0;
        
        for (int i = 0; i < seq.length(); ++i) {
            if (seq[i] == '(') {
                depth++;
                result[i] = depth % 2;
            } else {
                result[i] = depth % 2;
                depth--;
            }
        }
        
        return result;
    }
};