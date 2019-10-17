//----------------------------------------------
// Name: Timothy Leach    userID: tjleach
// Due Date: 12/07/2018
// Program 5
// File Name: thread-main.cpp
// Program Purpose:
//    Main thread code that gets input from the
//  user and starts the program.
//----------------------------------------------


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread.h"
#include "boat-monitor.h"

using namespace std;

int main(int argc, char* argv[])
{
    char buf[100];
    int i;

    int cannibals = atoi(argv[1]);
    int missionaries = atoi(argv[2]);
    int loads = atoi(argv[3]);

    if(cannibals == 0)
    {
        cannibals = 8;
    }
    if(missionaries == 0)
    {
        missionaries = 8;
    }
    if(loads == 0)
    {
        loads = 5;
    }

    sprintf(buf, "Starting Crossing\n");
    write(1, buf, strlen(buf));

    BoatThread *bThread = new BoatThread(loads);
    bThread->Begin();

    Missionary *miss[missionaries];
    for(i = 1; i <= missionaries; i++)
    {
        miss[i] = new Missionary(i);
        miss[i]->Begin();
    }


    Cannibal *can[cannibals];
    for(i = 1; i <= cannibals; i++)
    {
        can[i] = new Cannibal(i);
        can[i]->Begin();
    }


    bThread->Join();
    for(i = 1; i <= missionaries; i++)
    {
        miss[i]->Join();
    }
    for(i = 1; i <= cannibals; i++) {
        can[i]->Join();
    }


    return 0;

}
