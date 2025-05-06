#pragma once
#include"LinkedQueue.h"
#include"Patient.h"
#include"EU_waitingList.h"
#include"X_WaitingList.h"
#include"EarlypriList.h"
#include"ArrayStack.h"
#include"Resources.h"
class UI
{
public:
	UI() { }
	void print(int current,LinkedQueue<Patient*> &All, EU_WaitingList& E, EU_WaitingList& U, X_WaitingList& X, EarlyPList& Early, priQueue<Patient*>& Late,
		LinkedQueue<Resources*>& EDevice, LinkedQueue<Resources*>& UDevice, LinkedQueue<Resources*>& XRooms,priQueue<Patient*>& Intreat, ArrayStack<Patient*>& Finish)
	{
		cout << "Current TimeStep       " << current << endl;
		cout << "=====================  All List   ======================"<<endl;
		cout << All.GetCount() << " patients remaining: ";
		All.PrintQueue(10);
		cout << "=====================  Waiting Lists   ======================" << endl;
		cout << E.GetCount() << " E-threapy patients: ";
		E.PrintQueue();
		cout << endl;
		cout << U.GetCount() << " U-threapy patients: ";
		U.PrintQueue();
		cout << endl;
		cout << X.GetCount()<<" X-threapy patients:" ;
		X.PrintQueue();
		cout << endl;
		cout << "=====================  Early List  ======================" << endl;
		cout << Early.getCount() << " patients: ";
		Early.printList();
		cout << "=====================  Late List  ======================" << endl;
		cout << Late.getCount() << " Patients: ";
		Late.printList();
		cout << "=====================  E Avaiable List  ======================" << endl;
		cout << EDevice.GetCount() << " Electro device: ";
		EDevice.PrintQueue();
		cout << endl;
		cout << "=====================  U Avaiable List  ======================" << endl;
		cout << UDevice.GetCount() << " Ultra device: ";
		UDevice.PrintQueue();
		cout << endl;
		cout << "=====================  X Avaiable List  ======================" << endl;
		cout << XRooms.GetCount() << " rooms: ";
		XRooms.PrintQueue();
		cout << endl;
		cout << "=====================  Intreatment List  ======================" << endl;
		cout << Intreat.getCount() << " ==> ";
		Intreat.printList();
		cout << "--------------------------------------------------------" << endl;
		cout << Finish.GetCount() << " finished patients: ";
		Finish.PrintStack();
		cout << "-----------------------------------------------------------------------" << endl;
	}
	


};