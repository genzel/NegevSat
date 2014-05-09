/*
 * SendTask.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */

#include "SendTask.hpp"
#include "communication/CommunicationHandlerFactory.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <rtems++/rtemsEvent.h>
#include "logics/SendReceiveConf.hpp"

using namespace std;
/*
 c.f. cpukit/score/include/rtems/score/priority.h
#define PRIiPriority_Control PRIi32
 rtems_task_priority is a typedef to Priority_Control
#define PRIirtems_task_priority PRIiPriority_Control

 c.f. cpukit/rtems/include/rtems/rtems/modes.h
#define PRIXModes_Control PRIX32
#define PRIiModes_Control PRIi32
 rtems_mode is a typedef to Modes_Control
#define PRIXrtems_mode PRIXModes_Control
#define PRIirtems_mode PRIiModes_Control

 c.f. cpukit/score/include/rtems/score/isr.h
#define PRIiISR_Level PRIi32
 rtems_interrupt_level is a typedef to ISR_Level
#define PRIirtems_interrupt_level PRIiISR_Level
 */

SendTask::SendTask(SendReceiveQueue::SendReceiveQueue** sendQ)
:rtemsTask()
{

	sendQueues = sendQ;
	CommunicationHandlerFactory::CommunicationHandlerFactory factory;
	comm_handler = factory.createHandler("uart");
	send_type = STATIC_SEND;
}

void SendTask::send(string packet){
	comm_handler->send(&packet[0], packet.length());
}

string SendTask::dequeueMessage(int index){
	return sendQueues[index]->dequeue();
}


rtems_task SendTask::body(rtems_task_argument argument){
	for (;;){
		printf(" * SEND TASK! *\n");
		rtemsEvent send_type_event;
		rtems_event_set out;
		rtems_status_code status = send_type_event.receive((STATIC_SEND | ENERGY_SEND | TEMP_SEND | MIXED_SEND), out, 0, rtemsEvent::no_wait, rtemsEvent::any);
		if (status != RTEMS_SUCCESSFUL){
			//printf(" * SEND TASK:: failed to receive event for sending type *\n");
			//continue;
		}
		else {
			printf(" * SEND TASK:: changed send type to %d *\n", out);
			send_type = out;
		}
		string packet;
		switch (send_type) {
		case STATIC_SEND:
			printf(" * SEND TASK:: type of send is STATIC_SEND *\n");
			/*packet = sendQueues[SENDQ_STATIC_INDEX]->dequeue();
			send(packet);*/
			break;
		case ENERGY_SEND:
			printf(" * SEND TASK:: type of send is ENERGY_SEND *\n");
			/*packet = sendQueues[SENDQ_ENERGY_INDEX]->dequeue();
			send(packet);*/
			break;
		case TEMP_SEND:
			printf(" * SEND TASK:: type of send is TEMP_SEND *\n");
			/*packet = sendQueues[SENDQ_TEMP_INDEX]->dequeue();
			send(packet);*/
			break;
		case MIXED_SEND:
			printf(" * SEND TASK:: type of send is MIXED_SEND *\n");
			/*packet = sendQueues[SENDQ_ENERGY_INDEX]->dequeue();
			send(packet);
			packet = sendQueues[SENDQ_TEMP_INDEX]->dequeue();
			send(packet);*/
			break;
		}
	}
	exit(0);
}
