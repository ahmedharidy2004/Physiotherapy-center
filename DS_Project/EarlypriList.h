#pragma once
#include "priQueue.h"
#include "Patient.h"

class EarlyPList : public  priQueue<Patient*>
{

public:
	bool Reschedule(int presc)
	{
		int randommm = rand() % 101;

		if (randommm < presc)
		{


			/*int tempPri = 0, Rpri = 0;
			if (head == NULL)
				return false;
			if (head->getNext() == NULL)
			{
				int dummy = 0;
				Patient* p = head->getItem(dummy);
				p->SetAppointmentTime(rand() % 50 + head->getItem(dummy)->GetAppointmentTime());
				return true;
			}
			else
			{
				priNode<Patient*>* ptr = head->getNext();
				priNode<Patient*>* prev = head;
				int RandomPatient = rand() % getCount() + 1;

				int i = 2;
				while (ptr != NULL)
				{

					if (i == RandomPatient)
					{
						int dummy = 0;
						prev->setNext(ptr->getNext());
						int x = 0;
						ptr->getItem(dummy)->SetAppointmentTime(rand() % 50 + ptr->getItem(x)->GetAppointmentTime());


						break;

					}
					else
					{
						prev = prev->getNext();
						ptr = ptr->getNext();
						i++;
					}
				}
				if (ptr != nullptr) {
					int dummy = 0;
					enqueue(ptr->getItem(dummy), ptr->getItem(dummy)->GetAppointmentTime());
					count--;
				}
				return true;
			}*/
			if (getCount() > 0)
			{
				int RandomPatient = rand() % getCount() + 1;
				Patient* Rpatient = NULL;
				Patient* Ptemp = NULL;
				for (int i = 1; i <= getCount(); i++)
				{
					if (i == RandomPatient)
					{
						int Rpri = 0;
						peek(Rpatient, Rpri);
						if (Rpatient->GetNumofResc() > 3)
						{
							return false;
						}
						dequeue(Rpatient, Rpri);
						Rpatient->SetAppointmentTime(rand() % 10 + Rpatient->GetAppointmentTime());
						Rpatient->setNumofResc(Rpatient->GetNumofResc() + 1);
						this->enqueue(Rpatient, -1 * Rpatient->GetAppointmentTime());
						Rpatient->setResc(true);
						return true;
					}
					else if (i < getCount())
					{
						int tempPri = 0;
						dequeue(Ptemp, tempPri);
						this->enqueue(Ptemp, tempPri);

					}
				}
			}
			else return false;
		}
		else
		{
			return false;
		}
	}

	//bool Reschedule(int presc,int TimeStep)

	//{
	//	int randommm = rand() % 101;
	//	Patient* temp = nullptr;
	//	if (randommm < presc)
	//	{

	//		Patient* Rpatient = NULL;
	//		Patient* Ptemp = NULL;
	//		int tempPri = 0, Rpri = 0;
	//		if (head == NULL)
	//			return false;
	//		if (head->getNext() == NULL)
	//		{
	//			int dummy = 0;
	//			temp = head->getItem(dummy);
	//			if (temp->GetNumofResc ()>=0)
	//			{
	//				return false;
	//			}
	//			head->getItem(dummy)->SetAppointmentTime(rand() % 50 + TimeStep);
	//			head->getItem(dummy)->setResc(true);
	//			head->getItem(dummy)->setNumofResc(head->getItem(dummy)->GetNumofResc() + 1);
	//			return true;
	//		}
	//		else
	//		{
	//			priNode<Patient*>* ptr = head->getNext();
	//			priNode<Patient*>* prev = head;
	//			int RandomPatient = rand() % getCount() + 1;

	//			int i = 2;
	//			while (ptr != NULL)
	//			{

	//				if (i == RandomPatient)
	//				{
	//					int dummy = 0;
	//					temp = ptr->getItem(dummy);
	//					prev->setNext(ptr->getNext());
	//					int x = 0;
	//					if (temp->GetNumofResc()>=0)
	//					{
	//						return false;
	//					}
	//					temp->SetAppointmentTime(rand() % 50 + TimeStep);
	//					int dummyone;
	//					temp->setNumofResc(ptr->getItem(dummy)->GetNumofResc() + 1);
	//					temp->setResc(true);
	//					break;

	//				}
	//				else
	//				{
	//					prev = prev->getNext();
	//					ptr = ptr->getNext();
	//					i++;
	//				}
	//			} 
	//			if (temp != nullptr) {
	//				int dummy = 0;
	//				enqueue(temp, -1*(temp->GetAppointmentTime()));
	//				count--;
	//			}
	//			return true;
	//		}
	//		/*for (int i = 1; i <= getCount(); i++)
	//		{
	//			if (i == RandomPatient )
	//			{
	//				peek(*Rpatient, Rpri);
	//				dequeue(*Rpatient, Rpri);
	//				Rpatient->SetAppointmentTime(rand() % 50 + Rpatient->GetAppointmentTime());
	//				this->enqueue(*Rpatient, Rpri);
	//			}
	//			else if(i<getCount())
	//			{
	//				peek(*Ptemp, tempPri);
	//				dequeue(*Ptemp, tempPri);
	//				this->enqueue(*Ptemp, tempPri);

	//			}
	//		}*/
	//	}
	//	else return false;
	//}
};
