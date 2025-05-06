#pragma once
#include<iostream>
#include"fstream"
using namespace std;
class Resources
{
private:
	char type;
	int ID;
	int capacity;
	int RealCapcityOfRoom;
public:
	static int idE;
	static int idU;
	static int idR;
	char getType();
	int getID();
	void setType(char t);
	void setID(int id);
	void setCapacity(int cap);
	int getCapacity() const;
	void setRealCapacity(int cap);
	int getRealCapacity() const;
	char getType() const;
	Resources(char A);
	friend ostream& operator<<(ostream& os, const Resources& p);
	~Resources();
};
