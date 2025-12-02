#ifndef CAR_STATION_HPP
#define CAR_STATION_HPP

#include "Car.hpp"
#include "../Task_1/Queue.hpp"
#include "../Task_2/Services.hpp"
#include <string>

using namespace std;

class CarStation {
private:
    // Composition: CarStation HAS-A dining service, refueling service, and a queue.
    // We use pointers to interfaces to achieve Dependency Inversion.
    Dineable* diningService;
    Refuelable* refuelingService;
    Queue<Car>* queue;

public:
    // Constructor Injection (Dependency Injection)
    CarStation(Dineable* dining, Refuelable* refueling, Queue<Car>* q)
        : diningService(dining), refuelingService(refueling), queue(q) {}

    // Adds a car to the station's queue
    void addCar(const Car& c) {
        queue->enqueue(c);
    }

    // Processes all cars in the queue
    void serveCars() {
        while (!queue->isEmpty()) {
            // Get the next car
            Car c = queue->dequeue();
            string carIdStr = to_string(c.id);

            // 1. Serve Dinner
            if (c.isDining) {
                diningService->serveDinner(carIdStr);
            }

            // 2. Refuel
            if (c.consumption > 0) {
                refuelingService->refuel(carIdStr);
            }

            if (c.passengers == "ROBOTS") {
                // Increment robot dinner counter if applicable
                RobotDinner* robotDinnerService = dynamic_cast<RobotDinner*>(diningService);
                if (robotDinnerService) {
                    robotDinnerService->incrementRobots();
                }
            } else if (c.passengers == "PEOPLE") {
                // Increment people dinner counter if applicable
                PeopleDinner* peopleDinnerService = dynamic_cast<PeopleDinner*>(diningService);
                if (peopleDinnerService) {
                    peopleDinnerService->incrementPeople();
                }
            }
        }
    }
};

#endif // CAR_STATION_HPP
