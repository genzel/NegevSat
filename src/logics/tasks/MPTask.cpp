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
#include "EndTask.hpp"
#include <rtems++/rtemsEvent.h>

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


MPTask::MPTask() {
	// TODO Auto-generated constructor stub

}

MPTask::~MPTask() {
	// TODO Auto-generated destructor stub
}

void MPTask::printBlaBla(void) {
	printf(" * BLABLA *\n");
}

void MPTask::body(rtems_task_argument argument){
	for (;;){
		printf(" * MP TASK! *\n");
	}
	//printBlaBla();
	exit(0);
}

