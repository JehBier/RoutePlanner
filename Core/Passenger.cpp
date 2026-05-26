#include "Passenger.h"

Passenger::Passenger(std::string pName, std::string pDest, std::string pTime) 
    : name(pName), destination(pDest), requestTime(pTime), isMatched(false) {}

std::string Passenger::getName() const { return name; }
std::string Passenger::getDestination() const { return destination; }
std::string Passenger::getRequestTime() const { return requestTime; }
bool Passenger::getIsMatched() const { return isMatched; }

void Passenger::setIsMatched(bool status) { isMatched = status; }