#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>
#include "Treatment.h"
#include"Resources.h"
#include"fstream"
#include"LinkedQueue.h"
#include<string>
using namespace std;
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
	void setType(char t);
	void SetArrivalTime(int time);
	void SetAppointmentTime(int time);
	// Getter for the current status
	PatientStatus getStatus() const;
	// Setter to update the status
	void setStatus(PatientStatus newStatus);
		// Helper method to convert enum to string for display
	string getStatusString() const;
	int GetArrivalTime() const;
	int GetAppointmentTime() const;
	int getCurrTreatmentDuration();
	int getPersonalId() const;
	void addTreatment(Treatment*& t);
	Treatment* CurrentTreatment();
	int numberOfTreatments();
		//========================== added functions for waitng , finish, treament time ==========================================
	int getWaitingtime() const;
	int getTreatmentTime() const;
	int getFinishTime() const;
	void setWaitingTime(int time);
	void setTreatmentTime(int time);
	void setFinishTime(int time);
	bool getResc() const;
	bool getCancel() const;
	void setResc(bool f);
	void setCancel(bool f);
	void setNumofResc(int n);
	int GetNumofResc();
	LinkedQueue<Treatment*>& GetTReatList();
	//--------------------------------------------------------------------------------------------------------------------------
	friend ostream& operator<<(ostream& os, const Patient& p) {
		if (p.getStatus() == IDLE)
		{
			os << 'P' << p.personalId << '_'<<p.GetArrivalTime();
		}
		else if (p.getStatus() == IN_TREATMENT)
		{
			os << 'P' << p.personalId << '_';
			Treatment* dummy = NULL;
			p.Required_Treatments.peek(dummy);

				
					if(dummy->getType() == 'E')
					os << dummy->getType()<< dummy->GetResource()->getID();
				else if (dummy->getType() == 'U')
					os << dummy->getType() << dummy->GetResource()->getID();
				else if (dummy->getType() == 'X')
					os << dummy->getType() <<dummy->GetResource()->getID();
			
		}
		else
		{
			os << p.personalId;
		}
		// Add other fields as needed
		return os;
	}
	char getType() const;
	LinkedQueue<Treatment*> Required_Treatments;

private:
	char type;
	int AV, PT; int RescTimes;
	int personalId;
	int FT, WT, TT; // finish time, waiting time, treatment time
	bool cancel, resc;
	PatientStatus status;
};


#endif // PATIENT_