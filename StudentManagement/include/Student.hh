#ifndef STUDENT_HH
#define STUDENT_HH
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

struct Date{
    int day;
    int month;
    int year;
};

class Student{
private:
    string firstName;
    string lastName;
    string email;
    Date enrolmentDate;
    Date dateOfBirth;

public:
    Student(string fname,string lname,string email,Date edate,Date dbirth)
        : firstName(std::move(fname)),
          lastName(std::move(lname)),
          email(std::move(email)),
          enrolmentDate(edate),
          dateOfBirth(dbirth) {}

    string getFirstName() const { return firstName; }
    string getLastName()  const { return lastName;  }
    string getEmail()     const { return email;     }
    Date   getEnrolmentDate() const { return enrolmentDate; }
    Date   getDateOfBirth()   const { return dateOfBirth;   }
};


#endif //STUDENT_HH
