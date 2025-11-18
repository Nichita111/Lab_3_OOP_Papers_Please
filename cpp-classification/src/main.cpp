#include <iostream>
#include <fstream>
#include "../include/nlohmann/json.hpp"
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <unordered_set>

using json = nlohmann::json;
using namespace std;


#include "../include/file_reader.hh"

class Individual {
private:
    int id;
    std::optional<bool> isHumanoid;
    string originPlanet;
    int age;
    vector<string> physicalTraits;

public:
    Individual(int id, std::optional<bool> isHumanoidVal, const string& originPlanet, int age, const vector<string>& physicalTraits)
        : id(id), isHumanoid(isHumanoidVal), originPlanet(originPlanet), age(age), physicalTraits(physicalTraits) {}

    int getId() const {
        return id;
    }

    std::optional<bool> getIsHumanoid() const {
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

    void setIsHumanoid(std::optional<bool> value) { 
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
       cout << "ID: " << id << "\n";
       cout << "Humanoid: ";
       if (isHumanoid.has_value()) cout << (isHumanoid.value() ? "Yes" : "No"); else cout << "unknown";
       cout << "\n";
       cout << "Origin Planet: " << originPlanet << "\n"
           << "Age: " << age << "\n"
           << "Traits: ";
        for (const auto& trait : physicalTraits)
            cout << trait << " ";
        cout << "\n\n";
    }

    string classify() const {
        string planet = originPlanet;
        vector<string> traits;
        traits.reserve(physicalTraits.size());
        for (auto t : physicalTraits) traits.push_back(t);
        auto hasTrait = [&](const std::string& trait) {
            return std::find(traits.begin(), traits.end(), trait) != traits.end();
        };


        //Check unambiguous criterias
        // Star Wars
        if (planet == "ENDOR"){
            return "Star Wars: Ewok";
        }

        if (planet == "KASHYYYK" || hasTrait("HAIRY")) {
            return "Star Wars: Wookie";
        }

        // Marvel
        if (planet == "ASGARD"){
            return "Marvel: Asgardian";
        }

        // Hitchhiker's
        if (planet == "BETELGEUSE" || hasTrait("EXTRA_ARMS") || hasTrait("EXTRA_HEAD")){
            return "Hitchhiker's: Betelgeusian";
        }
        if (planet == "VOGSPHERE" || hasTrait("GREEN")){
            return "Hitchhiker's: Vogon";
        }

        // Lord of the Rings
        // Unambiguous hints for Elf on Earth: pointy ears, blonde, or extremely old
        if (age > 5000){
            return "Rings: Elf";
        }

        if (planet == "EARTH"){
            return "Rings: Elf";
        }

        // Unambiguous hints for Dwarf on Earth: short or bulky
        //if (planet == "EARTH" && (hasTrait("SHORT") || hasTrait("BULKY"))){
        //    return "Rings: Dwarf";
        //}

        if (hasTrait("POINTY_EARS")){
            return "Rings: Elf";
        }


        // ambiguous - use scoring
        int star_wookie = 0;
        int star_ewok = 0;
        int marvel_asgardian = 0;
        int hitchhiker_betelgeusian = 0;
        int hitchhiker_vogon = 0;
        int rings_elf = 0;
        int rings_dwarf = 0;


        // check humanoid (only score when the field is present)
        if (isHumanoid.has_value()) {
            if (!isHumanoid.value()){
                star_ewok++;
                star_wookie++;
                hitchhiker_vogon++;
            } else {
                marvel_asgardian++;
                hitchhiker_betelgeusian++;
                rings_elf++;
                rings_dwarf++;
            }
        }

        if (hasTrait("TALL")){
            star_wookie++;
            marvel_asgardian++;
        }

        if (hasTrait("SHORT")){
            star_ewok++;
            rings_dwarf++;
        }

        if (hasTrait("BLONDE")){
            marvel_asgardian++;
            rings_elf++;
        }

        if (hasTrait("BULKY")){
            hitchhiker_vogon++;
            rings_dwarf++;
        }

        if (60 < age)
            star_ewok--;
        
        if (100 < age)
            hitchhiker_betelgeusian--;

        if (200 < age){
            hitchhiker_vogon--;
            rings_dwarf--;
        }

        if (400 < age)
            star_wookie--;
        
        if (5000 < age)
            marvel_asgardian--;

        int max_count = max({star_wookie, star_ewok, marvel_asgardian, hitchhiker_betelgeusian, hitchhiker_vogon, rings_elf, rings_dwarf});
        // If more than one category shares the max score, it's ambiguous -> Undefined
        std::vector<int> counts = {star_wookie, star_ewok, marvel_asgardian, hitchhiker_betelgeusian, hitchhiker_vogon, rings_elf, rings_dwarf};
        int ties = std::count(counts.begin(), counts.end(), max_count);
        if (ties > 1) return "Undefined";

        if (max_count == star_wookie){
            return "Star Wars: Wookie";
        }
        if (max_count == star_ewok){
            return "Star Wars: Ewok";
        }
        if (max_count == marvel_asgardian){
            return "Marvel: Asgardian";
        }
        if (max_count == hitchhiker_betelgeusian){
            return "Hitchhiker's: Betelgeusian";
        }
        if (max_count == hitchhiker_vogon){
            return "Hitchhiker's: Vogon";
        }
        if (max_count == rings_elf){
            return "Rings: Elf";
        }
        if (max_count == rings_dwarf){
            return "Rings: Dwarf";
        }

        return "Undefined";
    }

    // Construct from json
    explicit Individual(const json& j) {
        id = j.value("id", -1);
        // Robust originPlanet: prefer "originPlanet" then "planet". Normalize to uppercase.
        originPlanet = "unknown";
        if (j.contains("originPlanet") && !j["originPlanet"].is_null()) originPlanet = j["originPlanet"].get<string>();
        else if (j.contains("planet") && !j["planet"].is_null()) originPlanet = j["planet"].get<string>();
        // normalize to upper-case for consistent comparisons
        for (auto & c : originPlanet) c = toupper((unsigned char)c);

        // isHumanoid may be null
        if (j.contains("isHumanoid") && !j["isHumanoid"].is_null()) isHumanoid = j["isHumanoid"].get<bool>(); else isHumanoid.reset();

        // age may be null; default to 0 when unknown
        if (j.contains("age") && !j["age"].is_null()) age = j["age"].get<int>(); else age = 0;

        // physical traits: support both "physicalTraits" and legacy "traits", normalize to uppercase
        physicalTraits.clear();
        const char* traitsKeys[] = {"physicalTraits", "traits"};
        for (const char* key : traitsKeys) {
            if (j.contains(key) && !j[key].is_null() && j[key].is_array()) {
                for (const auto& t : j[key]) {
                    if (t.is_string()) {
                        string tr = t.get<string>();
                        for (auto & c : tr) c = toupper((unsigned char)c);
                        physicalTraits.push_back(tr);
                    }
                }
                break;
            }
        }
    }

};

class Universe {
private:
    string name;
    vector<Individual> individuals;
public:
    Universe(const string& name) : name(name) {}
    void addIndividual(const Individual& individual){
        individuals.push_back(individual);
    }
    const vector<Individual>& getIndividuals() const {
        return individuals;
    }
    string getName() const {
        return name;
    }

