#include <iostream>
#include <string>
#include <vector>

#include "include/Display.hpp"
#include "include/Assistant.hh"

using namespace std;

int main() {
    Display dell(1920, 1080, 90.5, "Dell");
    Display hp(2560, 1440, 110.2, "HP");
    Display samsung(3840, 2160, 160.0, "Samsung");
    Display lg(2560, 1440, 120.0, "LG");

    Assistant alex("Alex");
    alex.assignDisplay(dell);
    alex.assignDisplay(hp);
    alex.assignDisplay(samsung);
    alex.assignDisplay(lg);

    alex.assist();
    Display existing(3840, 2160, 160.0, "Samsung");
    Display non_existing(3840, 2160, 170.0, "Samsung");
    alex.buyDisplay(existing);
    alex.buyDisplay(non_existing);
    alex.assist();

    return 0;
}