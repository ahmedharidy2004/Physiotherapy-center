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

			Patient* Rpatient = NULL;
			Patient* Ptemp = NULL;
			int tempPri = 0, Rpri = 0;
			if (head == NULL)
				return false;
			if (head->getNext() == NULL)
			{
				int dummy = 0;
				head->getItem(dummy)->SetAppointmentTime(rand() % 50 + head->getItem(dummy)->GetAppointmentTime());
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
			}
			/*for (int i = 1; i <= getCount(); i++)
			{
				if (i == RandomPatient )
				{
					peek(*Rpatient, Rpri);
					dequeue(*Rpatient, Rpri);
					Rpatient->SetAppointmentTime(rand() % 50 + Rpatient->GetAppointmentTime());
					this->enqueue(*Rpatient, Rpri);
				}
				else if(i<getCount())
				{
					peek(*Ptemp, tempPri);
					dequeue(*Ptemp, tempPri);
					this->enqueue(*Ptemp, tempPri);

				}
			}*/
		}
		else return false;
	}
};
