#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <vector>
#include <string>
#include "Shuttle.h"
#include "Passenger.h"
#include "Schedule.h" 

class RoutePlanner {
private:
    std::vector<Shuttle> totalShuttles;
    std::vector<Passenger> totalPassengers;
    std::vector<Schedule> activeSchedule; // Updated class name

public:
    RoutePlanner() = default;

    //File I/O Operations
    bool loadShuttles();   
    bool loadPassengers(); 
    bool saveSchedule();   

    //Core Matching Engine
    void generateSchedule();

    //RAM Management CRUD Operations
    void addShuttle(const Shuttle& newShuttle);
    void deletePassenger(int index);

    //CLI Debug Getters
    const std::vector<Shuttle>& getShuttles() const;
    const std::vector<Passenger>& getPassengers() const;
    const std::vector<Schedule>& getSchedule() const; 
};

#endif