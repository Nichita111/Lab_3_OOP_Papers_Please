//
// Created by Nikita on 13/11/2025.
//

#ifndef HELPERS_HH
#define HELPERS_HH
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include "University.hh"
#include "Utils.hh"

using namespace std;

void generalOperationsLoop(manageUniversity& uni){
    while (true){
        cout << "\nGeneral operations\n";
        cout << "What do you want to do?\n";
        cout << "Create faculty - nf/<faculty name>/<faculty abbreviation>/<field>\n";
        cout << "Search student and show faculty - ss/<student email>\n";
        cout << "Display faculties - df\n";
        cout << "Display all faculties of a field - df/<field>\n";
        cout << "Back - b\n";
        cout << "Quit Program - q\n\n";
        cout << "your input> ";

        string line;
        if (!getline(cin, line)) return;
        if (line == "b") break; //BACK
        if (line == "q") exit(0); //QUIT

        // DISPLAY FACULTY
        if (line == "df"){
            vector<Faculty> faculties = uni.getFaculties();
            cout << "Faculties:\n";
            for (const auto& f : faculties)
                cout << " - " << f.getName()
                     << " (" << f.getAbbreviation() << ")" << endl;

            // NEW FACULTY
        } else if (line.rfind("nf/", 0) == 0){
            auto parts = split(line, '/');      // nf/name/abbr/field
            if (parts.size() != 4){
                cout << "Invalid nf command format\n";
                continue;
            }
            StudyField field = parseField(parts[3]);
            uni.addFaculty(parts[1], parts[2], field);
            cout << "Succesfully added new faculty " << parts[1]
             << " (" << parts[2] << ")" << endl;

            // DISPLAY FACULTY WITH A FILED
        } else if (line.rfind("df/", 0) == 0){
            auto parts = split(line, '/');      // df/field
            if (parts.size() != 2){
                cout << "Invalid df/<field> command format\n";
                continue;
            }
            StudyField field = parseField(parts[1]);
            vector<Faculty> faculties = uni.getFaculties();
            cout << "Faculties with field " << field << ":\n";
            for (const auto& f : faculties)
                if (f.getStudyField() == field)
                    cout << " - " << f.getName()
                         << " (" << f.getAbbreviation() << ")" << endl;

            // SEARCH STUDENT
        } else if (line.rfind("ss/", 0) == 0){
            auto parts = split(line, '/');      // ss/email
            if (parts.size() != 2){
                cout << "Invalid ss command format\n";
                continue;
            }
            string facultyName = uni.findStudentByEmail(parts[1]);
            if (facultyName == "Not found")
                cout << "Student with email " << parts[1]
                     << " not found in any faculty\n";
            else
                cout << "Student with email " << parts[1]
                     << " belongs to faculty " << facultyName << endl;

        } else {
            cout << "Unknown command in General operations\n";
        }
    }
}

void facultyOperationsLoop(manageUniversity& uni){
    while (true){
        cout << "\nFaculty operations\n";
        cout << "What do you want to do?\n";
        cout << "Create students - ns/<faculty abbreviation>/<first name>/<last name>/<email>/<day>/<month>/<year>\n";
        cout << "Graduate student - gs/<email>\n";
        cout << "Display enrolled students - ds/<faculty abbreviation>\n";
        cout << "Display graduated students - dg/<faculty abbreviation>\n";
        cout << "Check if student belongs to faculty - bf/<faculty abbreviation>/<email>\n";
        cout << "Back - b\n";
        cout << "Quit Program - q\n\n";
        cout << "your input> ";

        string line;
        if (!getline(cin, line)) return;
        if (line == "b") break; //BACK
        if (line == "q") exit(0); //QUIT

        // NEW STUDENT
        if (line.rfind("ns/", 0) == 0){
            auto parts = split(line, '/');
            // ns/abbr/fname/lname/email/day/month/year
            if (parts.size() != 8){
                cout << "Invalid ns command format\n";
                continue;
            }
            string abbr      = parts[1];
            string firstName = parts[2];
            string lastName  = parts[3];
            string email     = parts[4];
            int    day       = stoi(parts[5]);
            int    month     = stoi(parts[6]);
            int    year      = stoi(parts[7]);

            Date enrol{1, 9, 2025};
            Date birth{day, month, year};
            Student s(firstName, lastName, email, enrol, birth);
            bool added_user = uni.addStudentToFaculty(abbr, s);
            if (added_user)
                cout << "Added student " << s.getFirstName() << " "
                 << s.getLastName() << " to " << abbr << endl;
            else
                cout << "Faculty with abbreviation " << abbr << " not found\n";


            // GRADUATE STUDENT
        } else if (line.rfind("gs/", 0) == 0){
            auto parts = split(line, '/');
            if (parts.size() != 2){
                cout << "Invalid gs command format\n";
                continue;
            }
            string graduated = uni.graduateStudentByEmail(parts[1]);
            if (graduated != "")
                cout << "Succesfully graduted from "<< graduated << "\n";
            else
                cout << "Student not found in any faculty\n";

            //DISPLAY STUDENT
        } else if (line.rfind("ds/", 0) == 0){
            auto parts = split(line, '/');
            if (parts.size() != 2){
                cout << "Invalid ds command format\n";
                continue;
            }
            auto abbr = parts[1];
            vector<Student> students = uni.displayStudents(abbr);
            if (students.empty()) {
                cout << "No enrolled students in " << abbr << endl;
            }

            for (const auto& s : students) {
                cout << "Student first name: " << s.getFirstName() << "\n"
                     << "Student last name: " << s.getLastName() << "\n"
                     << "Student email: " << s.getEmail() << "\n"
                     << "Student enrolment date: " << transformDate(s.getEnrolmentDate()) << "\n"
                     << "Student date of birth: " << transformDate(s.getDateOfBirth()) << "\n\n";
            }


            // DISPLAY GRADUATE
        } else if (line.rfind("dg/", 0) == 0){
            auto parts = split(line, '/');
            if (parts.size() != 2){
                cout << "Invalid dg command format\n";
                continue;
            }

            auto abbr = parts[1];

            vector<Student> graduates = uni.displayGraduates(abbr);
            if (graduates.empty()) {
                cout << "No graduates in " << abbr << endl;
            }

            for (const auto& s : graduates) {
                cout << "Graduate first name: " << s.getFirstName() << "\n"
                     << "Graduate last name: " << s.getLastName() << "\n"
                     << "Graduate email: " << s.getEmail() << "\n"
                     << "Graduate enrolment date: " << transformDate(s.getEnrolmentDate()) << "\n"
                     << "Graduate date of birth: " << transformDate(s.getDateOfBirth()) << "\n\n";
            }


            // BELONG TO FACULTY
        } else if (line.rfind("bf/", 0) == 0){
            auto parts = split(line, '/');
            if (parts.size() != 3){
                cout << "Invalid bf command format\n";
                continue;
            }
            bool belong = uni.checkBelongsToFaculty(parts[1], parts[2]);
            if (belong)
                cout << "Student " << parts[2]
                 << " belongs to faculty " << parts[1] << endl;
            else
                cout << "Student " << parts[2]
                 << " does NOT belong to faculty " << parts[1] << endl;

        } else {
            cout << "Unknown command in Faculty operations\n";
        }
    }
}


#endif //HELPERS_HH
