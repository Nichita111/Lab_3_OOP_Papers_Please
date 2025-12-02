#ifndef SERVICES_HPP
#define SERVICES_HPP

#include <iostream>
#include <string>
#include <atomic>

using namespace std;

//Why atomic? It is thread safe, we will have multiple paralel stations
//Why static? Conecino ca we need just one counter for the whole class

// Task 2: Interfaces

class Dineable {
public:
    virtual ~Dineable() = default;
    virtual void serveDinner(const string& carId) = 0;
};

class Refuelable {
public:
    virtual ~Refuelable() = default;
    virtual void refuel(const string& carId) = 0;
};


// Concrete Implementations

class PeopleDinner : public Dineable {
private:
    // Static counter for statistics
    static atomic<int> peopleServed;

public:
    void serveDinner(const string& carId) override {
        cout << "Serving dinner to people in car " << carId << "." << endl;
    }

    int getNrPeople() {
        return peopleServed;
    }

    void resetPeopleCounter() {
        peopleServed = 0;
    }

    void incrementPeople() {
        peopleServed++;
    }

};

// Initialize static member
atomic<int> PeopleDinner::peopleServed{0};


class RobotDinner : public Dineable {
private:
    static atomic<int> robotsServed;

public:
    void serveDinner(const string& carId) override {
        cout << "Serving dinner to robots in car " << carId << "." << endl;
    }

    int getNrRobots() {
        return robotsServed;
    }

    void resetRobotsCounter() {
        robotsServed = 0;
    }

    void incrementRobots() {
        robotsServed++;
    }
};

atomic<int> RobotDinner::robotsServed{0};


class ElectricStation : public Refuelable {
private:
    static atomic<int> electricCarsServed;

public:
    void refuel(const string& carId) override {
        electricCarsServed++;
        cout << "Refueling electric car " << carId << "." << endl;
    }

    int getNrElectricServed() {
        return electricCarsServed;
    }

    void resetElectricCounter() {
        electricCarsServed = 0;
    }
};

atomic<int> ElectricStation::electricCarsServed{0};


class GasStation : public Refuelable {
private:
    static atomic<int> gasCarsServed;

public:
    void refuel(const string& carId) override {
        gasCarsServed++;
        cout << "Refueling gas car " << carId << "." << endl;
    }

    int getNrGasServed() {
        return gasCarsServed;
    }

    void resetGasCounter() {
        gasCarsServed = 0;
    }
};

atomic<int> GasStation::gasCarsServed{0};

#endif // SERVICES_HPP