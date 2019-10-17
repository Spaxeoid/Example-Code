//----------------------------------------------
// Name: Timothy Leach         userID: tjleach
// Due Date: 12/07/2018
// File Name: thread.cpp
// Program Purpose:
//      Actual code implementation of the boat,
//   missionary and cannibal threads.
//----------------------------------------------

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "thread.h"
#include "boat-monitor.h"


static BoatMonitor *Boat = new BoatMonitor(3);


Cannibal::Cannibal(int cID)
{
    canID = cID;
}

void Cannibal::ThreadFunc() {
    Thread::ThreadFunc();

    while(1){
        Delay(rand() % 200);
        Boat->CannibalArrives(canID);
    }
}


Missionary::Missionary(int mID)
{
    missID = mID;
}

void Missionary::ThreadFunc()
{
    Thread::ThreadFunc();

    while(1)
    {
        Delay(rand() % 200);
        Boat->MissionaryArrives(missID);
    }
}

BoatThread::BoatThread(int boatLoads) {
    loads = boatLoads;
}

void BoatThread::ThreadFunc()
{
    Thread::ThreadFunc();

    for(i = 1; i <= loads; i++)
    {
        Delay();
        Boat->BoatReady(i);
        Delay();
        Boat->BoatDone();
        sprintf(buf, "***** Boat load (%d): Completed\n", i);
        write(1, buf, strlen(buf));
    }

    sprintf(buf, "MONITOR: %d crosses have been made.\n", loads);
    write(1, buf, strlen(buf));

    sprintf(buf, "MONITOR: This river cross is closed indefinitely for renovation.\n");
    write(1, buf, strlen(buf));

    exit(0);
}