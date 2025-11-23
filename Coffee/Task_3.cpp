#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include "include/Utils.hh"

using namespace std;

class Coffee {
protected:
    Intensity coffeeIntensity;
    const string name;

    // helper
    void printIntensityStep() const {
        cout << "Intensity set to " << intensityToString(coffeeIntensity) << endl;
    }
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

    virtual void makeCoffee() const final {
        cout << "\nMaking " << name << endl;
        printIntensityStep();
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

        Americano makeAmericano() const {
            Coffee::makeCoffee();
            cout << "Adding " << mlOfWater << " ml of water" << endl;
            return Americano(getCoffeeIntensity(), mlOfWater);
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

        Cappuccino makeCappuccino() const {
            Coffee::makeCoffee();
            cout << "Adding " << mlOfMilk << " ml of milk" << endl;
            return Cappuccino(getCoffeeIntensity(), mlOfMilk);
        }
};

class SyrupCappuccino : public Cappuccino {
protected:
    SyrupType syrup;
public:
    SyrupCappuccino (Intensity intensity, int mlOfMilk, SyrupType syrup)
        : Cappuccino(intensity, mlOfMilk, "Syrup Cappuccino"), syrup(syrup) {
            // validation for mlOfMilk is handled by Cappuccino
        }

        SyrupCappuccino makeSyrupCappuccino() const {
            Cappuccino::makeCappuccino();
            cout << "Adding syrup " << syrupTypeToString(syrup) << endl;
            return SyrupCappuccino(getCoffeeIntensity(), mlOfMilk, syrup);
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

        PumpkinSpiceLatte makePumpkinSpiceLatte() const {
            Cappuccino::makeCappuccino();
            cout << "Adding " << mgOfPumpkinSpice << " mgs of pumpkin spice" << endl;
            return PumpkinSpiceLatte(getCoffeeIntensity(), mlOfMilk, mgOfPumpkinSpice);
        }

};


int main() {
    Americano americano(NORMAL, 150);
    auto americanoMade = americano.makeAmericano();

    Cappuccino cappuccino(STRONG, 100);
    auto cappuccinoMade = cappuccino.makeCappuccino();

    SyrupCappuccino syrupCappuccino(LIGHT, 120, VANILLA);
    auto syrupCappuccinoMade = syrupCappuccino.makeSyrupCappuccino();

    PumpkinSpiceLatte pumpkinSpiceLatte(NORMAL, 130, 50);
    auto pumpkinSpiceLatteMade = pumpkinSpiceLatte.makePumpkinSpiceLatte();

    return 0;
}
