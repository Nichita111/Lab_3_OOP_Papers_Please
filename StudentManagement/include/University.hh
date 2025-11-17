#ifndef UNIVERSITY_HH
#define UNIVERSITY_HH
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include "Utils.hh"
#include "Faculty.hh"

using namespace std;

class manageUniversity{
private:
    string name;
    vector<Faculty> faculties;

    Faculty* findFacultyByAbbreviation(const string& abbr){
        for (auto& f : faculties)
            if (f.getAbbreviation() == abbr)
                return &f;
        return nullptr;
    }

public:
    manageUniversity(string name) : name(std::move(name)) {}

    manageUniversity(string name, vector<Faculty> faculties)
        : name(std::move(name)), faculties(std::move(faculties)) {}

    const vector<Faculty>& getFaculties() const { return faculties; }

    void addFaculty(const string& n, const string& a, StudyField field){
        faculties.emplace_back(n, a, field);
    }

    string findStudentByEmail(const string& email){
        for (auto& f : faculties)
            if (f.belongTo(email))
                return f.getName();
        return "Not found";
    }


    bool addStudentToFaculty(const string& facultyAbbr, const Student& student){
        Faculty* f = findFacultyByAbbreviation(facultyAbbr);
        if (!f){
            return false;
        }
        f->addStudent(student);
        return true;
    }

    string graduateStudentByEmail(const string& email){
        for (auto& f : faculties){
            if (f.belongTo(email)){
                f.graduateByEmail(email);
                return f.getAbbreviation();
            }
        }
        return "";
    }

    vector<Student> displayStudents(const string& facultyAbbr){
        Faculty* f = findFacultyByAbbreviation(facultyAbbr);
        return f->getStudents();
    }

    vector<Student> displayGraduates(const string& facultyAbbr){
        Faculty* f = findFacultyByAbbreviation(facultyAbbr);
        return f->getGraduates();
    }

    bool checkBelongsToFaculty(const string& facultyAbbr, const string& email){
        Faculty* f = findFacultyByAbbreviation(facultyAbbr);
        if (f->belongTo(email))
            return true;
        else
            return false;
    }
};

#endif //UNIVERSITY_HH
