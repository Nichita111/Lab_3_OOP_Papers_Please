#pragma once

#include "nlohmann/json.hpp"
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <iostream>

using json = nlohmann::json;
using namespace std;

class Individual {
private:
    int id;
    optional<bool> isHumanoid;
    optional<string> originPlanet; // optional to preserve null vs value
    optional<int> age; // optional so we can encode null when unknown
    optional<vector<string>> physicalTraits; // optional to allow null vs empty

public:
    Individual(int id, optional<bool> isHumanoidVal, const optional<string>& originPlanetVal, optional<int> ageVal, const optional<vector<string>>& physicalTraitsVal)
        : id(id), isHumanoid(isHumanoidVal), originPlanet(originPlanetVal), age(ageVal), physicalTraits(physicalTraitsVal) {}

    int getId() const { return id; }

    optional<bool> getIsHumanoid() const { return isHumanoid; }

    optional<string> getOriginPlanetOpt() const { return originPlanet; }
    optional<int> getAgeOpt() const { return age; }
    optional<vector<string>> getPhysicalTraitsOpt() const { return physicalTraits; }

    // helpers used for classification: provide normalized values with sensible defaults
    string getOriginPlanetUpper() const {
        if (!originPlanet.has_value()) return string("UNKNOWN");
        string p = originPlanet.value();
        for (auto & c : p) c = toupper((unsigned char)c);
        return p;
    }

    int getAgeOrDefault() const { return age.has_value() ? age.value() : 0; }

    vector<string> getPhysicalTraitsVec() const { return physicalTraits.has_value() ? physicalTraits.value() : vector<string>{}; }

    void setIsHumanoid(optional<bool> value) { isHumanoid = value; }
    void setOriginPlanet(const optional<string>& planet) { originPlanet = planet; }
    void setAge(const optional<int>& newAge) { age = newAge; }
    void addTrait(const string& trait) { if (!physicalTraits.has_value()) physicalTraits = vector<string>{}; physicalTraits->push_back(trait); }
    bool removeTrait(const string& trait) { if (!physicalTraits.has_value()) return false; auto &vec = *physicalTraits; auto it = remove(vec.begin(), vec.end(), trait); bool removed = it != vec.end(); vec.erase(it, vec.end()); if (vec.empty()) physicalTraits.reset(); return removed; }

    void display() const {
       cout << "ID: " << id << "\n";
       cout << "Humanoid: ";
       if (isHumanoid.has_value()) cout << (isHumanoid.value() ? "Yes" : "No"); else cout << "unknown";
       cout << "\n";
       cout << "Origin Planet: ";
       if (originPlanet.has_value()) cout << originPlanet.value(); else cout << "unknown";
       cout << "\n";
       cout << "Age: ";
       if (age.has_value()) cout << age.value(); else cout << "unknown";
       cout << "\n";
       cout << "Traits: ";
       if (physicalTraits.has_value()) {
           for (const auto& trait : physicalTraits.value()) cout << trait << " ";
       } else cout << "unknown";
       cout << "\n\n";
    }

    string classify() const {
        string planet = getOriginPlanetUpper();
        vector<string> traits = getPhysicalTraitsVec();
        auto hasTrait = [&](const string& trait) {
            return find(traits.begin(), traits.end(), trait) != traits.end();
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
        if (getAgeOrDefault() > 5000){
            return "Rings: Elf";
        }

        if (planet == "EARTH"){
            return "Rings: Elf";
        }

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

        if (60 < getAgeOrDefault())
            star_ewok--;
        
        if (100 < getAgeOrDefault())
            hitchhiker_betelgeusian--;

        if (200 < getAgeOrDefault()){
            hitchhiker_vogon--;
            rings_dwarf--;
        }

        if (400 < getAgeOrDefault())
            star_wookie--;
        
        if (5000 < getAgeOrDefault())
            marvel_asgardian--;

        int max_count = max({star_wookie, star_ewok, marvel_asgardian, hitchhiker_betelgeusian, hitchhiker_vogon, rings_elf, rings_dwarf});
        vector<int> counts = {star_wookie, star_ewok, marvel_asgardian, hitchhiker_betelgeusian, hitchhiker_vogon, rings_elf, rings_dwarf};
        int ties = count(counts.begin(), counts.end(), max_count);
        if (ties > 1) return "Undefined";

        if (max_count == star_wookie) return "Star Wars: Wookie";
        if (max_count == star_ewok) return "Star Wars: Ewok";
        if (max_count == marvel_asgardian) return "Marvel: Asgardian";
        if (max_count == hitchhiker_betelgeusian) return "Hitchhiker's: Betelgeusian";
        if (max_count == hitchhiker_vogon) return "Hitchhiker's: Vogon";
        if (max_count == rings_elf) return "Rings: Elf";
        if (max_count == rings_dwarf) return "Rings: Dwarf";

        return "Undefined";
    }

    // Construct from json
    explicit Individual(const json& j) {
        id = j.value("id", -1);
        originPlanet.reset();
        if (j.contains("originPlanet") && !j["originPlanet"].is_null()) {
            string p = j["originPlanet"].get<string>();
            for (auto & c : p) c = toupper((unsigned char)c);
            originPlanet = p;
        } else if (j.contains("planet") && !j["planet"].is_null()) {
            string p = j["planet"].get<string>();
            for (auto & c : p) c = toupper((unsigned char)c);
            originPlanet = p;
        } else {
            originPlanet.reset();
        }

        if (j.contains("isHumanoid") && !j["isHumanoid"].is_null()) isHumanoid = j["isHumanoid"].get<bool>(); else isHumanoid.reset();

        if (j.contains("age") && !j["age"].is_null()) age = j["age"].get<int>(); else age.reset();

        physicalTraits.reset();
        const char* traitsKeys[] = {"physicalTraits", "traits"};
        for (const char* key : traitsKeys) {
            if (j.contains(key) && !j[key].is_null() && j[key].is_array()) {
                vector<string> vec;
                for (const auto& t : j[key]) {
                    if (t.is_string()) {
                        string tr = t.get<string>();
                        for (auto & c : tr) c = toupper((unsigned char)c);
                        vec.push_back(tr);
                    }
                }
                physicalTraits = move(vec);
                break;
            }
        }
    }
};
