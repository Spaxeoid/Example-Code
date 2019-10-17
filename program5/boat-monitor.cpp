//----------------------------------------------
// Name: Timothy Leach        userID: tjleach
// Due Date: 12/07/2018
// Program 5
// File Name: boat-monitor.cpp
// Program Purpose:
//     implementation of boat-monitor
//----------------------------------------------


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "thread.h"
#include "boat-monitor.h"



BoatMonitor::BoatMonitor(int L) : Monitor("Boat", HOARE)
{
    loads = L;
    numWaiting = 0;
    riders = 0;
    cannibalsWaiting = 0;
    missionariesWaiting = 0;
    boatState = 0;

    riding = new Condition("Riding");
    canArrived = new Condition("cArrived");
    missArrived = new Condition("mArrived");
    loading = new Condition("boatLoad");
    boatWaiting = new Condition("boatWait");


    srand(time(NULL));
}

void BoatMonitor::BoatReady(int L)
{
    MonitorBegin();

    char buf[100];

    sprintf(buf, "***** The boat is ready\n");
    write(1, buf, strlen(buf));

    Load(L);

    if(riders < 3)
    {
        boatState = 1;
        boatWaiting->Wait();
    }

    sprintf(buf, "***** Boat Load(%d): Passenger list(%c%d, %c%d, %c%d)\n", L, riderType[0],
            riderID[0], riderType[1], riderID[1], riderType[2], riderID[2]);
    write(1, buf, strlen(buf));

    boatState = 0;

    MonitorEnd();
}

void BoatMonitor::BoatDone()
{
    MonitorBegin();

    int i;
    for(i = 0; i < 3; i++)
    {
        riding->Signal();
    }

    MonitorEnd();
}

void BoatMonitor::CannibalArrives(int canID)
{
    MonitorBegin();
    char s = ' ';
    char buf[100];

    sprintf(buf, "%*c Cannibal %d arrives\n",canID-1, s, canID);
    write(1, buf, strlen(buf));

    if((riders < 3 && boatState == 1) == 0)
    {
        numWaiting++;
        cannibalsWaiting++;
        canArrived->Wait();
        numWaiting--;
        cannibalsWaiting--;
    }

    riders++;

    if(riders == 1)
    {
        riderType[0] = 'c';
        riderID[0] = canID;
    }
    if(riders == 2)
    {
        riderType[1] = 'c';
        riderID[1] = canID;
    }
    if(riders == 3)
    {
        riderType[2] = 'c';
        riderID[2] = canID;
        boatWaiting->Signal();
    }
    riding->Wait();
    riders--;
    MonitorEnd();
}

void BoatMonitor::MissionaryArrives(int missID)
{
    MonitorBegin();

    char s = ' ';
    char buf[100];
    sprintf(buf, "%*c Missionary %d arrives\n",missID-1, s, missID);
    write(1, buf, strlen(buf));

    if((riders < 3 && boatState == 1) == 0)
    {
        numWaiting++;
        missionariesWaiting++;
        missArrived->Wait();
        numWaiting--;
        missionariesWaiting--;
    }

    riders++;

    if(riders == 1)
    {
        riderType[0] = 'm';
        riderID[0] = missID;
    }
    if(riders == 2)
    {
        riderType[1] = 'm';
        riderID[1] = missID;
    }
    if(riders == 3)
    {
        riderType[2] = 'm';
        riderID[2] = missID;
        boatWaiting->Signal();
    }
    riding->Wait();
    riders--;
    MonitorEnd();
}

void BoatMonitor::Load(int l)
{
    char buf[100];
    int r = rand() % 3;

    if(r == 0)
    {
        if(missionariesWaiting > 1 && cannibalsWaiting > 0)
        {
            missArrived->Signal();
            missArrived->Signal();
            canArrived->Signal();

            sprintf(buf, "MONITOR(%d): two missionaries and one cannibal are selected\n", l);
            write(1, buf, strlen(buf));
        }
    }
    else if(r == 1)
    {
        if(missionariesWaiting > 2)
        {
            missArrived->Signal();
            missArrived->Signal();
            missArrived->Signal();
            sprintf(buf, "MONITOR(%d): 3 missionaries are selected\n", l);
            write(1, buf, strlen(buf));
        }
    }
    else if(r == 2)
    {
        if(cannibalsWaiting > 2)
        {
            canArrived->Signal();
            canArrived->Signal();
            canArrived->Signal();
            sprintf(buf, "MONITOR(%d): 3 cannibals are selected\n", l);
            write(1, buf, strlen(buf));
        }
    }
    return;

}