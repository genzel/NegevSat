/*
 * LifeCycleTask.cpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#include <logics/tasks/LifeCycleTask.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "utils/stringutils.hpp"
#include "logics/NegevSatStates.hpp"

using namespace std;
using namespace stringutils;

LifeCycleTask::LifeCycleTask(WorkQueue::WorkQueue* _rdy_works, SendReceiveQueue::SendReceiveQueue** _send_queues) {
	rdy_works = _rdy_works;
	send_queues = _send_queues;
	samples_counter = 0;
	state = INIT_STATE;
}

LifeCycleTask::~LifeCycleTask() {
	// TODO Auto-generated destructor stub
}

void LifeCycleTask::control_unit_samples(){
	/*if (samples_counter == 0){
		parser.createPacket("","Energy");
		parser.createPacket("", "Temperature");
		string state_str = "";
		state_str = int_to_string(state,state_str);
		parser.createPacket(state_str.c_str(),"Static");
	}
	int energy = hardware.getEnergy();
	int current = hardware.getEnergyCurrent();
	Sample::Sample sample("EnergySample", "122");
	map<const char*,const char*> measure;
	measure.insert(pair<const char*,const char*>("voltage", str_to_chars(int_to_string(energy))));
	measure.insert(pair<const char*,const char*>("current", str_to_chars(int_to_string(current))));
	sample.addMeasure("Battery1", measure);
	parser.addSampleToPacket(sample,"Energy");*/

}

void LifeCycleTask::attitude_control(){
	control_unit_samples();
}

void LifeCycleTask::logics(){

}

void LifeCycleTask::perform_cmd(){

}

void LifeCycleTask::monitoring(){

}

void LifeCycleTask::module_ctrl(){

}

void LifeCycleTask::thermal_ctrl(){

}

void LifeCycleTask::body(rtems_task_argument argument){
	for (;;){
		printf(" * LifeCycle TASK! *\n");
		attitude_control();
		logics();
		perform_cmd();
		monitoring();
		module_ctrl(); // turn on or off modules
		thermal_ctrl();
	}
	exit(0);
}


