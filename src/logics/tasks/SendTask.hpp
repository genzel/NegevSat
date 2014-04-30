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


class SendTask : public rtemsTask
{
private:
	ICommunicationHandler::ICommunicationHandler* comm_handler;
	SendReceiveQueue::SendReceiveQueue* sendQueue;

protected:
	virtual void body(rtems_task_argument argument);

public:
	SendTask(SendReceiveQueue::SendReceiveQueue* sendQ);
	void send(string packet);
	string dequeueMessage();
};
#endif /* SENDTASK_HPP_ */


