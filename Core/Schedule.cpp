#include "Schedule.h"

Schedule::Schedule(Shuttle shuttle, Passenger passenger)
    : matchedShuttle(shuttle), matchedPassenger(passenger) {}

std::string Schedule::getLogLine() const {
    return "Shuttle: " + matchedShuttle.getShuttleID() + 
           " | Destination: " + matchedShuttle.getTargetChargingPoint() + 
           " | Passenger: " + matchedPassenger.getName() + 
           " | Time: " + matchedShuttle.getDispatchTime();
}