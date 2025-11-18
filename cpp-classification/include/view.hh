#pragma once

#include "nlohmann/json.hpp"
#include "universe.hh"
#include <fstream>

using json = nlohmann::json;
using namespace std;

class View {
public:
    static json individualToJson(const Individual& ind) {
        json j;
        j["id"] = ind.getId();
        if (ind.getIsHumanoid().has_value()) j["isHumanoid"] = ind.getIsHumanoid().value(); else j["isHumanoid"] = nullptr;
        auto op = ind.getOriginPlanetOpt();
        if (op.has_value()) j["originPlanet"] = op.value(); else j["originPlanet"] = nullptr;
        auto a = ind.getAgeOpt();
        if (a.has_value()) j["age"] = a.value(); else j["age"] = nullptr;
        auto pt = ind.getPhysicalTraitsOpt();
        if (pt.has_value()) j["physicalTraits"] = pt.value(); else j["physicalTraits"] = nullptr;
        return j;
    }

    static json universeToJson(const Universe& uni) {
        json j;
        j["name"] = uni.getName();
        j["individuals"] = json::array();
        for (const auto& ind : uni.getIndividuals()) j["individuals"].push_back(individualToJson(ind));
        return j;
    }

    static bool writeToFile(const Universe& uni, const string& path) {
        ofstream out(path);
        if (!out) return false;
        out << universeToJson(uni).dump(4) << endl;
        return true;
    }
};
