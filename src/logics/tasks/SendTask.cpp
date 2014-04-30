/*
 * SendTask.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */

#include "SendTask.hpp"
#include "communication/CommunicationHandlerFactory.hpp"
#include <iostream>
#include <stdio.h>

/* c.f. cpukit/score/include/rtems/score/priority.h */
#define PRIiPriority_Control PRIi32
/* rtems_task_priority is a typedef to Priority_Control */
#define PRIirtems_task_priority PRIiPriority_Control

/* c.f. cpukit/rtems/include/rtems/rtems/modes.h */
#define PRIXModes_Control PRIX32
#define PRIiModes_Control PRIi32
/* rtems_mode is a typedef to Modes_Control */
#define PRIXrtems_mode PRIXModes_Control
#define PRIirtems_mode PRIiModes_Control

/* c.f. cpukit/score/include/rtems/score/isr.h */
#define PRIiISR_Level PRIi32
/* rtems_interrupt_level is a typedef to ISR_Level */
#define PRIirtems_interrupt_level PRIiISR_Level

SendTask::SendTask(SendReceiveQueue::SendReceiveQueue* sendQ)
		:rtemsTask()
{
	printf("inside send task constructor\n");
	//cout << "inside send task constructor" << endl;
	sendQueue = sendQ;
	CommunicationHandlerFactory::CommunicationHandlerFactory factory;
	comm_handler = factory.createHandler("uart");
}

void SendTask::send(string packet){
	comm_handler->send(&packet[0], packet.length());
}

string SendTask::dequeueMessage(){
	return sendQueue->dequeue();
}


rtems_task SendTask::body(rtems_task_argument argument){
	//argument = arg;
	for (;;){
		string packet = dequeueMessage();
		cout << "Dequeued the packet: " << packet << endl;
		cout << "Sending ..." << endl;
		send(packet);
	}
}
