// computer_club.h
#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include "time_utils.h"
#include <sstream>

class ComputerClub {
public:
    ComputerClub(int numTables, Time startTime, Time endTime, int hourlyRate);
    void processEvent(const std::string& line);
    void generateEndOfDayEvents();
    void printStatistics();
    std::string getOutput();
private:
    int numTables;
    Time startTime;
    Time endTime;
    int hourlyRate;

    std::map<std::string, int> clientStatus;
    std::vector<int> tableStatus; 
    std::queue<std::string> waitingQueue;
    std::map<std::string, Time> clientArrivalTime;
    std::map<std::string, int> clientTable; 
    std::vector<std::pair<std::string, Time>> events;
    std::vector<int> tableRevenue;
    std::vector<int> tableUsage;

    std::stringstream outputStream; 

    void handleClientArrives(const Time& eventTime, const std::string& clientName);
    void handleClientSitsAtTable(const Time& eventTime, const std::string& clientName, int tableNumber);
    void handleClientWaits(const Time& eventTime, const std::string& clientName);
    void handleClientLeaves(const Time& eventTime, const std::string& clientName);
    void generateClientLeavesEvent(const std::string& clientName);
};

#endif // COMPUTER_CLUB_H
