#ifndef SCHEDULAR_H
#define SCHEDULAR_H
#include <fstream>
#include <string>
#include <iomanip>
#include"LinkedQueue.h"
#include"Patient.h"
#include"EarlypriList.h"
#include"X_WaitingList.h"
#include"priQueue.h"
#include "ArrayStack.h"
#include"EU_waitingList.h"
#include "Treatment.h"
#include "X_treatment.h"
#include "E_treatment.h"
#include "U_Treatment.h"
#include "Resources.h"
#include"UI.h"


class Schedular
{
	ArrayStack<Patient*> FinishList;
	priQueue<Patient*>Intreatment;
	EarlyPList Early;
	priQueue<Patient*>Late;
	LinkedQueue<Patient*>AllList;
	EU_WaitingList E_waiting;
	EU_WaitingList U_waiting;
	X_WaitingList X_waiting;
	LinkedQueue<Resources*> E_Devices;
	LinkedQueue<Resources*> U_Devices;
	LinkedQueue<Resources*> X_Rooms;
	int pResc, pCancel;
	int nNum, rNum, totalPat, totTimeSteps, ePatients, latePatients, totalPenalties, allTotWaiting, nTotWaiting, rTotWaiting, allTotTreatTime, nTotTreatTime, rTotTreatTime;
	int allResc, allCancel; int AcceptedResc; int Acceptedcancel;
public:
	Schedular();
	~Schedular();
	void loadPatients(LinkedQueue<Patient*>& patients);
	void RandomGenerator(Patient*& Nextpatient, int max = 101);
	void Simulation(LinkedQueue<Patient*>& L,int Mode);
	int getPresc();
	int getPCancel();
	void FromIntreat(Patient*& p);
	void moveFromAll(Patient*& p);
	void moveFromEarlyOrLate(Patient*& p);
	void RPMovetoWait(Patient*& P);
	void outputPatients();
	int CurrentTimeStep;
	Resources* getE() const;

	Resources* getU() const;

	void AssignE(int assignTime);

	void AssignU(int assignTime);
	void AssignX(int assignTime);
};
#endif // !SCHEDULAR_H
