//----------------------------------------------------
// Name: Timothy Leach        userID: tjleach
// Due Date: 11/02/2018
// Program Assignment 3
// File Name: thread.cpp
// Program Purpose: 
//    This is the thread implementation of the 
//  prefix sum algorithm. The program will get 
//  sent two arrays, the first is the previous
//  row of the main B array from thread-main.cpp
//  and the next is the current row of B. It 
//  will also get sent two ints, the first will 
//  be the current item in the array B and the 
//  second will be the item to add to the first int
//  The program will then set the current spot 
//  in B as the sum of the two numbers. 
//----------------------------------------------------



#include <iostream>
#include "thread.h"

thread::thread(int X[], int J, int b[], int I)
  :i(I), x(X), j(J), B(b)
{
  ThreadName.seekp(0, ios::beg);
  cout << "      Thread " << j << " created\n";
  if(i < 0)
    {
      cout << "      Thread " << j << " copies " << X[j];
    }
  else{
    cout << "      Thread " << j << " computes " << X[j] << " + " << X[i] << "\n";
  }
}

    void thread::ThreadFunc()
    {
      Thread::ThreadFunc();
      if(i < 0)
	{
	  B[j] = x[j];
	}
      else 
	{
	  B[j] = x[j] + x[i];
	}

      cout <<  "      Thread " << j << " exits\n";
      Exit();
    }
