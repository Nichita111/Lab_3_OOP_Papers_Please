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
        : coffeeIntensity(cI), name(std::move(n)) {}

    virtual ~Coffee() = default;

    Intensity getCoffeeIntensity() const {
        return coffeeIntensity;
    }

    const string& getName() const {
        return name;
    }

    virtual void printDetails() const {
        cout << "\n" << name << endl;
        cout << "Coffee intensity: " << intensityToString(coffeeIntensity) << endl;
    }

};

class Americano : public Coffee{
protected:
    int mlOfWater;

public:
     Americano (Intensity intensity, int mlOfWater, const string& n = "Americano")
        : Coffee(intensity, n), mlOfWater(mlOfWater) {
            if (mlOfWater < 0) {
                throw invalid_argument("mlOfWater must be positive");
            }
        }

        void printDetails() const override {
            Coffee::printDetails();
            cout << getName() << " water: " << mlOfWater << " ml" << endl;
        }
};

class Cappuccino : public Coffee{
protected:
    int mlOfMilk;
public:
     Cappuccino (Intensity intensity, int mlOfMilk, const string& n = "Cappuccino")
        : Coffee(intensity, n), mlOfMilk(mlOfMilk) {
            if (mlOfMilk < 0) {
                throw invalid_argument("mlOfMilk must be positive");
            }
        }

        void printDetails() const override {
            Coffee::printDetails();
            cout << getName() << " milk: " << mlOfMilk << " ml" << endl;
        }
};

class SyrupCappuccino : public Cappuccino {
protected:
    SyrupType syrup;
public:
    SyrupCappuccino (Intensity intensity, int mlOfMilk, SyrupType syrup)
        : Cappuccino(intensity, mlOfMilk, "Syrup Cappuccino"), syrup(syrup) {}

        void printDetails() const override {
            Cappuccino::printDetails();
            cout << "Syrup: " << syrupTypeToString(syrup) << endl;
        }
};

class PumpkinSpiceLatte : public Cappuccino {
    int mgOfPumpkinSpice;

public: 
    PumpkinSpiceLatte (Intensity intensity, int mlOfMilk, int mgOfPumpkinSpice)
        : Cappuccino(intensity, mlOfMilk, "Pumpkin Spice Latte"), mgOfPumpkinSpice(mgOfPumpkinSpice) {
            if (mgOfPumpkinSpice < 0){
                throw invalid_argument("mgOfPumpkinSpice must be positive");
            }
        }

        void printDetails() const override {
            Cappuccino::printDetails();
            cout << "Pumpkin spice: " << mgOfPumpkinSpice << " mg" << endl;
        }

};


int main() {
    Americano americano(NORMAL, 150);
    americano.printDetails();

    Cappuccino cappuccino(STRONG, 100);
    cappuccino.printDetails();

    SyrupCappuccino syrupCappuccino(LIGHT, 120, VANILLA);
    syrupCappuccino.printDetails();

    PumpkinSpiceLatte pumpkinSpiceLatte(NORMAL, 130, 50);
    pumpkinSpiceLatte.printDetails();

    return 0;
}













