#include <iostream>
#include <string>
#include <vector>

#include "Display.hpp"
#include "Assistant.hh"

using namespace std;

int main() {
    Task_1 dell(1920, 1080, 90.5, "Dell");
    Task_1 hp(2560, 1440, 110.2, "HP");
    Task_1 samsung(3840, 2160, 160.0, "Samsung");
    Task_1 lg(2560, 1440, 120.0, "LG");

    Assistant alex("Alex");
    alex.assignDisplay(dell);
    alex.assignDisplay(hp);
    alex.assignDisplay(samsung);
    alex.assignDisplay(lg);

    alex.assist();
    Task_1 existing(3840, 2160, 160.0, "Samsung");
    Task_1 non_existing(3840, 2160, 170.0, "Samsung");
    alex.buyDisplay(existing);
    alex.buyDisplay(non_existing);
    alex.assist();

    return 0;
}