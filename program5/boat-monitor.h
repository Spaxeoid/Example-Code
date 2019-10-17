//---------------------------------------------
// Name: Timothy Leach       userID: tjleach
// Due Date: 12/07/2018
// Program 5
// File Name: boat-monitor.h 
// Program Purpose: 
//   Header file for boat-monitor.cpp
//---------------------------------------------

#include "ThreadClass.h"

class BoatMonitor : public Monitor
{
	public: 
		BoatMonitor(int L);
		
		void BoatReady(int loadID);
		void BoatDone();
		void CannibalArrives(int canID);
		void MissionaryArrives(int missID);

	private:
		Condition *riding;
		Condition *canArrived; 
		Condition *missArrived;
		Condition *loading;
		Condition *boatWaiting;
		int loads;
		int numWaiting;
		int riders; 
		int boatState;
		int cannibalsWaiting;
		int missionariesWaiting;
		char riderType[3];
		int riderID[3];
		char buf[100];
		
		void ThreadFunc();
		void Load(int L);
};