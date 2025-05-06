#include"iostream"
#include"LinkedQueue.h"
#include"priQueue.h"
#include"ArrayStack.h"
using namespace std;
#include"Schedular.h"



int main()
{
	srand(time(0));
	LinkedQueue<Patient*>AllList;
	Schedular s; int x;
	// Your main code that calls the Scheduler function
	cout << "Choose Mode " << endl;
	cout << "Press 1 For Interactive Mode:" << endl;
	cout << "Press 2 For Silent Mode:" << endl;
	cin >> x;
	s.Simulation(AllList,x);
	if (x != 1)
	{
		cout << "Silent Mode, Simulation ends, Output file created" << endl;
	}
	return 0;
}

