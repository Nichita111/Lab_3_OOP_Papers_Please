#include <iostream>
#include <fstream>
#include "../include/nlohmann/json.hpp"
#include <vector>
#include <string>

using json = nlohmann::json;
using namespace std;

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Individual {
private:
    int id;
    bool isHumanoid;
    string originPlanet;
    int age;
    vector<string> physicalTraits;

public:
    Individual(int id, bool isHumanoid, const string& originPlanet, int age, const vector<string>& physicalTraits)
        : id(id), isHumanoid(isHumanoid), originPlanet(originPlanet), age(age), physicalTraits(physicalTraits) {}

    int getId() const {
        return id;
    }

    bool getIsHumanoid() const {
        return isHumanoid;
    }

    string getOriginPlanet() const {
        return originPlanet;
    }

    int getAge() const {
        return age;
    }

    const vector<string>& getPhysicalTraits() const {
        return physicalTraits;
    }

    // Modifiers
    void setIsHumanoid(bool value) { 
        isHumanoid = value; 
    }

    void setOriginPlanet(const string& planet) { 
        originPlanet = planet; 
    }

    void setAge(int newAge) { 
        age = newAge; 
    }

    void addTrait(const string& trait) { 
        physicalTraits.push_back(trait); 
    }

    bool removeTrait(const string& trait) {
        auto it = remove(physicalTraits.begin(), physicalTraits.end(), trait);
        bool removed = it != physicalTraits.end();
        physicalTraits.erase(it, physicalTraits.end());
        return removed;
    }

    void display() const {
        cout << "ID: " << id << "\n"
             << "Humanoid: " << (isHumanoid ? "Yes" : "No") << "\n"
             << "Origin Planet: " << originPlanet << "\n"
             << "Age: " << age << "\n"
             << "Traits: ";
        for (const auto& trait : physicalTraits)
            cout << trait << " ";
        cout << "\n";
    }

    string classify() const {
        return "undefined";
    }

};


class Universe {
private:
    string name;
    vector<json> individuals;
public:
    Universe(const string& name) : name(name) {}
    void setIndividuals(json individual){
        individuals.push_back(individual);
    }
    auto getIndividuals(){
        return individuals;
    }

    string getName(){
        return name;
    }
};

int main(int argc, char* argv[]) {
    // Demo mode: showcase Individual class creation, printing, testing, and modification
    cout << "--- Individual class demo ---\n";
    Individual hero(1, true, "Earth", 30, {"tall", "brave"});
    hero.display();
    cout << "Classification: " << hero.classify() << "\n\n";

    cout << "-- Modifying the individual --\n";
    hero.setAge(31);
    hero.addTrait("scarred");
    hero.removeTrait("brave");
    hero.setIsHumanoid(false);
    hero.setOriginPlanet("Krypton");
    hero.addTrait("metallic");

    hero.display();
    cout << "Classification after changes: " << hero.classify() << "\n";

    return 0; // Exit after demo

/*    ifstream inputFile("../resources/test-input.json");
    if (!inputFile) {
        cerr << "Error: Could not open the input file!" << endl;
        return 1;
    }

    json inputJson;
    inputFile >> inputJson;
    json data = inputJson["data"];
    
    Universe starWars("star-wars");
    Universe hitchhikers("hitch-hiker");
    Universe marvel("marvel");
    Universe rings("rings");

    string userInput;
    for (const auto& entry : data) {
        cout << entry.dump() << endl; 
        cin >> userInput;

        if (userInput == "1") {
            starWars.setIndividuals(entry);
        } else if (userInput == "2") {
            hitchhikers.setIndividuals(entry);
        } else if (userInput == "3") {
            marvel.setIndividuals(entry);
        } else if (userInput == "4") {
            rings.setIndividuals(entry);
        } else {
            cout << "Invalid input" << endl;
        }
    }

    ofstream outStarWars("../resources/output/star-wars.json");
    ofstream outHitchhikers("../resources/output/hitch-hiker.json");
    ofstream outMarvel("../resources/output/marvel.json");
    ofstream outRings("../resources/output/rings.json");
    outStarWars << json({{"name", starWars.getName()}, {"individuals", starWars.getIndividuals()}}).dump(4);
    outHitchhikers << json({{"name", hitchhikers.getName()}, {"individuals", hitchhikers.getIndividuals()}}).dump(4);
    outMarvel << json({{"name", marvel.getName()}, {"individuals", marvel.getIndividuals()}}).dump(4);
    outRings << json({{"name", rings.getName()}, {"individuals", rings.getIndividuals()}}).dump(4);

    cout << "Success! Files have been written." << endl;
    return 0;*/
}
