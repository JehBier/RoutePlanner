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
    int choice = 0;

    while (choice != 7) {
        std::cout << "\n========================================\n";
        std::cout << "           SHUTTLE ROUTE PLANNER       \n";
        std::cout << "========================================\n";
        std::cout << "1. Load Master Lists from Records/ Folder\n";
        std::cout << "2. View Active Shuttles (RAM)\n";
        std::cout << "3. View Waiting Passengers (RAM)\n";
        std::cout << "4. Add New Custom Fleet Shuttle (RAM Only)\n";
        std::cout << "5. Generate Matchmaking Schedule\n";
        std::cout << "6. Save/Archive Schedule to Records/Log.txt\n";
        std::cout << "7. Exit Application\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Enter selection (1-7): ";
        
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
                break;

            case 3:
                printPassengerTable(system);
                break;

            case 4: {
                std::string id, cp, time;
                std::cout << "\n--- New Live Shuttle ---\n";
                std::cout << "Enter Unique Shuttle ID: "; std::cin >> id;
                std::cout << "Enter Charging Node Target: "; std::cin >> cp;
                std::cout << "Enter Dispatch Time Slot (e.g., 0830): "; std::cin >> time;
                
                system.addShuttle(Shuttle(id, cp, time));
                std::cout << "\n>>> Success: Shuttle '" << id << "' loaded directly into working memory\n";
                break;
            }

            case 5:
                std::cout << "\nProcessing optimization constraints...\n";
                system.generateSchedule();
                std::cout << ">>> Matchmaking engine calculation completed successfully!\n";
                printScheduleTable(system);
                break;

            case 6:
                if (system.saveSchedule()) {
                    std::cout << ">>> Success: Active allocation archive exported to Records/Log.txt\n";
                } else {
                    std::cout << ">>> Error: Write permissions denied or Records/ folder is missing.\n";
                }
                break;

            case 7:
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