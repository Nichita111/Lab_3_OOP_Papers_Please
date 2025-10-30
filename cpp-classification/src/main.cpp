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

#include "../include/file_reader.hpp"

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
    // Continue to JSON file demo using FileReader
    cout << "\n--- FileReader JSON demo ---\n";
    FileReader fr("resources/test-input.json");

    // Simple flow: read and parse without many checks (per user's request)
    fr.read();
    fr.parseJson();

    fr.printRaw();
    fr.printTopLevelElements();
    fr.printArrayElements("data");

    return 0;

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
