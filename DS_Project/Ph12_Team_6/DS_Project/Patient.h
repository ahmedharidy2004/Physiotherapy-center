#include <iostream>
#include "Treatment.h"
using namespace std;
#ifndef PATIENT_H
#define PATIENT_H
enum  PatientStatus {
	IDLE,
	EARLY,
	WAITING,
	IN_TREATMENT,
	LATE,
	FINISHED
};
class Patient
{
public:
	static int Id;
	Patient();
	Patient(int one, int two);
	~Patient(); 
	void setType(char t) {
		type = t;
	}
	void SetArrivalTime(int time)
	{
		AV = time;
	}
	void SetAppointmentTime(int time)
	{
		PT = time;
	}
	// Getter for the current status
	PatientStatus getStatus() const {
		return status;
	}

	// Setter to update the status
	void setStatus(PatientStatus newStatus) {
		status = newStatus;
	}
	
	// Helper method to convert enum to string for display
	std::string getStatusString() const {
		switch (status) {
		case PatientStatus::IDLE: return "All";
		case PatientStatus::EARLY: return "Early";
		case PatientStatus::WAITING: return "Waiting";
		case PatientStatus::IN_TREATMENT: return "In Treatment";
		case PatientStatus::LATE: return "Late";
		case PatientStatus::FINISHED: return "Finished";
		default: return "Unknown";
		}
	}

	int GetArrivalTime() const
	{

		return AV;

	}
	int GetAppointmentTime() const
	{

		return PT;

	}
	int getCurrTreatmentDuration() {
		Treatment* ptr = nullptr;
		bool success = Required_Treatments.peek(ptr);
		if (success && ptr) {
			return ptr->GetDuration();
		}
		return 0; // or some default value, or throw an exception
	}
	void addTreatment(Treatment*& t) {
		Required_Treatments.enqueue(t);
	}
	Treatment* CurrentTreatment()
	{
		Treatment* Current;
		Required_Treatments.peek(Current);

		return Current;
	}

	int numberOfTreatments()
	{
		return Required_Treatments.GetCount();
	}
	friend ostream& operator<<(ostream& os, const Patient& p) {
		if (p.getStatus() == IDLE)
		{
			os << 'P' << p.personalId << '_'<<p.GetArrivalTime();
		}
		else if (p.getStatus() == IN_TREATMENT)
		{
			os << 'P' << p.personalId << '_';
			Treatment* dummy;
			p.Required_Treatments.peek(dummy);

				if (dummy->getType() == 'E')
					os << dummy->getType();
				else if (dummy->getType() == 'U')
					os << dummy->getType();
				else if (dummy->getType() == 'X')
					os << dummy->getType();
			
		}
		else
		{
			os << p.personalId;
		}
		// Add other fields as needed
		return os;
	}
private:
	char type;
	int AV, PT;
	int personalId;
	LinkedQueue<Treatment*> Required_Treatments;
	PatientStatus status;
};
int Patient::Id = 0;


Patient::Patient(int one, int two)
{
	SetArrivalTime(one);
	SetAppointmentTime(two);
	Id++;
	personalId = Id;
}
Patient::Patient()
{
	SetArrivalTime(0);
	SetAppointmentTime(0);
	Id++;
	personalId = Id;
}

Patient::~Patient()
{
}


#endif // PATIENT_H
