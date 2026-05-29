#include <iostream>
#include <iomanip>
#include <string>
#include "Core/RoutePlanner.h"
#include "Core/Shuttle.h"
#include "Core/Passenger.h"
#include "Core/Schedule.h"

void printShuttleTable(const RoutePlanner& system);
void printPassengerTable(const RoutePlanner& system);
void printScheduleTable(const RoutePlanner& system);

int main() {
    RoutePlanner system;
    int choice = -1; 

    while (choice != 0) {
        std::cout << "========================================\n";
        std::cout << "        ROUTE PLANNER MANAGEMENT        \n";
        std::cout << "========================================\n";
        std::cout << "1. Load Shuttles & Passengers\n";
        std::cout << "2. Display All Data (Tables)\n";
        std::cout << "3. Generate Matchmaking Schedule\n";
        std::cout << "4. Save Schedule to Log\n";
        std::cout << "5. Add a New Record (Shuttle/Passenger)\n";
        std::cout << "6. Edit an Existing Record\n";
        std::cout << "7. Delete a Record\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid numeric entry. Resetting menu...\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "\nAccessing Records directory...\n";
                if (system.loadShuttles() && system.loadPassengers()) {
                    std::cout << ">>> Success: Records successfully parsed into temporary RAM arrays!\n";
                } else {
                    std::cout << ">>> Error: Could not locate Shuttle.txt or Passenger.txt in Records/.\n";
                }
                break;

            case 2: 
                printShuttleTable(system);
                printPassengerTable(system);
                break;

            case 3: 
                std::cout << "\nProcessing optimization constraints...\n";
                system.generateSchedule();
                std::cout << ">>> Matchmaking engine calculation completed successfully!\n";
                printScheduleTable(system);
                break;

            case 4: 
                if (system.saveSchedule()) {
                    std::cout << ">>> Success: Active allocation archive exported to Records/Log.txt\n";
                } else {
                    std::cout << ">>> Error: Write permissions denied or Records/ folder is missing.\n";
                }
                break;
                
            case 5: { 
                int typeChoice;
                std::cout << "\n[1] Add Shuttle  [2] Add Passenger\nChoose type: ";
                std::cin >> typeChoice;
                
                if (typeChoice == 1) {
                    std::string id, cp, time;
                    std::cout << "Enter Unique Shuttle ID: "; std::cin >> id;
                    std::cout << "Enter Charging Node Target: "; std::cin >> cp;
                    std::cout << "Enter Dispatch Time Slot (e.g., 0830): "; std::cin >> time;
                    
                    system.addShuttle(Shuttle(id, cp, time));
                    std::cout << ">>> Success: Shuttle '" << id << "' loaded directly into working memory\n";
                } else if (typeChoice == 2) {
                    std::string name, dest, time;
                    std::cout << "Enter Passenger Name: "; std::cin >> name;
                    std::cout << "Enter Destination: "; std::cin >> dest;
                    std::cout << "Enter Request Time Slot: "; std::cin >> time;

                    system.addPassenger(Passenger(name, dest, time));
                    std::cout << ">>> Success: Passenger '" << name << "' loaded directly into working memory\n";
                }
                break;
            }

            case 6: { 
                int typeChoice;
                std::cout << "\n[1] Edit Shuttle  [2] Edit Passenger\nChoose type: ";
                std::cin >> typeChoice;

                if (typeChoice == 1) {
                    std::string id, newTime, newCP;
                    std::cout << "Enter Shuttle ID to modify: "; std::cin >> id;
                    std::cout << "Enter New Dispatch Time: "; std::cin >> newTime;
                    std::cout << "Enter New Target Charging Point: "; std::cin >> newCP;

                    if (system.editShuttle(id, newTime, newCP)) {
                        std::cout << ">>> Success: Shuttle properties updated in RAM!\n";
                    } else {
                        std::cout << ">>> Error: Shuttle ID '" << id << "' not found.\n";
                    }
                } else if (typeChoice == 2) {
                    std::string name, newDest, newTime;
                    std::cout << "Enter Passenger Name to modify: "; std::cin >> name;
                    std::cout << "Enter New Destination: "; std::cin >> newDest;
                    std::cout << "Enter New Request Time: "; std::cin >> newTime;

                    if (system.editPassenger(name, newDest, newTime)) {
                        std::cout << ">>> Success: Passenger properties updated in RAM!\n";
                    } else {
                        std::cout << ">>> Error: Passenger name '" << name << "' not found.\n";
                    }
                }
                break;
            }

            case 7: { 
                int typeChoice;
                std::cout << "\n[1] Delete Shuttle  [2] Delete Passenger\nChoose type: ";
                std::cin >> typeChoice;

                if (typeChoice == 1) {
                    std::string id;
                    std::cout << "Enter Shuttle ID to permanently remove: "; std::cin >> id;
                    if (system.deleteShuttle(id)) {
                        std::cout << ">>> Success: Shuttle dropped from memory vector.\n";
                    } else {
                        std::cout << ">>> Error: Shuttle ID '" << id << "' not found.\n";
                    }
                } else if (typeChoice == 2) {
                    std::string name;
                    std::cout << "Enter Passenger Name to permanently remove: "; std::cin >> name;
                    if (system.deletePassenger(name)) {
                        std::cout << ">>> Success: Passenger dropped from memory vector.\n";
                    } else {
                        std::cout << ">>> Error: Passenger name '" << name << "' not found.\n";
                    }
                }
                break;
            }

            case 0:
                std::cout << "\nWiping active operational RAM instances... Goodbye!\n";
                break;

            default:
                std::cout << "Selection outside permissible operational parameters. Try again.\n";
                break;
        }
    }
    return 0;
}

