#pragma once
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
	char getType() {
		return type;
	}
	int getID() {
		return ID;
	}
	void setType(char t) {
		type = t;
	}
	void setID(int id) {
		ID = id;
	}
	void setCapacity(int cap) {
		capacity = cap;
	}
	int getCapacity() const {
		return capacity;
	}
	char getType() const
	{
		return type;
	}
	Resources(char A=' ') {
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
		RealCapcityOfRoom=0;
	}
	friend ostream& operator<<(ostream& os, const Resources& p) {
		if (p.getType() == 'R')
		{
			cout << p.type << p.ID << '[';
			cout << p.getCapacity() - p.RealCapcityOfRoom;
			cout<< ", " << p.getCapacity() << ']';
		}
		else
		os << p.ID;
	
		return os;
	}
	~Resources() {

	}
};
int Resources::idE = 0;
int Resources::idU = 0;
int Resources::idR = 0;