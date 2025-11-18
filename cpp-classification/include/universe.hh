#pragma once

#include <vector>
#include <string>
#include "individual.hh"

using namespace std;

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
