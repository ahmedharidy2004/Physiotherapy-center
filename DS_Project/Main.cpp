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
	Schedular s;
	// Your main code that calls the Scheduler function
	s.Simulation(AllList);
	return 0;
}

