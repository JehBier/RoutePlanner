#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <vector>
#include <string>
#include "Shuttle.h"
#include "Passenger.h"

// Assuming your schedule class or struct is named Schedule. 
// If it has a different file name, change this include accordingly!
#include "Schedule.h" 

class RoutePlanner {
private:
    // Only ONE declaration per vector variable
    std::vector<Shuttle> totalShuttles;
    std::vector<Passenger> totalPassengers;
    std::vector<Schedule> activeSchedule; 

public:
    // --- File Loading Logic ---
    bool loadShuttles(const std::string& filePath = "Records/Shuttle.txt");
    bool loadPassengers(const std::string& filePath = "Records/Passenger.txt");
    
    // --- Core Algorithm Logic ---
    void generateSchedule();
    bool saveSchedule();

    // --- Shuttle CRUD ---
    void addShuttle(const Shuttle& s);
    bool editShuttle(const std::string& id, const std::string& newTime, const std::string& newChargingPoint);
    bool deleteShuttle(const std::string& id);

    // --- Passenger CRUD ---
    void addPassenger(const Passenger& p);
    bool editPassenger(const std::string& id, const std::string& newDestination, const std::string& newTime);
    bool deletePassenger(const std::string& id);

    // --- Data Synchronization Getters ---
    const std::vector<Shuttle>& getShuttles() const;
    const std::vector<Passenger>& getPassengers() const;
    const std::vector<Schedule>& getSchedule() const;
};

#endif