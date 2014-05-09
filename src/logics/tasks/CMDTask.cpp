/*
 * CMDTask.cpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#include <logics/tasks/CMDTask.hpp>
#include <stdio.h>

CMDTask::CMDTask(WorkQueue::WorkQueue* _works, WorkQueue::WorkQueue* _rdy_works){
	works = _works;
	rdy_works = _rdy_works;
}

CMDTask::~CMDTask() {
	// TODO Auto-generated destructor stub
}

void CMDTask::schedule_work(WorkDescription::WorkDescription work){
	rdy_works->enqueue(work);
}

bool CMDTask::time_has_come(WorkDescription::WorkDescription work){
	return true;
}

void CMDTask::body(rtems_task_argument argument){
	for (;;){
		printf(" * CMD TASK! *\n");
		works->sortWorks();
		WorkDescription::WorkDescription work = works->dequeue();
		if (time_has_come(work)){
			rdy_works->enqueue(work);
		}
		else {
			works->enqueue(work);
		}

	}
}
