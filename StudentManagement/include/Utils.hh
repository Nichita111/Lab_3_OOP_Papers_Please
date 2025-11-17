#ifndef UTILS_HH
#define UTILS_HH
#include <string>
#include "Student.hh"

using namespace std;

enum StudyField{
    MECHANICAL_ENGINEERING,
    SOFTWARE_ENGINEERING,
    FOOD_TECHNOLOGY,
    URBANISM_ARCHITECTURE,
    VETERINARY_MEDICINE
};

inline string transformDate(const Date& date) {
    return to_string(date.day) + "/" +
           to_string(date.month) + "/" +
           to_string(date.year);
}


inline StudyField parseField(const string& fieldStr){
    if (fieldStr == "MECHANICAL_ENGINEERING") return MECHANICAL_ENGINEERING;
    if (fieldStr == "SOFTWARE_ENGINEERING")   return SOFTWARE_ENGINEERING;
    if (fieldStr == "FOOD_TECHNOLOGY")        return FOOD_TECHNOLOGY;
    if (fieldStr == "URBANISM_ARCHITECTURE")  return URBANISM_ARCHITECTURE;
    if (fieldStr == "VETERINARY_MEDICINE")    return VETERINARY_MEDICINE;
    throw invalid_argument("Unknown field: " + fieldStr);
}

inline vector<string> split(const string& s, char delim) {
    vector<string> out; string cur; stringstream ss(s);
    while (getline(ss, cur, delim)) out.push_back(cur);
    if (!s.empty() && s.back()==delim) out.emplace_back(""); // keep trailing empty
    return out;
}

inline string fieldToString(StudyField f) {
    switch (f) {
        case MECHANICAL_ENGINEERING:  return "MECHANICAL_ENGINEERING";
        case SOFTWARE_ENGINEERING:    return "SOFTWARE_ENGINEERING";
        case FOOD_TECHNOLOGY:         return "FOOD_TECHNOLOGY";
        case URBANISM_ARCHITECTURE:   return "URBANISM_ARCHITECTURE";
        case VETERINARY_MEDICINE:     return "VETERINARY_MEDICINE";
    }
    return "SOFTWARE_ENGINEERING";
}
inline StudyField fieldFromString(const string& s) {
    if (s=="MECHANICAL_ENGINEERING")  return MECHANICAL_ENGINEERING;
    if (s=="SOFTWARE_ENGINEERING")    return SOFTWARE_ENGINEERING;
    if (s=="FOOD_TECHNOLOGY")         return FOOD_TECHNOLOGY;
    if (s=="URBANISM_ARCHITECTURE")   return URBANISM_ARCHITECTURE;
    return VETERINARY_MEDICINE;
}

inline string studentToLine(const Student& st) {
    const Date e = st.getEnrolmentDate();
    const Date b = st.getDateOfBirth();
    // first|last|email|eD|eM|eY|bD|bM|bY
    ostringstream os;
    os << st.getFirstName() << '|'
        << st.getLastName()  << '|'
        << st.getEmail()     << '|'
        << e.day << '|' << e.month << '|' << e.year << '|'
        << b.day << '|' << b.month << '|' << b.year;
    return os.str();
}
inline Student studentFromParts(const vector<string>& p) {
    // p: first last email eD eM eY bD bM bY
    Date enrol{ stoi(p[3]), stoi(p[4]), stoi(p[5]) };
    Date birth{ stoi(p[6]), stoi(p[7]), stoi(p[8]) };
    return Student(p[0], p[1], p[2], enrol, birth);
}

#endif //UTILS_HH
