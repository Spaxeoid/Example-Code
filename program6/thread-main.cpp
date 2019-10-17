//----------------------------------------------
// Name: Timothy Leach          userID: tjleach
// Due Date: 12/14/2018
// Program 6
// File Name: thread-main.cpp
// Program Purpose:
//      This program uses channels and threads
//   to complete matrix multiplication
//   between two matrices.
//----------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include "thread.h"
#include "ThreadClass.h"


SynOneToOneChannel* rightChannels[100][100];
SynOneToOneChannel* downChannels[100][100];

int inA[100][100];
int inB[100][100];
int outC[100][100];
int rowsA;
int rowsB;
int rowsC;
int colsA;
int colsB;
int colsC;


int main(void)
{
    int i, k;
    char buf[100];

    scanf("%d", &rowsA);
    scanf("%d", &colsA);

    sprintf(buf, "%d rows, %d cols\n", rowsA, colsA);
    write(1, buf, strlen(buf));
    for(i = 0; i < rowsA; i++)
    {
        for(k = 0; k < colsA; k++)
        {
            scanf("%d", &inA[i][k]);
        }
    }

    scanf("%d", &rowsB);
    scanf("%d", &colsB);

    if(colsA != rowsB)
    {
        sprintf(buf, "ERROR: The rows of B do not match the columns of A, matrix multiplication is impossible\n Exiting\n");
        write(1, buf, strlen(buf));
        Exit();
    }

    for(i = 0; i < rowsB; i++)
    {
        for(k = 0; k < colsB; k++)
        {
            scanf("%d", &inB[i][k]);
        }
    }

    rowsC = rowsA;
    colsC = colsB;

    sprintf(buf, "C rows: %d C columns: %d\n", rowsC, colsC);
    write(1, buf, strlen(buf));

    for(i = 0; i <= rowsC; i++)
    {
        for(k = 0; k <= colsC; k++)
        {
            rightChannels[i][k] = new SynOneToOneChannel("Channel", 0, 0);
            downChannels[i][k] = new SynOneToOneChannel("Channel", 0, 0);
        }
    }

    EdgeProcessor* edgeRows[rowsC+1];
    for(i = 1; i <= rowsC; i++)
    {
        edgeRows[i] = new EdgeProcessor(i, 1);
        edgeRows[i]->Begin();
    }

    EdgeProcessor* edgeCols[colsC+1];
    for(i = 1; i <= colsC; i++)
    {
        edgeCols[i] = new EdgeProcessor(i, 0);
        edgeCols[i]->Begin();
    }

    Processor* inside[rowsC+1][colsC+1];
    for(i = 1; i <= rowsC; i++)
    {
        for(k = 1; k <= colsC; k++)
        {
            inside[i][k] = new Processor(i, k);
            inside[i][k]->Begin();
        }
    }


    for(i = 1; i <= rowsA; i++)
    {
        edgeRows[i]->Join();
    }
    for(i = 1; i <= colsB; i++)
    {
        edgeCols[i]->Join();
    }

    for(i = 1; i <= rowsC; i++)
    {
        for(k = 1; k <= colsC; k++)
        {
            inside[i][k]->Join();
        }
    }

    sprintf(buf, "*** Main ***\n");
    write(1, buf, strlen(buf));

    sprintf(buf, "Matrix A: %2d rows and %2d columns\n", rowsA, colsA);
    write(1, buf, strlen(buf));

    for(i = 0; i < rowsA; i++)
    {
        for(k = 0; k < colsA; k++)
        {
            sprintf(buf, "%2d ", inA[i][k]);
            write(1, buf, strlen(buf));
        }
        sprintf(buf, "\n");
        write(1, buf, strlen(buf));
    }

    sprintf(buf, "Matrix B: %2d rows and %2d columns\n", rowsB, colsB);
    write(1, buf, strlen(buf));


    for(i = 0; i < rowsB; i++)
    {
        for(k = 0; k <colsB; k++)
        {
            sprintf(buf, "%2d ", inB[i][k]);
            write(1, buf, strlen(buf));
        }
        sprintf(buf, "\n");
        write(1, buf, strlen(buf));
    }

    sprintf(buf, "Matrix C = A*B: %2d rows and %2d columns\n", rowsC, colsC);
    write(1, buf, strlen(buf));


    for(i = 1; i <= rowsC; i++)
    {
        for(k = 1; k <= colsC; k++)
        {
            sprintf(buf, "%4d ", outC[i][k]);
            write(1, buf, strlen(buf));
        }
        sprintf(buf, "\n");
        write(1, buf, strlen(buf));
    }

}