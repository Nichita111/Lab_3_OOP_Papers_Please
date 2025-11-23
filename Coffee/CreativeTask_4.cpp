#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include "include/Utils.hh"

using namespace std;

enum class CoffeeType { 
    AMERICANO, 
    CAPPUCCINO, 
    SYRUP_CAPPUCCINO, 
    PUMPKIN_SPICE_LATTE 
};

struct Order { // simple data passed from main
    CoffeeType type;
    Intensity intensity;
    int mlOfWater = 0;        // Americano
    int mlOfMilk = 0;         // Cappuccino variants
    SyrupType syrup = VANILLA;// Syrup Cappuccino
    int mgPumpkinSpice = 0;   // Pumpkin Spice Latte
    // Extras
    int sugarTeaspoons = 0;   // how many teaspoons of sugar
    std::string temperature = "hot"; // hot / warm / cold
    bool extraShot = false;   // add extra espresso shot
};

class Barista; // forward declaration

class Coffee {
protected:
    Intensity coffeeIntensity;
    string name;
    // Extras that the Barista may set
    int sugarTeaspoons = 0;
    string temperature = "hot";
    bool extraShot = false;

    Coffee(Intensity i, string n)
        : coffeeIntensity(i), name(std::move(n)) {}

    // each derived class defines its specific steps
    virtual void makeSpecific() const = 0;
    
    void printDetails() const {
        cout << "\nPreparing " << name << '\n'
             << "Setting intensity to " << intensityToString(coffeeIntensity) << endl;
        if (extraShot) cout << "Adding an extra espresso shot" << endl;
        if (sugarTeaspoons > 0) cout << "Sugar: " << sugarTeaspoons << " tsp" << endl;
        if (!temperature.empty()) cout << "Temperature: " << temperature << endl;
    }

    // Template method for making any coffee
    virtual void makeCoffee() const {
        printDetails();
        makeSpecific();
        cout << "Coffee ready!" << endl;
    }

    friend class Barista; // Barista can use protected members

public:
    // must be public so unique_ptr can delete via default_delete
    virtual ~Coffee() = default;
};

class Americano : public Coffee {
protected:
    int mlOfWater;

    Americano(Intensity i, int w, string n = "Americano")
        : Coffee(i, std::move(n)), mlOfWater(w) {
        if (w < 0)
            throw invalid_argument("mlOfWater must be positive");
    }

    const Americano& makeAmericano() const {
        Coffee::makeCoffee();
        return *this;
    }

    void makeSpecific() const override {
        cout << "Adding " << mlOfWater << " ml water" << endl;
    }

    friend class Barista; // only Barista can create Americano
};

class Cappuccino : public Coffee {
protected:
    int mlOfMilk;

    Cappuccino(Intensity i, int m, string n = "Cappuccino")
        : Coffee(i, std::move(n)), mlOfMilk(m) {
            if (m < 0){
                throw invalid_argument("mlOfMilk must be positive");
            }
        }

    const Cappuccino& makeCappuccino() const {
        Coffee::makeCoffee();
        return *this;
    }

    void makeSpecific() const override {
        cout << "Adding " << mlOfMilk << " ml milk" << endl;
    }

    friend class Barista;
};

class SyrupCappuccino : public Cappuccino {
protected:
    SyrupType syrup;

    SyrupCappuccino(Intensity i, int m, SyrupType s)
        : Cappuccino(i, m, "Syrup Cappuccino"), syrup(s) {}

    const SyrupCappuccino& makeSyrupCappuccino() const {
        Coffee::makeCoffee();
        return *this;
    }

    void makeSpecific() const override {
        Cappuccino::makeSpecific();
        cout << "Adding syrup: " << syrupTypeToString(syrup) << endl;
    }

    friend class Barista;
};

class PumpkinSpiceLatte : public Cappuccino {
protected:
    int mgPumpkinSpice;

    PumpkinSpiceLatte(Intensity i, int m, int mg)
        : Cappuccino(i, m, "Pumpkin Spice Latte"), mgPumpkinSpice(mg) {
        if (mg < 0){
            throw invalid_argument("mgOfPumpkinSpice must be positive");
        }
    }

    const PumpkinSpiceLatte& makePumpkinSpiceLatte() const {
        Coffee::makeCoffee();
        return *this;
    }

    void makeSpecific() const override {
        Cappuccino::makeSpecific();
        cout << "Adding " << mgPumpkinSpice << " mg pumpkin spice" << endl;
    }

    friend class Barista;
};

class Barista {
private:
    string name;
    vector<Order> orders;

