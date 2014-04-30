/*
 * SendReceiveQueue.hpp
 *
 *  Created on: Apr 8, 2014
 *      Author: Genzel
 */

#ifndef SENDRECEIVEQUEUE_HPP_
#define SENDRECEIVEQUEUE_HPP_

using namespace std;

#include <queue>
#include <string>
#include <rtems.h>
#include <iostream>
#include <rtems++/rtemsSemaphore.h>

class SendReceiveQueue {

private:
	queue<string> pending_messages;
	rtems_id mutex_id;
	rtems_id produced_count_id;
	//rtemsSemaphore::rtemsSemaphore* sem;
public:
	SendReceiveQueue ();
	~SendReceiveQueue(){}
	void enqueue(string message);
	string dequeue();
};


#endif /* SENDRECEIVEQUEUE_HPP_ */
