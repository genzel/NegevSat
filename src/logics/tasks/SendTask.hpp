/*
 * SendTask.hpp
 *
 *  Created on: Apr 26, 2014
 *      Author: dariaz
 */

#ifndef SENDTASK_HPP_
#define SENDTASK_HPP_

#include "communication/SendReceiveQueue.hpp"
#include "communication/UartCommunicationHandler.hpp"
#include <rtems++/rtemsTask.h>

#define STATIC_SEND 		RTEMS_EVENT_1
#define ENERGY_SEND 		RTEMS_EVENT_2
#define TEMP_SEND 			RTEMS_EVENT_3
#define MIXED_SEND 			RTEMS_EVENT_4


class SendTask : public rtemsTask
{
private:
	ICommunicationHandler::ICommunicationHandler* comm_handler;
	SendReceiveQueue::SendReceiveQueue** sendQueues;
	int send_type;
protected:
	virtual void body(rtems_task_argument argument);

public:
	SendTask(SendReceiveQueue::SendReceiveQueue** sendQ);
	void send(string packet);
	string dequeueMessage(int index);
};
#endif /* SENDTASK_HPP_ */


