#ifndef CAR_HPP
#define CAR_HPP

#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

struct Car {
    int id{};
    string type;
    string passengers;
    bool isDining{};
    int consumption{};

    // Helper to parse from JSON (keeping it simple for now)
    static bool fromJson(const json& j, Car& c) {
        try {
            c.id = j.at("id").get<int>();
            c.type = j.at("type").get<string>();
            c.passengers = j.at("passengers").get<string>();
            c.isDining = j.at("isDining").get<bool>();
            c.consumption = j.at("consumption").get<int>();
            return true;
        } catch (...) {
            return false;
        }
    }
};

#endif // CAR_HPP
