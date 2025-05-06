#include<iostream>
#include<fstream>
#include<random>
#include<time.h>       /* time */
#include"Patient.h"
#include"Treatment.h"
#include"UI.h"
#include"Schedular.h"
Schedular::Schedular() {
	nNum = 0; // number of n patients
	rNum = 0; //number of r patients
	totalPat = 0; // total number of patients
	totTimeSteps = 0; // total time steps
	ePatients = 0; // total number of early patients
	latePatients = 0; // total number of late patients
	totalPenalties = 0; // total number of penalties of late patients
	allTotWaiting = 0; //total waiting time for all patiens
	nTotWaiting = 0; // total waiting time for n patients
	rTotWaiting = 0; // total waiting time for e patients
	allTotTreatTime = 0; // total treatment time for all patients
	nTotTreatTime = 0; // total treatment time for n patients
	rTotTreatTime = 0; // total treatment time for r patients
	allCancel = 0; //Total Number Of Attempts of cancel
	Acceptedcancel = 0;//Total Number of Accepted cancel
	allResc = 0; //Total Number Of Attempts of Rescheduale
	AcceptedResc = 0;//Total Number of Accepted Rescheduale
	CurrentTimeStep = 1;
}
Schedular::	~Schedular() {}
void Schedular::loadPatients(LinkedQueue<Patient*>& patients)
{
	int e, u, x;
	int pNumber;
	ifstream readFile("tests/test_case_6.txt");
	if (!readFile.is_open())
	{
		cout << "Failed to open myfile.txt" << endl;
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

void Schedular::RandomGenerator(Patient*& Nextpatient, int max)
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

void Schedular::Simulation(LinkedQueue<Patient*>& L,int Mode)
{
	loadPatients(L);
	UI p;
	int position = 0;
	int ENDOFFunc = L.GetCount();
	for (CurrentTimeStep ; FinishList.GetCount() != ENDOFFunc; CurrentTimeStep++)
	{
		
		///////From Intreatment To Finished Or Waiting Lists
		Patient* P = nullptr; int dummy1 = 0;
		bool Success = Intreatment.peek(P, dummy1);
		while (Success && (-1 * dummy1) == CurrentTimeStep)
		{

			Intreatment.dequeue(P, dummy1);
			FromIntreat(P);
			Success = Intreatment.peek(P, dummy1);
			
		}

		/////From All List to Early / waiting / Late
		Patient* P1=nullptr;
		bool successed = L.peek(P1);
		while (successed && P1->GetArrivalTime() == CurrentTimeStep)
		{
			L.dequeue(P1);
			moveFromAll(P1);
			successed = L.peek(P1);
		}
		/////From Early to Waiting Or rescheduale
		Patient* P2=nullptr; int dummy3;
		bool successed2 = Early.peek(P2, dummy3);
		if (successed2) {
			bool Resc = Early.Reschedule(pResc);
			allResc++;
			if (Resc)
			{
				AcceptedResc++;
			}
		}
		successed2 = Early.peek(P2, dummy3);
		while (successed2&& (-1*dummy3) == CurrentTimeStep)
		{
			Early.dequeue(P2, dummy3);
			Treatment* NewTreat=nullptr; 
			P2->GetTReatList().peek(NewTreat);
			NewTreat->MoveTOWAoting(P2, this);
			successed2 = Early.peek(P2, dummy3);
		}
		/////From Late to Waiting
		Patient* P3=nullptr; int dummy2;
		bool successed3 = Late.peek(P3, dummy2);
		while (successed3 && (-1*dummy2) == CurrentTimeStep)
		{
			Late.dequeue(P3, dummy2);
			Treatment* NewTreat=nullptr;
			P3->GetTReatList().peek(NewTreat);
			NewTreat->MoveTOWAoting(P3, this);
			successed3 = Late.peek(P3, dummy2);
		}

		
		
		///From X Waiting to Intreatment
		Patient* P4=nullptr; Treatment* treat=nullptr;
		bool found=X_waiting.peek(P4);
		if (found) {
			Patient* TobeCanceled = nullptr;
			bool Cancel = X_waiting.Cancel(TobeCanceled, pCancel);
			allCancel++;
			if (Cancel)
			{
				TobeCanceled->setFinishTime(CurrentTimeStep);
				FinishList.push(TobeCanceled);
				Acceptedcancel++;
			}
		}
			found = X_waiting.peek(P4);
			

			while (found && !X_Rooms.isEmpty()) {
				
					P4->GetTReatList().peek(treat);
		        	Resources* ToAssign = nullptr;
					bool valid = X_Rooms.peek(ToAssign);
					if (treat->canAssign(ToAssign))
					{
						AssignX(CurrentTimeStep);
					}
				
				found = X_waiting.peek(P4);

			}
		
		
		///From U_Waiting to Intreatment
		Patient* P5=nullptr; Treatment* treat2=nullptr;
		bool foundone= U_waiting.peek(P5);
		while (foundone && !U_Devices.isEmpty()) {
			P5->GetTReatList().peek(treat2);
			Resources* ToAssign1= nullptr;
			U_Devices.peek(ToAssign1);
			if (treat2->canAssign(ToAssign1))
			{
				AssignU(CurrentTimeStep);
			}
			 foundone = U_waiting.peek(P5);

		}
		/////From E_Waitint to Intreatment
		Patient* P6=nullptr; Treatment* treat3 =nullptr;
		bool find=E_waiting.peek(P6);

		while (find &&!E_Devices.isEmpty()) {
			P6->GetTReatList().peek(treat3);
			Resources* ToAssign2 = nullptr;
			E_Devices.peek(ToAssign2);
			if (treat3->canAssign(ToAssign2))
			{
				AssignE(CurrentTimeStep);
			}
			 find = E_waiting.peek(P6);

		}
		
		if (Mode != 1)
		{
			continue;
		}
		p.print(CurrentTimeStep, L, E_waiting, U_waiting, X_waiting, Early, Late, E_Devices, U_Devices, X_Rooms, Intreatment, FinishList);
		cout << endl << endl;
	}
	outputPatients();
}

int Schedular::getPresc()
{
	return pResc;
}

int Schedular::getPCancel()
{
	return pCancel;
}

void Schedular::FromIntreat(Patient*& p)
{
	Treatment* top_intreat=nullptr;
	p->GetTReatList().dequeue(top_intreat);
	if (top_intreat->GetResource()->getType() == 'E')
	{
		E_Devices.enqueue(top_intreat->GetResource());
	}
	else if (top_intreat->GetResource()->getType() == 'U')
	{
		U_Devices.enqueue(top_intreat->GetResource());
	}
	else
	{
		if (top_intreat->GetResource()->getCapacity() == top_intreat->GetResource()->getRealCapacity())
		{
			top_intreat->GetResource()->setRealCapacity(top_intreat->GetResource()->getRealCapacity() - 1);
			X_Rooms.enqueue(top_intreat->GetResource());
		}
		else
		{
			top_intreat->GetResource()->setRealCapacity(top_intreat->GetResource()->getRealCapacity() - 1);
		}
	}
	if (p->GetTReatList().GetCount()==0)
	{
		p->setFinishTime(CurrentTimeStep);
		p->setStatus(FINISHED);
		FinishList.push(p);
	}
	else
	{
		p->setStatus(WAITING);
		if (p->getType() == 'N')
		{
			if (p->CurrentTreatment()->getType() == 'X')
			{
				//p->setTreatmentTime(p->getTreatmentTime()+ (p->CurrentTreatment()->GetDuration()));
				X_waiting.InsertSorted(p);
			}
			else if (p->CurrentTreatment()->getType() == 'E')
			{
				E_waiting.InsertSorted(p);

			}
			else if (p->CurrentTreatment()->getType() == 'U')
			{
				U_waiting.InsertSorted(p);
			}
		}
		else
		{
			RPMovetoWait(p);
		}
	}

}

void Schedular::moveFromAll(Patient*& p)
{


	if (p->GetArrivalTime() < p->GetAppointmentTime())  //condition of adding to early list
	{
		Early.enqueue(p,-1*( p->GetAppointmentTime()));
		p->setStatus(EARLY);
	}
	else if (p->GetArrivalTime() > p->GetAppointmentTime())  //condition off adding to late list
	{
		int penalty =ceil((p->GetArrivalTime() - p->GetAppointmentTime())/2.0);   //calculate penalty will be added to patient AV

		Late.enqueue(p,-1*( p->GetArrivalTime() + penalty));
		totalPenalties += penalty;
		p->setStatus(LATE);

	}
	else if (p->getType() == 'R')   //check for recovering patient or not as it can join rooms without any order
	{

		this->RPMovetoWait(p);

	}
	else {
		Treatment* CurrentTreatment = p->CurrentTreatment();
		if (CurrentTreatment != NULL)
		{
			if (CurrentTreatment->getType() == 'X')
			{
				X_waiting.enqueue(p);
				p->setStatus(WAITING);
			}
			else
				if (CurrentTreatment->getType() == 'E')
				{
					E_waiting.enqueue(p);
					p->setStatus(WAITING);

				}
				else
					if (CurrentTreatment->getType() == 'U')
					{
						U_waiting.enqueue(p);
						p->setStatus(WAITING);

					}
		}
	}


}

void Schedular::moveFromEarlyOrLate(Patient*& p)
{


	if (p->getType() == 'R')   //check for recovering patient or not as it can join rooms without any order
	{

		this->RPMovetoWait(p);

	}
	else {
		
		Treatment* CurrentTreatment = p->CurrentTreatment();
		if (CurrentTreatment != NULL)
		{
			if (CurrentTreatment->getType() == 'X')
			{
				if (p->getStatus() == EARLY)
				{
					X_waiting.Enqueue(p);
				}
				else
				{
					X_waiting.InsertSorted(p);
				}
				p->setStatus(WAITING);
			}
			else
				if (CurrentTreatment->getType() == 'E')
				{
					if (p->getStatus() == EARLY)
					{
						E_waiting.enqueue(p);
					}
					else
					{
						E_waiting.InsertSorted(p);
					}
					p->setStatus(WAITING);
				}
				else
					if (CurrentTreatment->getType() == 'U')
					{
						if (p->getStatus() == EARLY)
						{
							U_waiting.enqueue(p);
						}
						else
						{
							U_waiting.InsertSorted(p);
						}
						p->setStatus(WAITING);
					}
		}
	}
}



void Schedular::RPMovetoWait(Patient*& P)
{
	int XTime = INT_MAX, ETime = INT_MAX, UTime = INT_MAX;
	LinkedQueue<Treatment*> Treats ;
	Treatment* temp7 = NULL;
	while (P->GetTReatList().dequeue(temp7))
	{
		
		Treats.enqueue(temp7);


	}
	LinkedQueue<Treatment*> Temp;
	if (Treats.isEmpty())
	{
		return;
	}
	Treatment* temp=nullptr;
	while (Treats.dequeue(temp))
	{
		if (temp->getType() == 'E')
		{
			ETime = E_waiting.calcTreatmentLatency();
		}
		else if (temp->getType() == 'U')
		{
			UTime = U_waiting.calcTreatmentLatency();
		}
		else
		{
			XTime = X_waiting.calcTreatmentLatency();
		}
		Temp.enqueue(temp);
	}
	int mintime = min(ETime, XTime);
	mintime = min(mintime, UTime);
	LinkedQueue<Treatment*> Temp2;
	while (!Temp.isEmpty())
	{
		Treatment* temp2=nullptr;
		Temp.dequeue(temp2);
		if (mintime == E_waiting.calcTreatmentLatency() && temp2->getType() == 'E')
		{
			Treats.enqueue(temp2);
		}
		else if (mintime == U_waiting.calcTreatmentLatency() && temp2->getType() == 'U')
		{
			Treats.enqueue(temp2);
		}
		else if (mintime == X_waiting.calcTreatmentLatency() && temp2->getType() == 'X')
		{
			Treats.enqueue(temp2);
		}
		else
		{
			Temp2.enqueue(temp2);
		}

	}
	Treatment* temp3=nullptr;
	while (Temp2.dequeue(temp3))
	{
		Treats.enqueue(temp3);
	}
	while (Treats.dequeue(temp3))
	{
		P->GetTReatList().enqueue(temp3);


	}
	Treatment* tr;
	P->GetTReatList().peek(tr);
	if (P->getStatus() == IN_TREATMENT || P->getStatus() == LATE)
	{
		if (mintime == E_waiting.calcTreatmentLatency() && tr->getType() == 'E')
		{
			P->setStatus(WAITING);
			E_waiting.InsertSorted(P);
		}
		if (mintime == U_waiting.calcTreatmentLatency() && tr->getType() == 'U')
		{
			P->setStatus(WAITING);
			U_waiting.InsertSorted(P);
		}
		if (mintime == X_waiting.calcTreatmentLatency() && tr->getType() == 'X')
		{
			P->setStatus(WAITING);
			X_waiting.InsertSorted(P);
		}
	}
	else {
		if (mintime == E_waiting.calcTreatmentLatency() && tr->getType() == 'E')
		{
			P->setStatus(WAITING);
			E_waiting.enqueue(P);
		}
		if (mintime == U_waiting.calcTreatmentLatency() && tr->getType() == 'U')
		{
			P->setStatus(WAITING);
			U_waiting.enqueue(P);
		}
		if (mintime == X_waiting.calcTreatmentLatency() && tr->getType() == 'X')
		{
			P->setStatus(WAITING);
			X_waiting.Enqueue(P);
		}
	}
	
}

void Schedular::outputPatients()
{
	totalPat = FinishList.GetCount();
	ofstream Outfile("sample.txt"); // creating sample file 
	if (Outfile.is_open()) {
		Outfile << left
			<< setw(5) << "PID"
			<< setw(8) << "PType"
			<< setw(6) << "PT"
			<< setw(6) << "VT"
			<< setw(6) << "FT"
			<< setw(6) << "WT"
			<< setw(6) << "TT"
			<< setw(8) << "Cancel"
			<< setw(6) << "Resc"
			<< endl;
		while (!FinishList.isEmpty()) {
			Patient* p;
			FinishList.pop(p);
			allTotWaiting += (p->getFinishTime() - p->GetArrivalTime() - p->getTreatmentTime());
			//========================================== some logic and calculations =======================================================================
			if (p->getType() == 'N') {
				nNum++;
				nTotWaiting += (p->getFinishTime() - p->GetArrivalTime() - p->getTreatmentTime());
				nTotTreatTime += p->getTreatmentTime();
			} // checks if patient N type
			else {
				rNum++;
				rTotWaiting += (p->getFinishTime() - p->GetArrivalTime() - p->getTreatmentTime());
				rTotTreatTime += p->getTreatmentTime();
			} // else it is patient R type
			if (p->GetArrivalTime() > p->GetAppointmentTime()) {
				latePatients++;
				totalPenalties += (p->GetArrivalTime() - p->GetAppointmentTime()) / 2;
			}
			else if(p->GetArrivalTime() < p->GetAppointmentTime()) {
				ePatients++;
			}
			allTotTreatTime += p->getTreatmentTime();
			if (p->getCancel()) allCancel++;
			if (p->getResc()) allResc++;
			//=========================================== printing patients details ========================================================================
			Outfile << left
				<< "p" << setw(4) << p->getPersonalId()
				<< setw(8) << p->getType()
				<< setw(6) << p->GetAppointmentTime()
				<< setw(6) << p->GetArrivalTime()
				<< setw(6) << p->getFinishTime()
				<< setw(6) << p->getFinishTime() - p->GetArrivalTime() - p->getTreatmentTime()
				<< setw(6) << p->getTreatmentTime()
				<< setw(8) << (p->getCancel() ? 'T' : 'F')
				<< setw(6) << (p->getResc() ? 'T' : 'F')
				<< endl;
		}
		//------------------------------------------------------------------------
		// Waiting Time  finish - treatment -arrival
		
		//============================================================ statistics ==========================================================================
		double avgAllW, avgNW, avgRW, avgAllT, avgNT, avgRT, percAllCancel, percAllResc;
		avgAllW = double(allTotWaiting) / double(totalPat); // avg waiting time for all patients
		avgNW = double(nTotWaiting) / double(nNum); // avg waiting time for n patients
		avgRW = double(rTotWaiting) / double(rNum); // avg waiting time for r patients
		avgAllT = double(allTotTreatTime) / double(totalPat); // avg treatment time for all patients
		avgNT = double(nTotTreatTime) / double(nNum); // avg treatment time for n patients
		avgRT = double(rTotTreatTime) / double(rNum); // avg treatment time for r patients
		percAllCancel = double(Acceptedcancel) / double(allCancel) * 100;
		percAllResc = double(AcceptedResc) / double(allResc) * 100;
		Outfile << "Total number of timesteps = " << CurrentTimeStep-1 << endl;
		Outfile << "Total number of all, N, and R patients = " << totalPat << ", " << nNum << ", " << rNum << endl;
		Outfile << "Average total waiting time for all, N, and R patients = " << avgAllW << ", " << avgNW << ", " << avgRW << endl;
		Outfile << "Average total treatment time for all, N, and R patients = " << avgAllT << ", " << avgNT << ", " << avgRT << endl;
		Outfile << "Percentage of Patients of accepted Cancellations (%) = " << percAllCancel << "%" << endl;
		Outfile << "Percentage of Patients of accepted Rescheduales (%) = " << percAllResc << "%" << endl;
		Outfile << "Percentage of early patients (%) = " << double(ePatients) / double(totalPat) * 100 << "%" << endl;
		Outfile << "Percentage of late patients (%) = " << double(latePatients) / double(totalPat) * 100 << "%" << endl;
		Outfile << "Average late penalty = " << totalPenalties / latePatients << " timestep(s)" << endl;
		Outfile.close();
	}
	else cout << "error creating the file" << endl;
}

Resources* Schedular::getE() const
{
	Resources* Eptr;
	E_Devices.peek(Eptr);
	return Eptr;
}

Resources* Schedular::getU() const
{
	Resources* Uptr;
	E_Devices.peek(Uptr);
	return Uptr;
}

void Schedular::AssignE(int assignTime)
{
	if (Treatment::canAssign(getE())) {
		Resources* r=nullptr;
		E_Devices.dequeue(r); // getting available resource
		Patient* p=nullptr;
		E_waiting.dequeue(p); // getting waiting patient
		Treatment* patientReqTreatment=nullptr; // getting the required treatment
		patientReqTreatment = p->CurrentTreatment();
		p->setStatus(IN_TREATMENT);
		p->setTreatmentTime(p->getTreatmentTime() + p->getCurrTreatmentDuration());
		p->setFinishTime(assignTime + p->getCurrTreatmentDuration());
		patientReqTreatment->setResource(r); // setting the resource
		patientReqTreatment->setAssignmentTime(assignTime); // assign time for patient
		Intreatment.enqueue(p,-1*( patientReqTreatment->GetDuration() + assignTime)); // not sure if finishing the treatment means assign time + the duration of treatment
	}
}

void Schedular::AssignU(int assignTime)
{
	if (Treatment::canAssign(getU())) {
		Resources* r=nullptr;
		U_Devices.dequeue(r); // getting available resource
		Patient* p=nullptr;
		U_waiting.dequeue(p); // getting waiting patient
		Treatment* patientReqTreatment=nullptr; // getting the required treatment
		p->setStatus(IN_TREATMENT);
		p->setTreatmentTime(p->getTreatmentTime() + p->getCurrTreatmentDuration());
		p->setFinishTime(assignTime + p->getCurrTreatmentDuration());
		patientReqTreatment = p->CurrentTreatment();
		patientReqTreatment->setResource(r); // setting the resource
		patientReqTreatment->setAssignmentTime(assignTime); // assign time for patient
		Intreatment.enqueue(p,-1*( patientReqTreatment->GetDuration() + assignTime)); 
	}
}
void Schedular::AssignX(int assigntime)
{
	Resources* R=nullptr;
	Patient* p=nullptr;
	X_Rooms.peek(R);
	X_waiting.dequeue(p);
	if (p && R) {
		Intreatment.enqueue(p,-1*(p->getCurrTreatmentDuration() + assigntime));
		p->CurrentTreatment()->setResource(R);
		p->setTreatmentTime(p->getTreatmentTime()+p->getCurrTreatmentDuration());	
		p->setStatus(IN_TREATMENT);
		p->setFinishTime(assigntime + p->getCurrTreatmentDuration());
		R->setRealCapacity(R->getRealCapacity() + 1);
		if (R->getRealCapacity() == R->getCapacity())
			X_Rooms.dequeue(R);
	}
}