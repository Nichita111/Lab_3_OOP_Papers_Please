#ifndef FACULTY_HH
#define FACULTY_HH
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include "Utils.hh"
#include "Student.hh"

using namespace std;

class Faculty{
private:
    string name;
    string abbreviation;
    vector<Student> students;
    vector<Student> graduates;
    StudyField studyField;

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
            students.erase(it);
        }
    }

};
#endif //FACULTY_HH
