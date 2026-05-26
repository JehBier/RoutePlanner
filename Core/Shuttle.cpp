#include "Shuttle.h"

Shuttle::Shuttle(std::string id, std::string chargingPoint, std::string time)
    : shuttleID(id), targetChargingPoint(chargingPoint), dispatchTime(time), isOccupied(false) {}

std::string Shuttle::getShuttleID() const { return shuttleID; }
std::string Shuttle::getTargetChargingPoint() const { return targetChargingPoint; }
std::string Shuttle::getDispatchTime() const { return dispatchTime; }
bool Shuttle::getIsOccupied() const { return isOccupied; }

void Shuttle::setIsOccupied(bool status) { isOccupied = status; }