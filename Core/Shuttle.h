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

    // Getters
    std::string getShuttleID() const;
    std::string getTargetChargingPoint() const;
    std::string getDispatchTime() const;
    bool getIsOccupied() const;

    // Setters
    void setIsOccupied(bool status);
    void setDispatchTime(const std::string& time) { dispatchTime = time; }
    void setTargetChargingPoint(const std::string& cp) { targetChargingPoint = cp; }
};

#endif