#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include "Utils.hh"

using namespace std;

class Coffee {
protected:
    Intensity coffeeIntensity;
    const string name;
public:
    Coffee (Intensity cI, string n)
        : coffeeIntensity(cI), name(std::move(n)) {};

    virtual ~Coffee() = default;

};

class Americano : public Coffee{
protected:
    int mlOfWater;

public:
     Americano (Intensity intensity, int mlOfWater)
        : Coffee(intensity, "Americano"), mlOfWater(mlOfWater) {
            if (mlOfWater < 0) {
                throw invalid_argument("mlOfWater must be positive");
            }
        }
};

class Cappuccino : public Coffee{
protected:
    int mlOfMilk;
public:
     Cappuccino (Intensity intensity, int mlOfMilk)
        : Coffee(intensity, "Cappuccino"), mlOfMilk(mlOfMilk) {
            if (mlOfMilk < 0) {
                throw invalid_argument("mlOfMilk must be positive");
            }
        }
};

class SyrupCappuccino : public Cappuccino {
protected:
    SyrupType syrup;
public:
    SyrupCappuccino (Intensity intensity, int mlOfMilk, SyrupType syrup)
        : Cappuccino(intensity, mlOfMilk), syrup(syrup) {}
};

class PumpkinSpiceLatte : public Cappuccino {
    int mgOfPumpkinSpice;

public: 
    PumpkinSpiceLatte (Intensity intensity, int mlOfMilk, int mgOfPumpkinSpice)
        : Cappuccino(intensity, mlOfMilk), mgOfPumpkinSpice(mgOfPumpkinSpice) {
            if (mlOfMilk < 0){
                throw invalid_argument("mlOfMilk must be positive");
            }
            if (mgOfPumpkinSpice < 0){
                throw invalid_argument("mgOfPumpkinSpice must be positive");
            }
        }

};


int main() {
    Americano americano(NORMAL, 150);
    Cappuccino cappuccino(STRONG, 100);
    SyrupCappuccino syrupCappuccino(LIGHT, 120, VANILLA);
    PumpkinSpiceLatte pumpkinSpiceLatte(NORMAL, 130, 50);

    return 0;
}











