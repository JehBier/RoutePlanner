#include "RoutePlanner.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// ==========================================
// FILE LOADING LOGIC
// ==========================================

// Reading shuttles dynamically from a specified text file path
bool RoutePlanner::loadShuttles(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;

    totalShuttles.clear(); 
    std::string id, cp, time;
    while (file >> id >> cp >> time) {
        totalShuttles.emplace_back(id, cp, time);
    }
    file.close();
    return true;
}

// Reading passengers dynamically from a specified text file path
bool RoutePlanner::loadPassengers(const std::string& filePath) {
    std::ifstream file(filePath); 
    if (!file.is_open()) return false;

    totalPassengers.clear();
    std::string name, dest, time;
    while (file >> name >> dest >> time) {
        totalPassengers.emplace_back(name, dest, time);
    }
    file.close();
    return true;
}

// ==========================================
// CORE MATCHMAKING ALGORITHM
// ==========================================

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

// ==========================================
// SHUTTLE CRUD OPERATIONS
// ==========================================

void RoutePlanner::addShuttle(const Shuttle& s) {
    totalShuttles.push_back(s);
}

bool RoutePlanner::editShuttle(const std::string& id, const std::string& newTime, const std::string& newChargingPoint) {
    // Aligned perfectly with your getShuttleID() function from Shuttle.h
    auto it = std::find_if(totalShuttles.begin(), totalShuttles.end(), [&](const Shuttle& s) {
        return s.getShuttleID() == id; 
    });

    if (it != totalShuttles.end()) {
        it->setDispatchTime(newTime);
        it->setTargetChargingPoint(newChargingPoint);
        return true; 
    }
    return false; 
}

bool RoutePlanner::deleteShuttle(const std::string& id) {
    auto originalSize = totalShuttles.size();
    
    // Aligned perfectly with your getShuttleID() function from Shuttle.h
    totalShuttles.erase(
        std::remove_if(totalShuttles.begin(), totalShuttles.end(), [&](const Shuttle& s) {
            return s.getShuttleID() == id;
        }), 
        totalShuttles.end()
    );

    return totalShuttles.size() < originalSize; 
}

// ==========================================
// PASSENGER CRUD OPERATIONS
// ==========================================

void RoutePlanner::addPassenger(const Passenger& p) {
    totalPassengers.push_back(p);
}

bool RoutePlanner::editPassenger(const std::string& id, const std::string& newDestination, const std::string& newTime) {
    auto it = std::find_if(totalPassengers.begin(), totalPassengers.end(), [&](const Passenger& p) {
        return p.getName() == id; // <--- Changed to getName()
    });

    if (it != totalPassengers.end()) {
        it->setDestination(newDestination);
        it->setRequestTime(newTime);
        return true;
    }
    return false;
}

bool RoutePlanner::deletePassenger(const std::string& id) {
    auto originalSize = totalPassengers.size();
    
    totalPassengers.erase(
        std::remove_if(totalPassengers.begin(), totalPassengers.end(), [&](const Passenger& p) {
            return p.getName() == id; // <--- Changed to getName()
        }), 
        totalPassengers.end()
    );

    return totalPassengers.size() < originalSize;
}

// ==========================================
// OUTPUT / PERSISTENCE LOGIC
// ==========================================

bool RoutePlanner::saveSchedule() {
    std::ofstream file("Records/Log.txt");
    if (!file.is_open()) return false;

    file << "==================================================\n";
    file << "        AUTOMATED ROUTE PLANNER SYSTEM LOG       \n";
    file << "==================================================\n";
    for (const auto& item : activeSchedule) {
        file << item.getLogLine() << "\n";
    }
    file.close();
    return true;
}

// ==========================================
// GETTER METHODS FOR DATA RECONCILIATION
// ==========================================

const std::vector<Shuttle>& RoutePlanner::getShuttles() const { return totalShuttles; }
const std::vector<Passenger>& RoutePlanner::getPassengers() const { return totalPassengers; }
const std::vector<Schedule>& RoutePlanner::getSchedule() const { return activeSchedule; }