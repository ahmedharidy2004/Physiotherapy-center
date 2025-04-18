#ifndef SCHEDULAR_H
#define SCHEDULAR_H
#include <fstream>
#include <string>
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
public:
	Schedular() {}
	void loadPatients(LinkedQueue<Patient*>& patients) {
		int e, u, x;
		int pNumber;
		ifstream readFile("myfile.txt");
		if (!readFile.is_open())
		{cout << "Failed to open myfile.txt" << endl;
		return;
		}
		readFile >> e >> u >> x; // reading the number of e devices, u devices and x rooms
		for (int i = 0; i < e; i++) {
			Resources* E_d = new Resources('E'); //creating e devices
			E_Devices.enqueue(E_d);
		}
		for (int i = 0; i < u; i++) {
			Resources* U_d = new Resources('U'); //creating u devices
			U_Devices.enqueue(U_d);
		}
		for (int i = 0; i < x; i++) {
			Resources* X_R = new Resources('R'); // creating x rooms
			int cap;
			readFile >> cap; //reading the capacity of each room
			X_R->setCapacity(cap);
			X_Rooms.enqueue(X_R);
		}
		readFile >> pCancel >> pResc; // reading pCancel and pResc
		readFile >> pNumber; // reading patients number
		for (int i = 0; i < pNumber; i++) {
			Patient* pat = new Patient;
			char T;
			int p, a, nr;
			readFile >> T >> p >> a >> nr;
			for (int j = 0; j < nr; j++) {
				char t;
				int n;
				readFile >> t >> n;
				//cout << t << n << endl;
				if (t == 'E') {
					E_treatment* etreatment = new E_treatment;
					etreatment->SetDuration(n);
					etreatment->setType(t);
					Treatment* t_cast = etreatment;
					pat->addTreatment(t_cast);
				}
				else if (t == 'U') {
					U_Treatment* utreatment = new U_Treatment;
					utreatment->SetDuration(n);
					utreatment->setType(t);
					Treatment* t_cast = (utreatment);
					pat->addTreatment(t_cast);
				}
				else if (t == 'X') {
					X_treatment* xtreatment = new X_treatment;
					xtreatment->SetDuration(n);
					xtreatment->setType(t);
					Treatment* t_cast = (xtreatment);
					pat->addTreatment(t_cast);
				}
			}
			pat->SetAppointmentTime(p);
			pat->SetArrivalTime(a);
			pat->setType(T);
			patients.enqueue(pat);
		}
		readFile.close();
	}
	~Schedular() {}
	void RandomGenerator(Patient*& Nextpatient, int max = 101)
	{
		int N = rand() % 101;
		if (N < 33) { 
			Nextpatient->setStatus(WAITING);
			E_waiting.enqueue(Nextpatient); //////////////
		}
		else if (N < 66) {
			Nextpatient->setStatus(WAITING);
			U_waiting.enqueue(Nextpatient);/////////////////
		}
		else
		{
			Nextpatient->setStatus(WAITING);
			X_waiting.Enqueue(Nextpatient);
		}
	}
	void Simulation(LinkedQueue<Patient*>&L)
	{
		loadPatients(L);
		UI p;
		int currentTimestep = 0;
		int position = 0;
		int ENDOFFunc = L.GetCount();
			for (int CurrentTimeStep = 0; FinishList.GetCount()!=ENDOFFunc; CurrentTimeStep++)
		{
			Patient* P;
			bool Success = L.peek(P);
			while (Success && P->GetArrivalTime() == CurrentTimeStep)
			{
				L.dequeue(P);

				if (P->GetArrivalTime() < P->GetAppointmentTime())
				{
					P->setStatus(EARLY);
					Early.enqueue(P, P->GetAppointmentTime());
				}
				else if (P->GetArrivalTime() > P->GetAppointmentTime())
				{
					P->setStatus(LATE);
					Late.enqueue(P, P->GetAppointmentTime());
				}
				else
				{
					RandomGenerator(P);
				}

				// Check for next patient
				Success = L.peek(P);
			}
			int X =rand() % 101;
					int dummy;
				Patient* Pa;
				Patient* Pb;
				if (X < 10)
				{
					bool success = Early.peek(Pa, dummy);
					if (success)
					{
						Early.dequeue(Pa, dummy);
						RandomGenerator(Pa);
					}
				}
				else if (X < 20)
				{
					int dummy;
					bool S1 = Late.peek(Pa, dummy);
					if (S1)
					{
						Late.dequeue(Pa, dummy);
						int N = rand() % 101;
						Pa->setStatus(WAITING);
						if (N < 33)
						{
							E_waiting.InsertSorted(Pa);
						}
						else if (N < 66)
						{
							U_waiting.InsertSorted(Pa);
						}
						else
						{
							X_waiting.InsertSorted(Pa);
						}
					}
				}
				else if (X < 40)
				{
					int i = 0;
					while (i < 2 && ((E_waiting.GetCount() + U_waiting.GetCount() + X_waiting.GetCount()) > 0))
					{
						int N = rand() % 101;
						if (N < 33)
						{
							bool success = E_waiting.peek(Pa);
							if (success) {
								E_waiting.dequeue(Pa);
								Pa->setStatus(IN_TREATMENT);
								Intreatment.enqueue(Pa, CurrentTimeStep);
								i++;
							}
						}
						else if (N < 66)
						{
							bool success = U_waiting.peek(Pa);
							if (success) {
								U_waiting.dequeue(Pa);
								Pa->setStatus(IN_TREATMENT);
								Intreatment.enqueue(Pa, CurrentTimeStep);
								i++;
							}
						}
						else
						{
							bool success = X_waiting.peek(Pa);
							if (success) {
								X_waiting.dequeue(Pa);
								Pa->setStatus(IN_TREATMENT);
								Intreatment.enqueue(Pa, CurrentTimeStep);
								i++;
							}
						}
					}

				}
				else if (X < 50)
				{
					int dummy;
					bool Notempty = Intreatment.peek(Pa, dummy);
					if (Notempty)
					{
						Intreatment.dequeue(Pa, dummy);
						RandomGenerator(Pa);
					}
				}
				else if (X < 60)
				{
					int dummy;
					bool Notempty = Intreatment.peek(Pa, dummy);
					if (Notempty)
					{
						Intreatment.dequeue(Pa, dummy);
						Pa->setStatus(FINISHED);
						FinishList.push(Pa);
					}
				}
				else if (X < 70)
				{
					int n = 30;
					Patient* P = nullptr;
					bool canceled = 0;
					while (n--)
					{
						if (X_waiting.Cancel(P, pCancel))
						{
							canceled = true;
							break;
						}
					}
					if (canceled)
					{
						P->setStatus(FINISHED);
						FinishList.push(P);
					}
				}
				else if (X < 80)
				{
					int n = 30;
					while (n--)
					{
						if (Early.Reschedule(pResc))
						{
							break;
						}
					}
				}
				p.print(CurrentTimeStep, L, E_waiting, U_waiting, X_waiting, Early, Late, E_Devices, U_Devices, X_Rooms, Intreatment, FinishList);
				system("pause");
				cout << endl << endl;
		}
	}
	int getPresc() {
		return pResc;
	}
	int getPCancel() {
		return pCancel;
	}
};
#endif // !SCHEDULAR_H
