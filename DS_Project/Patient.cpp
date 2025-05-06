#include"Patient.h"
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
	WT = FT = TT = 0; // waiting time, finish time, treatment time
	cancel = resc = false;
	RescTimes = 0;
}

Patient::~Patient()
{
}

void Patient::setType(char t)
{
	type = t;
}

void Patient::SetArrivalTime(int time)
{
	AV = time;
}

void Patient::SetAppointmentTime(int time)
{
	PT = time;
}

PatientStatus Patient::getStatus() const
{
	return status;
}

void Patient::setStatus(PatientStatus newStatus)
{
	status = newStatus;
}

string Patient::getStatusString() const
{
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

int Patient::GetArrivalTime() const
{
	return AV;
}

int Patient::GetAppointmentTime() const
{
	return PT;
}

int Patient::getCurrTreatmentDuration()
{
	Treatment* ptr = nullptr;
	bool success = Required_Treatments.peek(ptr);
	if (success && ptr) {
		return ptr->GetDuration();
	}
	return 0; // or some default value, or throw an exception}
}

int Patient::getPersonalId() const
{
	return personalId;
}

void Patient::addTreatment(Treatment*& t)
{
	Required_Treatments.enqueue(t);
}

Treatment* Patient::CurrentTreatment()
{
	Treatment* Current;
	Required_Treatments.peek(Current);

	return Current;
}

int Patient::numberOfTreatments()
{
	return Required_Treatments.GetCount();
}

int Patient::getWaitingtime() const
{
	return WT;
}

int Patient::getTreatmentTime() const
{
	return TT;
}

int Patient::getFinishTime() const
{
	return FT;
}

void Patient::setWaitingTime(int time)
{
	WT = time;
}

void Patient::setTreatmentTime(int time)
{
	TT = time;
}

void Patient::setFinishTime(int time)
{
	FT = time;
}

bool Patient::getResc() const
{
	return resc;
}

bool Patient::getCancel() const
{
	return cancel;
}

void Patient::setResc(bool f)
{
	resc = f;
}

void Patient::setCancel(bool f)
{
	cancel = f;
}

void Patient::setNumofResc(int n)
{
	RescTimes = n;
}

int Patient::GetNumofResc()
{
	return RescTimes;
}

char Patient::getType() const
{
	return type;
}

LinkedQueue<Treatment*>& Patient::GetTReatList()
{
	return Required_Treatments;
}
































