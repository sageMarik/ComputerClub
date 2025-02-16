#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "computer_club.h"
#include "time_utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: task.exe <input_file>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    ifstream file(inputFile);

    if (!file.is_open()) {
        cerr << "Error opening file: " << inputFile << endl;
        return 1;
    }

    int numTables;
    Time startTime, endTime;
    int hourlyRate;

    string line;
    if (!getline(file, line)) {
        cerr << "Error reading number of tables" << endl;
        return 1;
    }
    try {
        numTables = stoi(line);
    } catch (const invalid_argument& e) {
        cerr << "Error parsing number of tables" << endl;
        return 1;
    }

    if (!getline(file, line)) {
        cerr << "Error reading start and end times" << endl;
        return 1;
    }
    stringstream timeStream(line);
    string startTimeStr, endTimeStr;
    if (!(timeStream >> startTimeStr >> endTimeStr)) {
        cerr << "Error parsing start and end times" << endl;
        return 1;
    }
    startTime = parseTime(startTimeStr);
    endTime = parseTime(endTimeStr);

    if (!getline(file, line)) {
        cerr << "Error reading hourly rate" << endl;
        return 1;
    }
    try {
        hourlyRate = stoi(line);
    } catch (const invalid_argument& e) {
        cerr << "Error parsing hourly rate" << endl;
        return 1;
    }

    ComputerClub club(numTables, startTime, endTime, hourlyRate);

    cout << formatTime(startTime) << endl; 

    while (getline(file, line)) {
        club.processEvent(line);
    }

    club.generateEndOfDayEvents();
    club.printStatistics();
    cout << club.getOutput();
    file.close();
    return 0;
}
