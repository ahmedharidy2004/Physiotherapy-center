#ifndef TREATMENT_H
#define TREATMENT_H
#include <iostream>
class Resources;
class Patient;
class Schedular;
using namespace std;

class Treatment {
private:
    char type;
    int duration;
    int assignmentTime;
    Resources* curr_treatment;
public:
    void SetDuration(int time);
    Resources* GetResource() const;
    void setResource(Resources*& r);
    void setAssignmentTime(int time);
    int GetDuration() const;
    void setType(char t);
    char getType() const;
    friend ostream& operator<<(ostream& os, const Treatment& p);
    static bool canAssign(Resources* r);
    void MoveTOWAoting(Patient*& p, Schedular* sch);
    Treatment();
    ~Treatment();
};

#endif // TREATMENT_H