#ifndef FACULTY_HH
#define FACULTY_HH
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include "Student.hh"

using namespace std;

enum StudyField{
    MECHANICAL_ENGINEERING,
    SOFTWARE_ENGINEERING,
    FOOD_TECHNOLOGY,
    URBANISM_ARCHITECTURE,
    VETERINARY_MEDICINE
};

class Faculty{
private:
    string name;
    string abbreviation;
    vector<Student> students;
    vector<Student> graduates;
    StudyField studyField;

    string transformDate(const Date& date) const {
        return to_string(date.day) + "/" +
               to_string(date.month) + "/" +
               to_string(date.year);
    }

public:
    Faculty(string name, string abbreviation, StudyField field)
        : name(std::move(name)),
          abbreviation(std::move(abbreviation)),
          studyField(field) {}

    Faculty(string n, string a, vector<Student> s, vector<Student> g, StudyField sF)
        : name(std::move(n)),
          abbreviation(std::move(a)),
          students(std::move(s)),
          graduates(std::move(g)),
          studyField(std::move(sF)) {}

    string getName() const          { return name; }
    string getAbbreviation() const  { return abbreviation; }
    vector<Student> getStudents() const   { return students; }
    vector<Student> getGraduates() const  { return graduates; }
    StudyField getStudyField() const      { return studyField; }

    void addStudent(const Student& student){
        students.push_back(student);
        cout << "Added student " << student.getFirstName() << " "
             << student.getLastName() << " to " << abbreviation << endl;
    }

    bool belongTo(const string& email) const{
        for (const auto& s : students)
            if (s.getEmail() == email)
                return true;
        return false;
    }

    void graduateByEmail(const string& email) {
        auto it = students.end();
        for (auto i = students.begin(); i != students.end(); ++i) {
            if (i->getEmail() == email) { it = i; break; }
        }
        if (it != students.end()) {
            graduates.push_back(*it);
            cout << "Student " << it->getFirstName() << " " << it->getLastName()
                 << " succesfully graduated from " << abbreviation << endl;
            students.erase(it);
        } else {
            cout << "Student with email " << email
                 << " not found in faculty " << abbreviation << endl;
        }
    }

    void displayStudents() const {
        if (students.empty()) {
            cout << "No enrolled students in " << abbreviation << endl;
            return;
        }
        for(const auto& s: students){
            cout << "Student first name: " << s.getFirstName() << "\n"
                 << "Student last name: " << s.getLastName() << "\n"
                 << "Student email: " << s.getEmail() << "\n"
                 << "Student enrolment date: " << transformDate(s.getEnrolmentDate()) << "\n"
                 << "Student date of birth: " << transformDate(s.getDateOfBirth()) << "\n\n";
        }
    }

    void displayGraduates() const {
        if (graduates.empty()) {
            cout << "No graduates in " << abbreviation << endl;
            return;
        }
        for (const auto& s : graduates){
            cout << "Graduate first name: " << s.getFirstName() << "\n"
                 << "Graduate last name: " << s.getLastName() << "\n"
                 << "Graduate email: " << s.getEmail() << "\n"
                 << "Graduate enrolment date: " << transformDate(s.getEnrolmentDate()) << "\n"
                 << "Graduate date of birth: " << transformDate(s.getDateOfBirth()) << "\n\n";
        }
    }
};
#endif //FACULTY_HH
