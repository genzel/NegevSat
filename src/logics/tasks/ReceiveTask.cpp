/*
 * ReceiveTask.cpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#include <logics/tasks/ReceiveTask.hpp>
#include "communication/CommunicationHandlerFactory.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

ReceiveTask::ReceiveTask(SendReceiveQueue::SendReceiveQueue* receiveQ) {
	receive_queue = receiveQ;
	CommunicationHandlerFactory::CommunicationHandlerFactory factory;
	comm_handler = factory.createHandler("uart");
}

ReceiveTask::~ReceiveTask() {
	// TODO Auto-generated destructor stub
}

string ReceiveTask::receive(){
	return comm_handler->receive();
}

void ReceiveTask::enqueue_message(string msg){
	receive_queue->enqueue(msg);
}

rtems_task ReceiveTask::body(rtems_task_argument argument){
	for(;;) {
		printf(" * RECEIVE TASK! *\n");
		string msg = receive();
		if (comm_handler->verifyBytes(msg)){
			enqueue_message(msg);
		}
		else {
			printf(" * RECEIVE TASK:: bytes which were received are not verified *\n");
		}
	}
	exit(0);
}

