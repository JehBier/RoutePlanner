#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

class Passenger {
private:
    std::string name;
    std::string destination;
    std::string requestTime;
    bool isMatched;

public:
    Passenger(std::string pName, std::string pDest, std::string pTime);

    // Getters
    std::string getName() const;
    std::string getDestination() const;
    std::string getRequestTime() const;
    bool getIsMatched() const;

    // Setters
    void setIsMatched(bool status);
    
    // ADD THESE TWO SETTERS HERE:
    void setDestination(const std::string& dest) { destination = dest; }
    void setRequestTime(const std::string& time) { requestTime = time; }
};
#endif