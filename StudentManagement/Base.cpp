#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include <filesystem>
#include "include/Helpers.hh"

using namespace std;

int main(){

    uni.addFaculty("Faculty of Computers, Informatics and Microelectronics",
                    "FCIM", SOFTWARE_ENGINEERING);
    uni.addFaculty("Faculty of Mechanical Engineering",
                    "FIMIT", MECHANICAL_ENGINEERING);

    // students
    Date en1{1, 9, 2024};  Date b1{15, 6, 2005};
    Student s1("Robert", "Robertson", "robert.robertson@isa.utm.md", en1, b1);
    uni.addStudentToFaculty("FCIM", s1);

    Date en2{1, 9, 2022};  Date b2{2, 2, 2004};
    Student s2("Track", "Star", "track.star@isa.utm.md", en2, b2);
    uni.addStudentToFaculty("FIMIT", s2);

    //Menu loops
    while (true){
        cout << "\nWelcome to TUM's student management system!\n";
        cout << "What do you want to do?\n";
        cout << "General operations - g\n";
        cout << "Faculty operations - f\n";
        cout << "Quit Program - q\n\n";
        cout << "your input> ";

        char choice;
        if (!(cin >> choice)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 'q') break;
        else if (choice == 'g') generalOperationsLoop(uni);
        else if (choice == 'f') facultyOperationsLoop(uni);
        else cout << "Unknown option\n";
    }

    cout << "Goodbye!\n";
    return 0;
}