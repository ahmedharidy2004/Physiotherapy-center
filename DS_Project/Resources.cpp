#include"Resources.h"
int Resources::idE = 0;
int Resources::idU = 0;
int Resources::idR = 0;
char Resources::getType()
{
	return type;
}
int Resources::getID()
{
	return ID;
}
void Resources::setType(char t)
{
	type = t;
}
void Resources::setID(int id)
{
	ID = id;

}
void Resources::setCapacity(int cap)
{
	capacity = cap;

}
int Resources::getCapacity() const
{
	return capacity;
}
void Resources::setRealCapacity(int cap)
{
	RealCapcityOfRoom = cap;
}
int Resources::getRealCapacity() const
{
	return RealCapcityOfRoom;
}
char Resources::getType() const
{
	return type;
}
Resources::Resources(char A = ' ') {
	capacity = 1;
	type = A;
	if (type == 'E')
	{
		idE++;
		ID = idE;
	}
	else if (type == 'U')
	{
		idU++;


		ID = idU;
	}
	else
	{
		idR++;
		ID = idR;
	}
	RealCapcityOfRoom = 0;
}

Resources::~Resources()
{
}

ostream& operator<<(ostream& os, const Resources& p)
{
	if (p.getType() == 'R')
	{
		cout << p.type << p.ID << '[';
		cout << p.RealCapcityOfRoom;
		cout << ", " << p.getCapacity() << ']';
	}
	else
		os << p.ID;

	return os;
}
