#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Shuttle.h"
#include "Passenger.h"
#include <string>

class Schedule {
private:
    Shuttle matchedShuttle;
    Passenger matchedPassenger;

public:
    Schedule(Shuttle shuttle, Passenger passenger);
    std::string getLogLine() const;
};

#endif