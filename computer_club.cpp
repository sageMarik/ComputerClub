#include "computer_club.h"
#include <iostream>
#include <sstream>
#include <algorithm>

ComputerClub::ComputerClub(int numTables, Time startTime, Time endTime, int hourlyRate)
    : numTables(numTables), startTime(startTime), endTime(endTime), hourlyRate(hourlyRate),
    tableStatus(numTables + 1, 0), tableRevenue(numTables + 1, 0), tableUsage(numTables + 1, 0)
{
}

void ComputerClub::processEvent(const std::string& line) {
    std::stringstream eventStream(line);
    std::string timeStr;
    int eventId;
    std::string clientName;

    if (!(eventStream >> timeStr >> eventId >> clientName)) {
        std::cerr << "Error parsing event: " << line << std::endl;
        return;
    }

    Time eventTime = parseTime(timeStr);
    events.push_back({line, eventTime});
    outputStream << line << std::endl;

    switch (eventId) {
    case 1: { 
        handleClientArrives(eventTime, clientName);
        break;
    }
    case 2: { 
        int tableNumber;
        if (!(eventStream >> tableNumber)) {
            std::cerr << "Error parsing table number" << std::endl;
            return;
        }
        handleClientSitsAtTable(eventTime, clientName, tableNumber);
        break;
    }
    case 3: { 
        handleClientWaits(eventTime, clientName);
        break;
    }
    case 4: { 
        handleClientLeaves(eventTime, clientName);
        break;
    }
    default:
        std::cerr << "Unknown event ID: " << eventId << std::endl;
        break;
    }
}

void ComputerClub::handleClientArrives(const Time& eventTime, const std::string& clientName) {
    if (isTimeBefore(eventTime, startTime)) {
        Time now = eventTime;
        outputStream << formatTime(now) << " 13 NotOpenYet" << std::endl;
    } else if (clientStatus.count(clientName)) {
        Time now = eventTime;
        outputStream << formatTime(now) << " 13 YouShallNotPass" << std::endl;
    } else {
        clientStatus[clientName] = 0;
        clientArrivalTime[clientName] = eventTime;
    }
}

void ComputerClub::handleClientSitsAtTable(const Time& eventTime, const std::string& clientName, int tableNumber) {
    if (!clientStatus.count(clientName)) {
        Time now = eventTime;
        outputStream << formatTime(now) << " 13 ClientUnknown" << std::endl;
    } else if (tableStatus[tableNumber] == 1) {
        Time now = eventTime;
        outputStream << formatTime(now) << " 13 PlaceIsBusy" << std::endl;
    } else {
        if (clientStatus[clientName] > 0) {
            int prevTable = clientStatus[clientName];
            tableStatus[prevTable] = 0;
            int minutesSpent = timeDiffInMinutes(clientArrivalTime[clientName], eventTime);
            int hoursSpent = (minutesSpent + 59) / 60;
            tableRevenue[prevTable] += hoursSpent * hourlyRate;
            tableUsage[prevTable] += minutesSpent;

            clientStatus[clientName] = 0; 
            clientTable.erase(clientName);
        }
        clientStatus[clientName] = tableNumber;
        tableStatus[tableNumber] = 1;
        clientTable[clientName] = tableNumber;
        clientArrivalTime[clientName] = eventTime;
    }
}

void ComputerClub::handleClientWaits(const Time& eventTime, const std::string& clientName) {
    if (!clientStatus.count(clientName)) {
        Time now = eventTime;
        outputStream << formatTime(now) << " 13 ClientUnknown" << std::endl;
    } else {
        bool hasFreeTable = false;
        for (int i = 1; i <= numTables; ++i) {
            if (tableStatus[i] == 0) {
                hasFreeTable = true;
                break;
            }
        }
        if (hasFreeTable) {
            Time now = eventTime;
            outputStream << formatTime(now) << " 13 ICanWaitNoLonger!" << std::endl;
        } else if (waitingQueue.size() >= numTables) {
            Time now = eventTime;
            outputStream << formatTime(now) << " 11 " << clientName << std::endl;
            clientStatus.erase(clientName);
            clientArrivalTime.erase(clientName);
        } else {
            waitingQueue.push(clientName);
            clientStatus[clientName] = -1;
        }
    }
}

void ComputerClub::handleClientLeaves(const Time& eventTime, const std::string& clientName) {
    if (!clientStatus.count(clientName)) {
        Time now = eventTime;
        outputStream << formatTime(now) << " 13 ClientUnknown" << std::endl;
    } else {
        int tableNumber = clientStatus[clientName];
        if (tableNumber > 0) {
            tableStatus[tableNumber] = 0;
            int minutesSpent = timeDiffInMinutes(clientArrivalTime[clientName], eventTime);
            int hoursSpent = (minutesSpent + 59) / 60;
            tableRevenue[tableNumber] += hoursSpent * hourlyRate;
            tableUsage[tableNumber] += minutesSpent;
        }

        clientStatus.erase(clientName);
        clientArrivalTime.erase(clientName);
        clientTable.erase(clientName);

        if (!waitingQueue.empty()) {
            std::string nextClient = waitingQueue.front();
            waitingQueue.pop();

            int freeTable = 0;
            for (int i = 1; i <= numTables; i++){
                if(tableStatus[i] == 0){
                    freeTable = i;
                    break;
                }
            }

            if(freeTable != 0){
                Time now = eventTime;
                outputStream << formatTime(now) << " 12 " << nextClient << " " << freeTable << std::endl;

                clientStatus[nextClient] = freeTable;
                tableStatus[freeTable] = 1;
                clientArrivalTime[nextClient] = now;
                clientTable[nextClient] = freeTable;
            }

        }
    }
}

void ComputerClub::generateEndOfDayEvents() {
    std::vector<std::string> remainingClients;
    for (auto const& [name, status] : clientStatus) {
        if (status > 0 )
            remainingClients.push_back(name);
    }
    std::sort(remainingClients.begin(), remainingClients.end());

    for (const std::string& clientName : remainingClients) {
        int tableNumber = clientStatus[clientName];
        if(tableNumber > 0){
            tableStatus[tableNumber] = 0;
            int minutesSpent = timeDiffInMinutes(clientArrivalTime[clientName], endTime);
            int hoursSpent = (minutesSpent + 59) / 60;
            tableRevenue[tableNumber] += hoursSpent * hourlyRate;
            tableUsage[tableNumber] += minutesSpent;
        }
    }

    for (const std::string& clientName : remainingClients) {
        outputStream << formatTime(endTime) << " 11 " << clientName << std::endl;
    }
}

void ComputerClub::printStatistics() {
    outputStream << formatTime(endTime) << std::endl;

    for (int i = 1; i <= numTables; ++i) {
        int usageHours = (tableUsage[i] + 59) / 60;
        char buf[6];
        sprintf(buf, "%02d:%02d", (tableUsage[i]/60), (tableUsage[i]%60));
        outputStream << i << " " << tableRevenue[i] << " " << std::string(buf) << " " << std::endl;
    }
}

std::string ComputerClub::getOutput(){
    return outputStream.str();
}
