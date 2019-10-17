//-----------------------------------------
// Name: Timothy Leach   userID: tjleach
// Due Date: 11/02/2018
// Program Assignment 3
// File Name: thread.h
// Program Purpose: 
//    This is the header file for the thread.cpp
//  class and is used to create the variables and
//  functions that will be used in thread.cpp

#ifndef _THREAD_H
#define _THREAD_H

#include "ThreadClass.h"


class thread : public Thread
{
 public: 
  thread(int x[], int j, int B[], int i);
 private:
  //VARIABLES
  void ThreadFunc();
  int *x;
  int *B;
  int i;
  int j;

};

#endif
