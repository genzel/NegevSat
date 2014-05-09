/*
 * ReceiveTask.hpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#ifndef RECEIVETASK_HPP_
#define RECEIVETASK_HPP_

#include "communication/SendReceiveQueue.hpp"
#include "communication/UartCommunicationHandler.hpp"
#include <rtems++/rtemsTask.h>
#include <string>

using namespace std;

class ReceiveTask : public rtemsTask{
private:
	ICommunicationHandler::ICommunicationHandler* comm_handler;
	SendReceiveQueue::SendReceiveQueue* receive_queue;

protected:
	virtual void body(rtems_task_argument argument);

public:
	ReceiveTask(SendReceiveQueue::SendReceiveQueue* receiveQ);
	virtual ~ReceiveTask();
	string receive();
	void enqueue_message(string msg);
};

#endif /* RECEIVETASK_HPP_ */
