#include <iostream>
#include <string>
#include "include/Display.hpp"

using namespace std;

int main(){
  Display display_1(200, 90, 0.6, "Samsung");
    Display display_2(120, 110, 0.5, "Panasonic");
    Display display_3(220, 50, 0.6, "LG");
  display_1.compareSize(display_2);
    display_1.compareSharpness(display_2);
    display_1.compareWithMonitor(display_3);
}