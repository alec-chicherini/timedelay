#include "timedelay.h"
#include <iostream>
#include <chrono> // std::chrono::seconds
#include <thread> // std::this_thread::sleep_for

//sleep for some secondson this thread
void sleep (int x)
{
	std::this_thread::sleep_for(std::chrono::seconds{ x });
}


int main()
{

	
	timedelay T;
	//creating first timer with name first and 3 second wait condition. before timer is over it return 0 after 1
	T.addTimer("first",10.0);
	sleep(1);

	T.addTimer("second", 4.0);
	sleep(1);

	std::cout << "first timer:checkTimer"<<std::endl;
	std::cout << "second timer:checkTimer" << std::endl;

	std::cout<<T.readTimer("first")<<":"<<T.checkTimer("first")<<std::endl;
	std::cout<<T.readTimer("second") << ":" << T.checkTimer("second") << std::endl;

	sleep(3);

	std::cout << T.readTimer("first") << ":" << T.checkTimer("first") << std::endl;
	std::cout << T.readTimer("second") << ":" << T.checkTimer("second") << std::endl;

	sleep(3);

	std::cout << T.readTimer("first") << ":" << T.checkTimer("first") << std::endl;
	std::cout << T.readTimer("second") << ":" << T.checkTimer("second") << std::endl;

	sleep(3);

	std::cout << T.readTimer("first") << ":" << T.checkTimer("first") << std::endl;
	std::cout << T.readTimer("second") << ":" << T.checkTimer("second") << std::endl;

	std::cout << std::endl;
   //this queue logic supposed using some cycle for example(0.1 sec each step) and we adding timers sometimes 
   //and have have access and need check state is it the first element over or not.

	
	// 0sec     {3}  ...adding timer 3sec...  
    // 0sec     {3,5}  ...adding timer 3sec...  

	// time		queue  checkQueue()
    //2.5 sec {3,5} ...after checking do nothing.. check timer return 0.
	//3.1 sec {5}  ... after checking first timer is over and deleted. only 5sec next timer in queue. return 1.
	//4.4 sec {5} ...do nothing. return 0
	//5.1 sec {} ...5 sec timer expiring, deleted and return 1.
	//5.5 sec {} ...queue empty - return 0.
	//6.0 sec {7} ...
	//13.1 sec {0} ...7 sec timer expiring after adding, deleted and return 1.
	
	T.addAtQueue(3);
	T.addAtQueue(5);
	

	std::cout << "queue: cQ queueTest()" << std::endl;
	T.addTimer("queue");
	while (T.readTimer("queue")<20)
	{
		sleep(1);
		
		std::cout << T.readTimer("queue")<<" ";
		std::cout << T.checkQueue()<<" ";
		std::cout << T.queueTest()<<std::endl;

		//adding new timer inside loop
		if(T.readTimer("queue")>5.6 && T.readTimer("queue") < 6.5)T.addAtQueue(7);
	}


	return 1;

}


