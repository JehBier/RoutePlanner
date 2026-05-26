#include "RoutePlanner.h"
#include <fstream>
#include <iostream>

//reading shuttle
bool RoutePlanner::loadShuttles() {
    std::ifstream file("Records/Shuttle.txt");
    if (!file.is_open()) return false;

    totalShuttles.clear(); 
    std::string id, cp, time;
    while (file >> id >> cp >> time) {
        totalShuttles.emplace_back(id, cp, time);
    }
    file.close();
    return true;
}

//reading passenger
bool RoutePlanner::loadPassengers() {
    std::ifstream file("Records/Passenger.txt"); 
    if (!file.is_open()) return false;

    totalPassengers.clear();
    std::string name, dest, time;
    while (file >> name >> dest >> time) {
        totalPassengers.emplace_back(name, dest, time);
    }
    file.close();
    return true;
}

//matchmake algo
void RoutePlanner::generateSchedule() {
    activeSchedule.clear();

    for (auto& s : totalShuttles) s.setIsOccupied(false);
    for (auto& p : totalPassengers) p.setIsMatched(false);

    for (auto& passenger : totalPassengers) {
        for (auto& shuttle : totalShuttles) {
            if (!shuttle.getIsOccupied() && 
                shuttle.getTargetChargingPoint() == passenger.getDestination() && 
                shuttle.getDispatchTime() == passenger.getRequestTime()) {
                
                shuttle.setIsOccupied(true);
                passenger.setIsMatched(true);
                
                activeSchedule.emplace_back(shuttle, passenger); 
                break; 
            }
        }
    }
}

//write into log
bool RoutePlanner::saveSchedule() {
    std::ofstream file("Records/Log.txt");
    if (!file.is_open()) return false;

    file << "==================================================\n";
    file << "         AUTOMATED ROUTE PLANNER SYSTEM LOG       \n";
    file << "==================================================\n";
    for (const auto& item : activeSchedule) {
        file << item.getLogLine() << "\n";
    }
    file.close();
    return true;
}

void RoutePlanner::addShuttle(const Shuttle& newShuttle) {
    totalShuttles.push_back(newShuttle);
}
void RoutePlanner::deletePassenger(int index) {
    if (index >= 0 && index < static_cast<int>(totalPassengers.size())) {
        totalPassengers.erase(totalPassengers.begin() + index);
    }
}

//moethods to display 
const std::vector<Shuttle>& RoutePlanner::getShuttles() const { return totalShuttles; }
const std::vector<Passenger>& RoutePlanner::getPassengers() const { return totalPassengers; }
const std::vector<Schedule>& RoutePlanner::getSchedule() const { return activeSchedule; }