    unique_ptr<Coffee> create(const Order &o) const {
        unique_ptr<Coffee> ptr;
        switch (o.type) {
            case CoffeeType::AMERICANO:
                // Barista is a friend, so it can call private ctor
                ptr = unique_ptr<Coffee>(new Americano(o.intensity, o.mlOfWater));
                break;

            case CoffeeType::CAPPUCCINO:
                ptr = unique_ptr<Coffee>(new Cappuccino(o.intensity, o.mlOfMilk));
                break;

            case CoffeeType::SYRUP_CAPPUCCINO:
                ptr = unique_ptr<Coffee>(new SyrupCappuccino(o.intensity, o.mlOfMilk, o.syrup));
                break;

            case CoffeeType::PUMPKIN_SPICE_LATTE:
                ptr = unique_ptr<Coffee>(new PumpkinSpiceLatte(o.intensity, o.mlOfMilk, o.mgPumpkinSpice));
                break;
            default:
                throw runtime_error("Unknown coffee type");
        }
        // copy creative extras from order into the Coffee object (Barista is friend)
        ptr->sugarTeaspoons = o.sugarTeaspoons;
        ptr->temperature = o.temperature;
        ptr->extraShot = o.extraShot;
        return ptr;
    }

public:
    Barista(string name, vector<Order> orders)
        : name(std::move(name)), orders(std::move(orders)) {}

    // Ask the user interactively for orders and populate `orders`.
    void askOrdersFromConsole() {
        cout << "How many orders would you like to place? ";
        int n = 0;
        if (!(cin >> n) || n <= 0) {
            cout << "Invalid number, using 0 orders." << endl;
            cin.clear();
            string dummy; getline(cin, dummy);
            return;
        }
        orders.clear();
        for (int i = 0; i < n; ++i) {
            cout << "\nOrder #" << (i+1) << "\n";
            cout << "Choose coffee (1=Americano,2=Cappuccino,3=Syrup Cappuccino,4=Pumpkin Spice Latte): ";
            int t=0; cin >> t; CoffeeType type = CoffeeType::AMERICANO;
            switch (t) {
                case 1: type = CoffeeType::AMERICANO; break;
                case 2: type = CoffeeType::CAPPUCCINO; break;
                case 3: type = CoffeeType::SYRUP_CAPPUCCINO; break;
                case 4: type = CoffeeType::PUMPKIN_SPICE_LATTE; break;
                default: cout << "Unknown choice, defaulting to Americano." << endl; break;
            }

            cout << "Intensity (Light/Normal/Strong): ";
            string intensityStr; cin >> intensityStr; Intensity intensity = NORMAL;
            try { intensity = stringToIntensity(intensityStr); } catch (...) { cout << "Invalid intensity, using Normal." << endl; }

            Order o; o.type = type; o.intensity = intensity;

            if (type == CoffeeType::AMERICANO) {
                cout << "ml of water (e.g. 150): "; cin >> o.mlOfWater;
            } else {
                cout << "ml of milk (e.g. 120): "; cin >> o.mlOfMilk;
            }

            if (type == CoffeeType::SYRUP_CAPPUCCINO) {
                cout << "Syrup (Macadamia/Vanilla/Coconut/Caramel/Chocolate/Popcorn): ";
                string s; cin >> s; try { o.syrup = stringToSyrupType(s); } catch (...) { cout << "Unknown syrup, using Vanilla." << endl; o.syrup = VANILLA; }
            }

            if (type == CoffeeType::PUMPKIN_SPICE_LATTE) {
                cout << "mg of pumpkin spice (e.g. 50): "; cin >> o.mgPumpkinSpice;
            }

            cout << "Sugar (teaspoons, 0 for none): "; cin >> o.sugarTeaspoons;
            cout << "Temperature (hot/warm/cold): "; cin >> o.temperature;
            cout << "Extra shot? (0=no,1=yes): "; int es = 0; cin >> es; o.extraShot = (es != 0);

            orders.push_back(o);
        }
    }

    void process() {
        for (const auto &o : orders) {
            auto coffee = create(o);
            switch (o.type) {
                case CoffeeType::AMERICANO:
                    static_cast<Americano*>(coffee.get())->makeAmericano();
                    break;
                case CoffeeType::CAPPUCCINO:
                    static_cast<Cappuccino*>(coffee.get())->makeCappuccino();
                    break;
                case CoffeeType::SYRUP_CAPPUCCINO:
                    static_cast<SyrupCappuccino*>(coffee.get())->makeSyrupCappuccino();
                    break;
                case CoffeeType::PUMPKIN_SPICE_LATTE:
                    static_cast<PumpkinSpiceLatte*>(coffee.get())->makePumpkinSpiceLatte();
                    break;
            }
        }
        cout << "\nAll orders completed!" << endl;
    }
};

int main() {

    cout << "Do you want interactive ordering? (y/n): ";
    char choice = 'n';
    if (!(cin >> choice)) choice = 'n';

    if (choice == 'y' || choice == 'Y') {
        Barista b("John", {});
        b.askOrdersFromConsole();
        b.process();
    } else {
        vector<Order> orders = {
            {CoffeeType::AMERICANO,           NORMAL, 150},
            {CoffeeType::CAPPUCCINO,          STRONG, 0, 100},
            {CoffeeType::SYRUP_CAPPUCCINO,    LIGHT,  0, 120, VANILLA},
            {CoffeeType::PUMPKIN_SPICE_LATTE, NORMAL, 0, 130, VANILLA, 50}
        };

        Barista b("John", orders);
        b.process();
    }

    return 0;
}
