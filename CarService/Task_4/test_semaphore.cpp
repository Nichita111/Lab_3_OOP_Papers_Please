#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "Semaphore.hpp"
#include "../Task_3/Car.hpp"
#include "../Task_2/Services.hpp"

using namespace std;
using json = nlohmann::json;

void testSemaphore() {
    cout << "Task 4: Semaphore Tests" << endl;

    // 1. Reset Stats (still not sure if needed)

    // 2. Create Semaphore
    Semaphore semaphore;

    // 3. Create Test Data (JSON Strings)
    vector<string> jsonInputs = {
        R"({"id": 1, "type": "ELECTRIC", "passengers": "PEOPLE", "isDining": true, "consumption": 42})",
        R"({"id": 2, "type": "ELECTRIC", "passengers": "ROBOTS", "isDining": false, "consumption": 26})",
        R"({"id": 3, "type": "GAS", "passengers": "PEOPLE", "isDining": true, "consumption": 41})",
        R"({"id": 4, "type": "GAS", "passengers": "ROBOTS", "isDining": true, "consumption": 15})"
    };

    // 4. Parse and Guide Cars
    for (const auto& jsonStr : jsonInputs) {
        try {
            json j = json::parse(jsonStr);
            Car c;
            if (Car::fromJson(j, c)) {
                semaphore.guideCar(c);
            } else {
                cerr << "Failed to parse car JSON: " << jsonStr << endl;
            }
        } catch (const exception& e) {
            cerr << "JSON parsing error: " << e.what() << endl;
        }
    }

    // 5. Serve All
    semaphore.serveAll();

    // 6. Verify Stats
    
    // Electric Cars: c1, c2 -> Total 2
    assert(semaphore.getElectric() == 2);
    cout << "Electric Cars: " << semaphore.getElectric() << " (Expected: 2)" << endl;

    // Gas Cars: c3, c4 -> Total 2
    assert(semaphore.getGas() == 2);
    cout << "Gas Cars: " << semaphore.getGas() << " (Expected: 2)" << endl;

    // People Dining: c1 (Dining), c3 (Dining) -> Total 2
    assert(semaphore.getPeople() == 2);
    cout << "People Served: " << semaphore.getPeople() << " (Expected: 2)" << endl;

    // Robots Dining: c2 (Not Dining), c4 (Dining) -> Total 1
    assert(semaphore.getRobots() == 2);
    cout << "Robots Served: " << semaphore.getRobots() << " (Expected: 2)" << endl;

    cout << "All Semaphore tests passed!" << endl;
}

int main() {
    testSemaphore();
    return 0;
}
