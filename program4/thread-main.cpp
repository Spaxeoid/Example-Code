// Thread Main



#include <iostream>
#include "thread.h"


int main(int argc, char *argv[])
{

  int n, m, k;
  m = atoi(argv[1]);
  n = atoi(argv[2]);
  k = atoi(argv[3]);

  if(m == 0)
  {
	m = 5;	
  }
  if(n == 0)
  {
	n = 5;
  }
  if(k == 0)
  {
	k = 10;
  }
  
  studentThread *student[k];

  int i = 0;
  for(i = 0; i < k; i++)
    {
      student[i] = new studentThread(i);
      student[i]->Begin();
    }

  landLordThread *landLord = new landLordThread(n, m);

  landLord->Begin();

  for(i = 0; i < k; i++)
    {
      student[i]->Join();
    }
    
  landLord->Join();
  cout << "After checking the room " << n << " times, the landlord retires and is on vacation!\n";


}
