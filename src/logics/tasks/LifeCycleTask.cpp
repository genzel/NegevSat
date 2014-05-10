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
#include "logics/NegevSatConstants.hpp"

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

	//TODO ADD TIMER!!!!!
	//TODO REFACTOR INTO OBJECT NAMED "SAMPLER"

	if (samples_counter == 0){
		parser.createPacket("","Energy");
		parser.createPacket("", "Temperature");
		parser.createPacket(state_to_chars(state),"Static");
	}
	// create energy sample
	int energy = hardware.getEnergy();
	int current = hardware.getEnergyCurrent();
	Sample::Sample energy_sample("EnergySample", "122");
	map<string,string> energy_measure;
	string energy_str = "";
	string current_str = "";
	energy_str = int_to_string(energy,energy_str);
	current_str = int_to_string(current,current_str);
	energy_measure.insert(pair<string,string>("voltage", energy_str));
	energy_measure.insert(pair<string,string>("current", current_str));
	energy_sample.addMeasure("Battery1", energy_measure);
	parser.addSampleToPacket(energy_sample,"Energy");

	// create temperature sample
	int temp = hardware.getTemperature();
	Sample::Sample temp_sample("TemperatureSample", "122");
	map<string,string> temp_measure;
	string temp_str = "";
	temp_str = int_to_string(temp,temp_str);
	temp_measure.insert(pair<string,string>("temp", temp_str));
	temp_sample.addMeasure("Sensor1", temp_measure);
	parser.addSampleToPacket(temp_sample,"Temperature");

	// create static sample
	int sband_module  = hardware.getSbandStatus();
	int temp_module = hardware.getTemperatureStatus();
	int energy_module  = hardware.getEnergyStatus();
	int solarp_module = hardware.getSolarPanelsStatus();
	int payload_module  = hardware.getPayloadStatus();
	int thermal_ctrl_module = hardware.getThermalControlStatus();


	//TODO STOPPED HERE!!! AND ADD CONSTANTS TO CONSTANT FILE AND CHANCE ALL OCCURANCES TO THE CONSTANTS

	Sample::Sample sband_sample("Module", "122");
	map<string,string> sband_measure;
	string sband_str = "";
	sband_str = int_to_string(temp,sband_str);
	sband_measure.insert(pair<string,string>("name", hardware.getSbandName()));
	sband_measure.insert(pair<string,string>("status", hardware.getSbandName()));
	sband_sample.addMeasure("Sensor1", sband_measure);
	parser.addSampleToPacket(sband_sample,"Temperature");

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