    void printAll() const {
        for (const auto& ind : individuals) ind.display();
    }

    void printIds() const {
        for (const auto& ind : individuals) cout << ind.getId() << "\n";
    }

    void printFilteredIds(bool even) const {
        for (const auto& ind : individuals) {
            int id = ind.getId();
            if (id < 0) continue;
            if (even) {
                if (id % 2 == 0) ind.display();
            } else {
                if (id % 2 != 0) ind.display();
            }
        }
    }
};

static void printCounts(const Universe& starWars,
                        const Universe& marvel,
                        const Universe& hitchhikers,
                        const Universe& rings,
                        const Universe& undefinedUni,
                        const Universe& mapped) {
    cout << "\n--- Classification counts ---\n";
    cout << "star-wars: " << starWars.getIndividuals().size() << '\n';
    cout << "marvel: " << marvel.getIndividuals().size() << '\n';
    cout << "hitch-hiker: " << hitchhikers.getIndividuals().size() << '\n';
    cout << "rings: " << rings.getIndividuals().size() << '\n';
    cout << "undefined: " << undefinedUni.getIndividuals().size() << '\n';
    cout << "total mapped: " << mapped.getIndividuals().size() << '\n';
}

int main(int argc, char* argv[]) {
    // Continue to JSON file demo using FileReader
    cout << "\n--- FileReader JSON demo ---\n";
    FileReader fr("resources/input_full.json");

    // Simple flow: read and parse without many checks (per user's request)
    fr.read();
    fr.parseJson();

    // Map JSON to internal classes
    const json& root = fr.getJson();
    Universe uni("mapped-universe");
    Universe starWars("star-wars");
    Universe marvel("marvel");
    Universe hitchhikers("hitch-hiker");
    Universe rings("rings");
    Universe undefined("undefined");
    // Support both top-level array files and objects with a "data" array
    const json* dataPtr = nullptr;
    if (root.is_array()) dataPtr = &root;
    else if (root.contains("data") && root["data"].is_array()) dataPtr = &root["data"];

    if (dataPtr) {
        for (const auto& entry : *dataPtr) {
            Individual ind(entry);
            uni.addIndividual(ind);
            // classify and distribute into simple containers
            string label = ind.classify();
            if (label.rfind("Star Wars", 0) == 0) starWars.addIndividual(ind);
            else if (label.rfind("Marvel", 0) == 0) marvel.addIndividual(ind);
            else if (label.rfind("Hitchhiker'", 0) == 0) hitchhikers.addIndividual(ind);
            else if (label.rfind("Rings", 0) == 0) rings.addIndividual(ind);
            else undefined.addIndividual(ind);
        }
    } else {
        cerr << "Warning: no data array found in input JSON\n";
    }

    // Print a compact counts summary
    printCounts(starWars, marvel, hitchhikers, rings, undefined, uni);

    //cout << "\n--- Mapped Individuals (display) ---\n";
    //uni.printAll();
    return 0;
    cout << "\n--- Classified: Star Wars ---\n";
    starWars.printAll();
    cout << "\n--- Classified: Marvel ---\n";
    marvel.printAll();
    cout << "\n--- Classified: Hitchhiker's ---\n";
    hitchhikers.printAll();
    cout << "\n--- Classified: Rings ---\n";
    rings.printAll();
    cout << "\n--- Classified: Undefined ---\n";
    undefined.printAll();

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
