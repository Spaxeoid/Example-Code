// Support File for the program

#include <iostream>
#include <stdlib.h>
#include "thread.h"



static Mutex Door("Door");
static Mutex DoorExit("DoorExit");
static Mutex landLordCheck("landLordCheck");
static Mutex landLordLeaves("landLordLeaves");
static Semaphore printMutex("printMutex", 1);

static int studentCount = 0;
static int llChecking = 0;
static int llLastCheck = 0;

void studentThread::GoToParty(int studentNum)
{
  printMutex.Wait();
  cout << "     Student " << studentNum << " waits to enter the room\n";
  printMutex.Signal();

  Door.Lock();
  landLordCheck.Lock();
  if(llLastCheck == 1)
    {
      printMutex.Wait();
      cout << "     Student " << studentNum << " terminates\n";
      printMutex.Signal();
      Door.Unlock();
      landLordCheck.Unlock();
      Exit();
    }
  studentCount++;

  printMutex.Wait();
  cout << "     Student " << studentNum << " enters the room (" << studentCount << " students in the room)\n";
  printMutex.Signal();

  landLordCheck.Unlock();
  Door.Unlock();

	Delay();

  printMutex.Wait();
  cout << "     Student " << studentNum << " waits to leave the room\n";
  printMutex.Signal();

  DoorExit.Lock();
  //landLordLeaves.Lock();
  studentCount--;

  printMutex.Wait();
  cout << "     Student " << studentNum << " leaves the room (" << studentCount << " students in the room)\n";
  printMutex.Signal();

  //landLordCheck.Unlock();
  DoorExit.Unlock();
}


void landLordThread::CheckRoom(int i, int n, int m)
{
  Door.Lock();
landLordCheck.Lock();
  printMutex.Wait();
  cout << "The landlord checks the room for the " << i << "-th time\n";
  printMutex.Signal();
  if((studentCount > n))
    {
      printMutex.Wait();
      cout << "The landlord finds " << studentCount << " students in the room and breaks up the party\n";
      printMutex.Signal();
	  
	  landLordLeaves.Unlock();
	  DoorExit.Unlock();
    }
  else if(studentCount <= n)
    {
      printMutex.Wait();
      cout << "The landlord finds there are " << studentCount << " students in the room ";
      cout << "(the condition being good) and leaves.\n";
      printMutex.Signal();
    }
  else if(studentCount == 0)
    {
      printMutex.Wait();
      cout << "The landlord finds the room has no students and leaves.\n";
      printMutex.Signal();
    }
  if(i == m)
    {
      llLastCheck = 1;
	  for(int j = 0; j < studentCount; j++)
		{
		landLordLeaves.Unlock();
		}
	}
  landLordLeaves.Unlock();
  landLordCheck.Unlock();
  Door.Unlock();
}
