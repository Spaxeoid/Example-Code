//----------------------------------------------
// Name: Timothy Leach       userID: tjleach
// Due Date: 12/14/2018
// Program 6
// File Name: thread.h
// Program Purpose:
// 		Header file for thread.cpp
//----------------------------------------------


#include "ThreadClass.h"

class EdgeProcessor : public Thread 
{
	public:
		EdgeProcessor(int id, int type);
		~EdgeProcessor();
		SynOneToOneChannel *channel;
		
	private:
		int processID;
		int num;
		int processorType;
		int i;
		char buf[100];
		
		void ThreadFunc();
		
};

class Processor : public Thread
{
	public: 
		Processor(int row, int column);
		~Processor();
		SynOneToOneChannel *down;
		SynOneToOneChannel *right;
		
	private:
		int processID;
		int rowID;
		int cID;
		int num;
		int up;
		int left;
		char buf[100];
		
		void ThreadFunc();
};
