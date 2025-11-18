#include <iostream>
#include "../include/nlohmann/json.hpp"
#include "../include/file_reader.hh"
#include "../include/individual.hh"
#include "../include/universe.hh"
#include "../include/view.hh"

using json = nlohmann::json;
using namespace std;

int main(int argc, char* argv[]) {
    // Simple main: read, classify and write outputs
    FileReader fr("resources/input_full.json");
    fr.read();
    fr.parseJson();

    const json& root = fr.getJson();
    Universe uni("mapped-universe");
    Universe starWars("star-wars");
    Universe marvel("marvel");
    Universe hitchhikers("hitch-hiker");
    Universe rings("rings");
    Universe undefined("undefined");

    const json* dataPtr = nullptr;
    if (root.is_array()) dataPtr = &root;
    else if (root.contains("data") && root["data"].is_array()) dataPtr = &root["data"];

    if (dataPtr) {
        for (const auto& entry : *dataPtr) {
            Individual ind(entry);
            uni.addIndividual(ind);
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

    // Print counts for each universe
    cout << "\n--- Classification counts ---\n";
    cout << "star-wars: " << starWars.getIndividuals().size() << '\n';
    cout << "marvel: " << marvel.getIndividuals().size() << '\n';
    cout << "hitch-hiker: " << hitchhikers.getIndividuals().size() << '\n';
    cout << "rings: " << rings.getIndividuals().size() << '\n';
    cout << "undefined: " << undefined.getIndividuals().size() << '\n';
    cout << "total mapped: " << uni.getIndividuals().size() << '\n';

    // Write outputs
    bool ok = true;
    ok &= View::writeToFile(starWars, "resources/output/star-wars.json");
    ok &= View::writeToFile(marvel, "resources/output/marvel.json");
    ok &= View::writeToFile(hitchhikers, "resources/output/hitch-hiker.json");
    ok &= View::writeToFile(rings, "resources/output/rings.json");

    if (ok) cout << "Wrote classification outputs to resources/output/\n";
    else cerr << "Warning: failed to write one or more output files\n";

    return 0;
}
