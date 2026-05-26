#ifndef SHUTTLE_H
#define SHUTTLE_H

#include <string>

class Shuttle {
private:
    std::string shuttleID;
    std::string targetChargingPoint;
    std::string dispatchTime;
    bool isOccupied;

public:
    Shuttle(std::string id, std::string chargingPoint, std::string time);

    std::string getShuttleID() const;
    std::string getTargetChargingPoint() const;
    std::string getDispatchTime() const;
    bool getIsOccupied() const;

    void setIsOccupied(bool status);
};

#endif