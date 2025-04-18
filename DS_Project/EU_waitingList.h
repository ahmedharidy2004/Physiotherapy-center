#pragma once
#include "LinkedQueue.h"
#include "Patient.h"
class EU_WaitingList : public LinkedQueue<Patient*>
{
public:
    void InsertSorted(Patient*& p) {
        if (!p)
        {
            return;
        }
        int time;
        Node<Patient*>* pat = new Node<Patient*>(p);
        count++;
        if (p->GetArrivalTime() > p->GetAppointmentTime()) {
            time = p->GetAppointmentTime() + (p->GetArrivalTime() - p->GetAppointmentTime()) / 2;
        }
        else {
            time = p->GetAppointmentTime();
        }

        // Case 1: Empty list
        if (!frontPtr) {
            frontPtr = backPtr = pat;
            return;
        }

        // Case 2: Insert at front
        if (time < frontPtr->getItem()->GetAppointmentTime()) {
            pat->setNext(frontPtr);
            frontPtr = pat;
            return;
        }

        // Case 3: Traverse to find correct position
        Node<Patient*>* ptr = frontPtr;
        Node<Patient*>* prev = nullptr;

        while (ptr && time >= ptr->getItem()->GetAppointmentTime()) {
            prev = ptr;
            ptr = ptr->getNext();
        }

        // Insert in middle or at end
        if (prev) {
            prev->setNext(pat);
        }

        pat->setNext(ptr);

        if (!ptr) {
            backPtr = pat; // if inserted at end
        }
    }

    int calcTreatmentLatency() {
        int treatmentLatency = 0;
        Node<Patient*>* ptr = frontPtr;
        while (ptr) {
            treatmentLatency += ptr->getItem()->getCurrTreatmentDuration();
            ptr = ptr->getNext();
        }
        return treatmentLatency;
    }
    EU_WaitingList() {

    }
    ~EU_WaitingList() {

    }
};