void printShuttleTable(const RoutePlanner& system) {
    const auto& shuttles = system.getShuttles();
    if (shuttles.empty()) {
        std::cout << "\n[RAM Status: array empty. Please load files or add custom entries.]\n";
        return;
    }
    std::cout << "\n-----------------------------------------------------\n";
    std::cout << std::left << std::setw(15) << "SHUTTLE ID" << std::setw(20) << "CHARGING NODE" << std::setw(10) << "DISPATCH" << "STATUS\n";
    std::cout << "-----------------------------------------------------\n";
    for (const auto& s : shuttles) {
        std::cout << std::left << std::setw(15) << s.getShuttleID() 
                  << std::setw(20) << s.getTargetChargingPoint() 
                  << std::setw(10) << s.getDispatchTime() 
                  << (s.getIsOccupied() ? "Occupied" : "Available") << "\n";
    }
}

void printPassengerTable(const RoutePlanner& system) {
    const auto& passengers = system.getPassengers();
    if (passengers.empty()) {
        std::cout << "\n[RAM Status: array empty. Please load files first.]\n";
        return;
    }
    std::cout << "\n-----------------------------------------------------\n";
    std::cout << std::left << std::setw(18) << "PASSENGER NAME" << std::setw(14) << "DESTINATION" << std::setw(14) << "REQUEST" << "ASSIGNED\n";
    std::cout << "-----------------------------------------------------\n";
    for (const auto& p : passengers) {
        std::cout << std::left << std::setw(18) << p.getName() 
                  << std::setw(14) << p.getDestination() 
                  << std::setw(10) << p.getRequestTime() 
                  << (p.getIsMatched() ? "Yes" : "No") << "\n";
    }
}

void printScheduleTable(const RoutePlanner& system) {
    const auto& schedule = system.getSchedule();
    if (schedule.empty()) {
        std::cout << "\n[Schedule State: No active pairings calculated by core engine.]\n";
        return;
    }
    std::cout << "\n--------------------------------------------------------------------------------\n";
    std::cout << "                         ACTIVE LOG MATCHINGS (IN RAM)                         \n";
    std::cout << "--------------------------------------------------------------------------------\n";
    for (const auto& item : schedule) {
        std::cout << item.getLogLine() << "\n";
    }
}