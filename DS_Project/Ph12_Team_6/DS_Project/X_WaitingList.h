#pragma once
#include "EU_WaitingList.h"
#include "StackADT.h"

class X_WaitingList : public EU_WaitingList
{

public:
	X_WaitingList()
	{
	}
	bool  Cancel(Patient*& Cpatient, int Pcancel)
	{
		bool contain = false;
		Node<Patient*>* ptr = frontPtr;
		while (ptr)
		{

			if (ptr->getItem()->numberOfTreatments() == 0)
			{
				contain = true;
				break;
			}
			ptr = ptr->getNext();




		}

		int randommm = rand() % 101;

		if (randommm < Pcancel&& contain)
		{

			if (frontPtr == backPtr)
			{
				if (frontPtr == nullptr)
					return false;
				if (frontPtr->getItem()->CurrentTreatment()->getType() == 'X' && frontPtr->getItem()->numberOfTreatments() == 0)
				{
					Cpatient = frontPtr->getItem();
					frontPtr = NULL;
					backPtr = frontPtr;

					return true;
				}



			}
			else {
				Node<Patient*>* ptr = frontPtr->getNext();
				Node<Patient*>* prev = frontPtr;
				int i = 2;
				int RandomPatient = rand() % GetCount() + 1;

				while (ptr != NULL)
				{
					if (i == RandomPatient)

					{

						if (ptr->getItem()->CurrentTreatment()->getType() == 'X' && ptr->getItem()->numberOfTreatments() == 0)
						{
							Cpatient = ptr->getItem();
							prev->setNext(ptr->getNext());

							return true;
						}
						else
						{
							return false;
						}

					}
					else {

						ptr = ptr->getNext();
						prev = prev->getNext();
						i++;


					}






				} return false;










			}
		}
		else  return false;



	}
	bool Enqueue(Patient* newEntry)
	{
		return(enqueue(newEntry));
	} // end enqueue
	void Print()
	{
		PrintQueue();
	}




};