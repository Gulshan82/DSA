#include <string>

class Solution {
public:
    bool checkString(std::string s) {
        return s.find("ba") == std::string::npos;
    }
};