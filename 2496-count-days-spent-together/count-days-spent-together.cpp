#include <string>
#include <vector>
#include <algorithm>

class Solution {
    int dateToDay(const std::string& date) {
        std::vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int month = std::stoi(date.substr(0, 2));
        int day = std::stoi(date.substr(3, 2));
        
        int total_days = 0;
        for (int i = 0; i < month - 1; ++i) {
            total_days += days_in_month[i];
        }
        total_days += day;
        
        return total_days;
    }

public:
    int countDaysTogether(std::string arriveAlice, std::string leaveAlice, std::string arriveBob, std::string leaveBob) {
        int arriveA = dateToDay(arriveAlice);
        int leaveA = dateToDay(leaveAlice);
        int arriveB = dateToDay(arriveBob);
        int leaveB = dateToDay(leaveBob);
        
        int overlap_start = std::max(arriveA, arriveB);
        int overlap_end = std::min(leaveA, leaveB);
        
        return std::max(0, overlap_end - overlap_start + 1);
    }
};