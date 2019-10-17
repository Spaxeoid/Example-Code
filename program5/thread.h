//---------------------------------------------
// Name: Timothy Leach        userID: tjleach
// Due Date: 12/07/2018
// Program 5
// File Name: thread.h 
// Program Purpose:
//    Header file for the missionary and 
//  cannibal threads
//---------------------------------------------


#include "ThreadClass.h"

class Cannibal : public Thread 
{
	public:
		Cannibal(int cID);
	
	private: 
		int canID;
		char buf[100];
		void ThreadFunc();
};

class Missionary : public Thread
{
	public: 
		Missionary(int mID);
		
	private: 
		int missID;
		char buf[100];
		void ThreadFunc();
};

class BoatThread : public Thread
{
	public:
		BoatThread(int boatLoads);
		
	private: 
		int i;
		int loads;
		char buf[100];
		void ThreadFunc();
};
