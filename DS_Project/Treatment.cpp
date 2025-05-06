#include"Treatment.h"
#include"Resources.h"
#include"Patient.h"
#include"Schedular.h"


Treatment::Treatment() :type(' '), duration(0) {}  // Initialize members
Treatment::~Treatment() {}  // Empty destructor unless needed

void Treatment::SetDuration(int time)
{
    duration = time;
}

Resources* Treatment::GetResource() const
{
    return curr_treatment;
}

void Treatment::setResource(Resources*& r)
{
    curr_treatment = r;
}

void Treatment::setAssignmentTime(int time)
{
    assignmentTime = time;
}

int Treatment::GetDuration() const
{
    return duration;
}

void Treatment::setType(char t)
{
    type = t;
}

char Treatment::getType() const
{
    return type;
}

bool Treatment::canAssign(Resources* r)
{
    return r ==  nullptr ? false : true;
}


void Treatment::MoveTOWAoting(Patient*& p, Schedular* sch)
{
    sch->moveFromEarlyOrLate(p);

}

ostream& operator<<(ostream& os, const Treatment& p)
{
    os << p.getType();
    return os;
}
