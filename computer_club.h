// computer_club.h
#ifndef COMPUTER_CLUB_H
#define COMPUTER_CLUB_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include "time_utils.h"
#include <sstream> // Added to include stringstream

class ComputerClub {
public:
    ComputerClub(int numTables, Time startTime, Time endTime, int hourlyRate);
    void processEvent(const std::string& line);
    void generateEndOfDayEvents();
    void printStatistics();
    std::string getOutput(); // Added to get the output string
private:
    int numTables;
    Time startTime;
    Time endTime;
    int hourlyRate;

    std::map<std::string, int> clientStatus; // 0 - in club, >0 - sitting at table, -1 - waiting
    std::vector<int> tableStatus; // 0 - free, 1 - occupied
    std::queue<std::string> waitingQueue;
    std::map<std::string, Time> clientArrivalTime;
    std::map<std::string, int> clientTable; // Table number client is sitting at, if applicable.
    std::vector<std::pair<std::string, Time>> events;
    std::vector<int> tableRevenue;
    std::vector<int> tableUsage;

    std::stringstream outputStream; // Use stringstream for output

    void handleClientArrives(const Time& eventTime, const std::string& clientName);
    void handleClientSitsAtTable(const Time& eventTime, const std::string& clientName, int tableNumber);
    void handleClientWaits(const Time& eventTime, const std::string& clientName);
    void handleClientLeaves(const Time& eventTime, const std::string& clientName);
    void generateClientLeavesEvent(const std::string& clientName);
};

#endif // COMPUTER_CLUB_H
