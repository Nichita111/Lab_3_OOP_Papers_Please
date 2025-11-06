

#ifndef ASSISTANT_HH
#define ASSISTANT_HH
#include <iostream>
#include <string>
#include <vector>

#include "Display.hpp"

using namespace std;

class Assistant {
private:
    string assistantName;
    vector<Display> assignedDisplays;

    bool compare(Display a, Display b) {
        float eps = 0.00001;
        return a.getWidth() == b.getWidth() &&
            a.getHeight() == b.getHeight() &&
                fabs(a.getPPI() - b.getPPI()) < eps &&
                a.getModel() == b.getModel();
    }

public:
    Assistant(string name) {
        this->assistantName = name;
    }

    auto getName() {
        return assistantName;
    }

    auto setName(string name) {
        assistantName = move(name);
    }

    void assignDisplay(Display& d) {
        assignedDisplays.push_back(d);
    }

    void assist() {
        cout << "Assistant is comparing all assigned displays:\n\n";
        for (int i = 0; i < assignedDisplays.size(); i++) {
            Display compared_display = assignedDisplays[i];
            for (int j = i + 1; j < assignedDisplays.size(); j++) {
                Display comparable_display = assignedDisplays[j];
                compared_display.compareWithMonitor(comparable_display);
            }
        }
        cout << endl;
    }

    Display buyDisplay(const Display& d) {
        for (auto it = assignedDisplays.begin(); it != assignedDisplays.end(); it++) {
            if (compare(*it, d)) {     // compare by model name
                Display bought = *it;                 // make a copy to return
                assignedDisplays.erase(it);           // remove from vector
                cout << "You bought: " << bought.getModel() << "\n\n";
                return bought;
            }
        }

        cout << "Display not found: " << d.getModel() << "\n";
        return Display(0, 0, 0, "Unknown");
    }

};
#endif //ASSISTANT_HH
