// Thread.cpp


#include "thread.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>


landLordThread::landLordThread(int n, int m): maxStudents(n), maxIterations(m)
{
  ThreadName.seekp(0, ios::beg);
}

void landLordThread::ThreadFunc()
{
  Thread::ThreadFunc();
  for(int i = 1; i <= maxIterations; i++)
    {
		Delay();
		Delay();
		Delay();
		CheckRoom(i, maxStudents, maxIterations);
		Delay();
    }
  Exit();
}


studentThread::studentThread(int j) : studentNum(j)
{
  ThreadName.seekp(0, ios::beg);
}

void studentThread::ThreadFunc()
{
  Thread::ThreadFunc();
  while(1)
    {
      Delay();
      GoToParty(studentNum);
      Delay();
    }
  Exit();
}
