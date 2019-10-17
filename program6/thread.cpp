//----------------------------------------------
// Name: Timothy Leach    userID: tjleach
// Due Date: 12/14/2018
// Program Assignment 6
// File Name: thread.cpp
// Program Purpose:
//      implementation of the processors for
//   matrix multiplication
//----------------------------------------------

#include <string.h>
#include <stdio.h>
#include <iostream>
#include "ThreadClass.h"
#include "thread.h"


extern SynOneToOneChannel *rightChannels[100][100];
extern SynOneToOneChannel *downChannels[100][100];
extern int inA[100][100];
extern int inB[100][100];
extern int outC[100][100];
extern int rowsA;
extern int rowsB;
extern int rowsC;
extern int colsA;
extern int colsB;
extern int colsC;


EdgeProcessor::EdgeProcessor(int id, int type)
{
    processID = id;
    processorType = type;
    ThreadName.seekp(0, ios::beg);
    ThreadName << "Outer" << processID << ends;

    UserDefinedThreadID = processID;
}

void EdgeProcessor::ThreadFunc()
{
    Thread::ThreadFunc();
    Thread_t self = GetID();

    if(processorType == 1)
    {
        sprintf(buf, "Row thread r[%d] started\n", processID);
        write(1, buf, strlen(buf));

        for(i = 1; i <= colsA; i++)
        {
            num = inA[processID-1][i-1];
            rightChannels[processID][1]->Send(&num, sizeof(int));
            sprintf(buf, "   Column thread c[%d] sent %d to P[%d,%d]\n", processID, num, 1, processID);
            write(1, buf, strlen(buf));
        }
    }
    else
    {
        for(i = 1; i <= rowsB; i++)
        {
            num = inB[i - 1][processID-1];
            downChannels[1][processID]->Send(&num, sizeof(int));
            sprintf(buf, "   Column thread c[%d] sent %d to P[%d, %d]\n", processID, num, 1, processID);
            write(1, buf, strlen(buf));
        }
        num = -1;
        downChannels[1][processID]->Send(&num, sizeof(int));

        sprintf(buf, "   Column thread c[%d] sent EOD to P[%d, %d] and terminated\n", processID, 1, processID);
        write(1, buf, strlen(buf));
    }

    Exit();
}


EdgeProcessor::~EdgeProcessor()
{

}

Processor::Processor(int row, int column)
{
    rowID = row;
    cID = column;
    num = 0;

    ThreadName.seekp(0, ios::beg);
    ThreadName << "Inner" << rowID << cID << ends;

    UserDefinedThreadID = rowID + cID;
}

void Processor::ThreadFunc()
{
    Thread::ThreadFunc();
    Thread_t self = GetID();

    while(true)
    {
        downChannels[rowID][cID]->Receive(&up, sizeof(int));

        if(up == -1)
        {
            if(rowID < rowsC)
            {
                downChannels[rowID+1][cID]->Send(&up, sizeof(int));
            }
            outC[rowID][cID] = num;
            sprintf(buf, "      Thread P[%d, %d] received EOD, saved result %d and terminated\n", rowID, cID, num);
            write(1, buf, strlen(buf));
            Exit();
        }
        rightChannels[rowID][cID]->Receive(&left, sizeof(int));

        sprintf(buf, "      Thread P[%d, %d] received %d from up and %d from left\n", rowID, cID, up, left);
        write(1, buf, strlen(buf));


        if(rowID < rowsC)
        {
            downChannels[rowID + 1][cID]->Send(&up, sizeof(int));
            sprintf(buf, "      Thread P[%d, %d] sent %d down to P[%d, %d]\n", rowID, cID, up, rowID +1, cID);
            write(1, buf, strlen(buf));
        }

        if(cID < colsC)
        {
            rightChannels[rowID][cID+1]->Send(&left, sizeof(int));
            sprintf(buf, "      Thread P[%d, %d] sent %d right to P[%d, %d]\n", rowID, cID, left, rowID, cID+1);
            write(1, buf, strlen(buf));
        }

        num = num + (up * left);
    }
}
