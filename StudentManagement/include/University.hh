#ifndef UNIVERSITY_HH
#define UNIVERSITY_HH
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
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
        cout << "Succesfully added new faculty " << n
             << " (" << a << ")" << endl;
    }

    string findStudentByEmail(const string& email){
        for (auto& f : faculties)
            if (f.belongTo(email))
                return f.getName();
        return "Not found";
    }

    void displayFaculties() const{
        cout << "Faculties:\n";
        for (const auto& f : faculties)
            cout << " - " << f.getName()
                 << " (" << f.getAbbreviation() << ")" << endl;
    }

    void displayFacultiesWithField(StudyField studyField) const{
        cout << "Faculties with field " << studyField << ":\n";
        for (const auto& f : faculties)
            if (f.getStudyField() == studyField)
                cout << " - " << f.getName()
                     << " (" << f.getAbbreviation() << ")" << endl;
    }

    void addStudentToFaculty(const string& facultyAbbr, const Student& student){
        Faculty* f = findFacultyByAbbreviation(facultyAbbr);
        if (!f){
            cout << "Faculty with abbreviation " << facultyAbbr << " not found\n";
            return;
        }
        f->addStudent(student);
    }

    void graduateStudentByEmail(const string& email){
        for (auto& f : faculties){
            if (f.belongTo(email)){
                f.graduateByEmail(email);
                cout << "Succesfully graduted\n";
                return;
            }
        }
        cout << "Student with email " << email << " not found in any faculty\n";
    }

    void displayStudents(const string& facultyAbbr){
        Faculty* f = findFacultyByAbbreviation(facultyAbbr);
        if (!f){
            cout << "Faculty with abbreviation " << facultyAbbr << " not found\n";
            return;
        }
        f->displayStudents();
    }

    void displayGraduates(const string& facultyAbbr){
        Faculty* f = findFacultyByAbbreviation(facultyAbbr);
        if (!f){
            cout << "Faculty with abbreviation " << facultyAbbr << " not found\n";
            return;
        }
        f->displayGraduates();
    }

    void checkBelongsToFaculty(const string& facultyAbbr, const string& email){
        Faculty* f = findFacultyByAbbreviation(facultyAbbr);
        if (!f){
            cout << "Faculty with abbreviation " << facultyAbbr << " not found\n";
            return;
        }
        if (f->belongTo(email))
            cout << "Student " << email
                 << " belongs to faculty " << f->getName() << endl;
        else
            cout << "Student " << email
                 << " does NOT belong to faculty " << f->getName() << endl;
    }
};

#endif //UNIVERSITY_HH
