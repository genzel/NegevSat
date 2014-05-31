/*
 * MPTask.cpp
 *
 *  Created on: May 3, 2014
 *      Author: dariaz
 */

#include <logics/tasks/MPTask.hpp>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <rtems++/rtemsEvent.h>
#include "data_protocol/ValidatorFactory.hpp"

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


MPTask::MPTask(SendReceiveQueue::SendReceiveQueue* receiveQ, WorkQueue::WorkQueue* _works) {
	receive_queue = receiveQ;
	works = _works;
	ValidatorFactory::ValidatorFactory factory;
	validator = factory.createValidator("XML");
}

MPTask::~MPTask() {
	// TODO Auto-generated destructor stub
}

bool MPTask::validateMessage(){
	return validator->validate();
}

vector<WorkDescription::WorkDescription> MPTask::parseMessage(){
	return parser.parsePacket(validator->getRoot());
}

void MPTask::enqueueToWorks(WorkDescription::WorkDescription work){
	works->enqueue(work);
}

void MPTask::body(rtems_task_argument argument){
	unsigned int i;
	for (;;){
		printf(" * MP TASK! *\n");
		printf(" * MP TASK::before dequeue *\n");
		string packet = receive_queue->dequeue();
		printf(" * MP TASK::after dequeue *\n");
		validator->buildPacket(packet);
		if (validateMessage()){

			vector<WorkDescription::WorkDescription> parsed_works = parseMessage();
			for (i=0; i<parsed_works.size(); i++){
				enqueueToWorks(parsed_works.at(i));
			}
		}
		else {
			printf(" * MP TASK:: validation of packet:\n %s \n FAILED!!!*\n", &packet[0]);
		}
	}

	exit(0);
}

