#ifndef TREATMENT_H
#define TREATMENT_H

#include <iostream>
#include "Resources.h"
using namespace std;

class Treatment {
private:
    char type;
    int duration;
    int assignmentTime;
    Resources* curr_treatment;
public:
    Treatment() :type(' '), duration(0) {}  // Initialize members
    ~Treatment() {}  // Empty destructor unless needed

    // Setters
    void SetDuration(int time) { duration = time; }

    // Getters
    Resources* GetResource() const {
        return curr_treatment;
    }
    int GetDuration() const {
        return duration;
    }  // Fixed return type from char to int
    void setType(char t) {
        type = t;
    }
    char getType() const {
        return type;
    }
    friend ostream& operator<<(ostream& os, const Treatment& p) {
        os <<p.getType();
               return os;
    }

};

#endif // TREATMENT_H