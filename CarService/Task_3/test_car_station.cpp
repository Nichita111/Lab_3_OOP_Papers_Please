#include <iostream>
#include <cassert>
#include "CarStation.hpp"
#include "../Task_2/Services.hpp"
#include "../Task_1/Queue.hpp"

using namespace std;

void testCarStation() {
    cout << "Task 3: CarStation Tests" << endl;

    // 1. Setup Dependencies (The "IoC Container" part, done manually here)
    
    // We want a station for: Electric Cars with People
    ElectricStation electricStation;
    PeopleDinner peopleDinner;
    DequeQueue<Car> carQueue;

    // 2. Inject Dependencies into CarStation
    CarStation station(&peopleDinner, &electricStation, &carQueue);

    // 3. Create some test cars
    Car c1; c1.id = 101; c1.type = "ELECTRIC"; c1.passengers = "PEOPLE"; c1.isDining = true; c1.consumption = 20;
    Car c2; c2.id = 102; c2.type = "ELECTRIC"; c2.passengers = "PEOPLE"; c2.isDining = false; c2.consumption = 10;

    // 4. Add cars
    station.addCar(c1);
    station.addCar(c2);

    // Reset counters (ok we don't need that)
    //electricStation.resetElectricCounter();
    //peopleDinner.resetPeopleCounter();

    // 5. Serve cars
    cout << "Starting service..." << endl;
    station.serveCars();

    // 6. Verify Logic
    // Both cars should be refueled
    assert(electricStation.getNrElectricServed() == 2);
    cout << "Electric Cars Served: " << electricStation.getNrElectricServed() << " (Expected: 2)" << endl;

    // Only car 101 was dining
    assert(peopleDinner.getNrPeople() == 2);
    cout << "People Served Dinner: " << peopleDinner.getNrPeople() << " (Expected: 2)" << endl;

    cout << "All CarStation tests passed!" << endl;
}

int main() {
    testCarStation();
    return 0;
}
