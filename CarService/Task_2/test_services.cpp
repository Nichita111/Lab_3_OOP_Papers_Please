#include <iostream>
#include <cassert>
#include <string>
#include "Services.hpp"

using namespace std;

void testServices() {
    cout << "Task 2: Service Tests" << endl;

    // 1. Test PeopleDinner
    PeopleDinner pd;
    pd.serveDinner("1");
    pd.serveDinner("2");

    // 2. Test RobotDinner
    RobotDinner rd;
    rd.serveDinner("3");

    // 3. Test ElectricStation
    ElectricStation es;
    es.refuel("1"); // Car 1 is electric
    es.refuel("2"); // Car 2 is electric
    assert(es.getNrElectricServed() == 2);
    cout << "ElectricStation stats: " << es.getNrElectricServed() << " (Expected: 2)" << endl;

    // 4. Test GasStation
    GasStation gs;
    gs.refuel("3"); // Car 3 is gas
    assert(gs.getNrGasServed() == 1);
    cout << "GasStation stats: " << gs.getNrGasServed()<< " (Expected: 1)" << endl;

    // 5. Test Shared Statistics (Multiple instances)
    // "Imagine there are two car service station with electric station"
    ElectricStation es2;
    es2.refuel("4");
    assert(es2.getNrElectricServed() == 3); // Should be 2 + 1
    cout << "ElectricStation shared stats after new instance: " << es2.getNrElectricServed() << " (Expected: 3)" << endl;

    cout << "All Service tests passed!" << endl;
}

int main() {
    testServices();
    return 0;
}