

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
    vector<Task_1> assignedDisplays;

    bool compare(Task_1 a, Task_1 b) {
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

    void assignDisplay(Task_1& d) {
        assignedDisplays.push_back(d);
    }

    void assist() {
        cout << "Assistant is comparing all assigned displays:\n\n";
        for (int i = 0; i < assignedDisplays.size(); i++) {
            Task_1 compared_display = assignedDisplays[i];
            for (int j = i + 1; j < assignedDisplays.size(); j++) {
                Task_1 comparable_display = assignedDisplays[j];
                compared_display.compareWithMonitor(comparable_display);
            }
        }
        cout << endl;
    }

    Task_1 buyDisplay(const Task_1& d) {
        for (auto it = assignedDisplays.begin(); it != assignedDisplays.end(); it++) {
            if (compare(*it, d)) {     // compare by model name
                Task_1 bought = *it;                 // make a copy to return
                assignedDisplays.erase(it);           // remove from vector
                cout << "You bought: " << bought.getModel() << "\n\n";
                return bought;
            }
        }

        cout << "Display not found: " << d.getModel() << "\n";
        return Task_1(0, 0, 0, "Unknown");
    }

};
#endif //ASSISTANT_HH
