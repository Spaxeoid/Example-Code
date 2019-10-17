// Landlord Thread Header

#ifndef _THREAD_H
#define _THREAD_H

#include "ThreadClass.h"
//#include "thread-support.cpp"

class landLordThread : public Thread
{
 public: 
  landLordThread(int n, int m);
 private: 
  void ThreadFunc();
  void CheckRoom(int i, int n, int m);
  int maxStudents;
  int maxIterations;


};

class studentThread : public Thread
{
 public: 
  studentThread(int j);
 private: 
  void ThreadFunc();
  void GoToParty(int studentNum);
  int studentNum;
};


#endif
