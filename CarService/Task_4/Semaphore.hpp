#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include "../Task_3/CarStation.hpp"
#include "../Task_2/Services.hpp"
#include "../Task_1/Queue.hpp"
#include "../Task_3/Car.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Semaphore {
private:
    // We need 4 distinct stations to cover all combinations:
    // 1. Electric + People
    // 2. Electric + Robots
    // 3. Gas + People
    // 4. Gas + Robots
    
    // Concrete services
    ElectricStation electricStation;
    GasStation gasStation;
    PeopleDinner peopleDinner;
    RobotDinner robotDinner;

    // Queues for each station
    DequeQueue<Car> q1, q2, q3, q4;

    // The 4 stations
    CarStation* stationElectricPeople;
    CarStation* stationElectricRobots;
    CarStation* stationGasPeople;
    CarStation* stationGasRobots;

public:
    Semaphore() {
        // Initialize stations with correct dependencies
        stationElectricPeople = new CarStation(&peopleDinner, &electricStation, &q1);
        stationElectricRobots = new CarStation(&robotDinner, &electricStation, &q2);
        stationGasPeople = new CarStation(&peopleDinner, &gasStation, &q3);
        stationGasRobots = new CarStation(&robotDinner, &gasStation, &q4);
    }

    ~Semaphore() {
        delete stationElectricPeople;
        delete stationElectricRobots;
        delete stationGasPeople;
        delete stationGasRobots;
    }

    // Guides a car to the correct station based on its type and passengers
    void guideCar(const Car& c) {
        if (c.type == "ELECTRIC") {
            if (c.passengers == "PEOPLE") {
                stationElectricPeople->addCar(c);
            } else if (c.passengers == "ROBOTS") {
                stationElectricRobots->addCar(c);
            }
        } else if (c.type == "GAS") {
            if (c.passengers == "PEOPLE") {
                stationGasPeople->addCar(c);
            } else if (c.passengers == "ROBOTS") {
                stationGasRobots->addCar(c);
            }
        }
    }

    // Triggers service on all stations
    void serveAll() {
        stationElectricPeople->serveCars();
        stationElectricRobots->serveCars();
        stationGasPeople->serveCars();
        stationGasRobots->serveCars();
    }

    int getPeople() {
        return peopleDinner.getNrPeople();
    }
    int getRobots() {
        return robotDinner.getNrRobots();
    }
    int getGas() {
        return gasStation.getNrGasServed();
    }
    int getElectric() {
        return electricStation.getNrElectricServed();
    }
};

#endif // SEMAPHORE_HPP
