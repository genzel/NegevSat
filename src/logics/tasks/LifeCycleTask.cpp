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
#include "logics/SendReceiveConf.hpp"

using namespace std;
using namespace stringutils;

LifeCycleTask::LifeCycleTask(WorkQueue::WorkQueue* _rdy_works, SendReceiveQueue::SendReceiveQueue** _send_queues) {
	rdy_works = _rdy_works;
	send_queues = _send_queues;
	samples_counter = 0;
	state = INIT_STATE;
	executor.setHardawre(&hardware);
}

LifeCycleTask::~LifeCycleTask() {
	// TODO Auto-generated destructor stub
}

/**
 * Write the results of the algorithms calculation to I2C
 */
void LifeCycleTask::control_command(){
	printf(" * LifeCycle TASK:: control_command *\n");
}

/**
 * Perform algorithm - using the samples which were read in the control_unit_samples function and
 * perform computation
 */
void LifeCycleTask::control_algorithmics(){

	printf(" * LifeCycle TASK:: control_algorithmics *\n");
}

/**
 * Samples control unit - critical samples (read using I2C)
 */
void LifeCycleTask::control_unit_samples(){
	printf(" * LifeCycle TASK:: control_unit_samples *\n");
	//TODO ADD TIMER!!!!!
	//TODO REFACTOR INTO OBJECT NAMED "SAMPLER"

	if (samples_counter == 0){
		parser.createPacket("",ENERGY_STR);
		parser.createPacket("", TEMPERATURE_STR);
		parser.createPacket(state_to_chars(state),STATIC_STR);
	}
	// create energy sample
	int energy = hardware.getEnergy(true);
	int current = hardware.getEnergyCurrent(true);
	Sample::Sample energy_sample(ENERGY_SAMPLE_STR, "122");
	map<string,string> energy_measure;
	string energy_str = "";
	string current_str = "";
	energy_str = int_to_string(energy,energy_str);
	current_str = int_to_string(current,current_str);
	energy_measure.insert(pair<string,string>(VOLTAGE_STR, energy_str));
	energy_measure.insert(pair<string,string>(CURRENT_STR, current_str));
	energy_sample.addMeasure(BATTERY1_STR, energy_measure);
	parser.addSampleToPacket(energy_sample,ENERGY_STR);

	// create temperature sample
	int temp = hardware.getTemperature(true);
	Sample::Sample temp_sample(TEMPERATURE_SAMPLE_STR, "122");
	map<string,string> temp_measure;
	string temp_str = "";
	temp_str = int_to_string(temp,temp_str);
	temp_measure.insert(pair<string,string>(TEMP_STR, temp_str));
	temp_sample.addMeasure(SENSOR1_STR, temp_measure);
	parser.addSampleToPacket(temp_sample,TEMPERATURE_STR);

	// create static sample
	int sband_module  = hardware.getSbandStatus();
	int temp_module = hardware.getTemperatureStatus();
	int energy_module  = hardware.getEnergyStatus();
	int solarp_module = hardware.getSolarPanelsStatus();
	int payload_module  = hardware.getPayloadStatus();
	int thermal_ctrl_module = hardware.getThermalControlStatus();

	// sband module
	Sample::Sample sband_sample(MODULE_STR, "122");
	map<string,string> sband_measure;
	sband_measure.insert(pair<string,string>(NAME_STR, hardware.getSbandName()));
	sband_measure.insert(pair<string,string>(STATUS_STR, module_state_to_chars(sband_module)));
	sband_sample.addMeasure(INFO_STR, sband_measure);
	parser.addSampleToPacket(sband_sample,STATIC_STR);

	// temp module
	Sample::Sample temp_module_sample(MODULE_STR, "122");
	map<string,string> temp_module_measure;
	temp_module_measure.insert(pair<string,string>(NAME_STR, hardware.getTemperatureName()));
	temp_module_measure.insert(pair<string,string>(STATUS_STR, module_state_to_chars(temp_module)));
	temp_module_sample.addMeasure(INFO_STR, temp_module_measure);
	parser.addSampleToPacket(temp_module_sample,STATIC_STR);

	// energy module
	Sample::Sample energy_module_sample(MODULE_STR, "122");
	map<string,string> energy_module_measure;
	energy_module_measure.insert(pair<string,string>(NAME_STR, hardware.getEnergyName()));
	energy_module_measure.insert(pair<string,string>(STATUS_STR, module_state_to_chars(energy_module)));
	energy_module_sample.addMeasure(INFO_STR, energy_module_measure);
	parser.addSampleToPacket(energy_module_sample,STATIC_STR);

	// solarp module
	Sample::Sample solarp_sample(MODULE_STR, "122");
	map<string,string> solarp_measure;
	solarp_measure.insert(pair<string,string>(NAME_STR, hardware.getSolarPanelsName()));
	solarp_measure.insert(pair<string,string>(STATUS_STR, module_state_to_chars(solarp_module)));
	solarp_sample.addMeasure(INFO_STR, solarp_measure);
	parser.addSampleToPacket(solarp_sample,STATIC_STR);

	// payload module
	Sample::Sample payload_sample(MODULE_STR, "122");
	map<string,string> payload_measure;
	payload_measure.insert(pair<string,string>(NAME_STR, hardware.getPayloadName()));
	payload_measure.insert(pair<string,string>(STATUS_STR, module_state_to_chars(payload_module)));
	payload_sample.addMeasure(INFO_STR, payload_measure);
	parser.addSampleToPacket(payload_sample,STATIC_STR);

	// thermal_ctrl module
	Sample::Sample thermal_ctrl_sample(MODULE_STR, "122");
	map<string,string> thermal_ctrl_measure;
	thermal_ctrl_measure.insert(pair<string,string>(NAME_STR, hardware.getThermalControlName()));
	thermal_ctrl_measure.insert(pair<string,string>(STATUS_STR, module_state_to_chars(thermal_ctrl_module)));
	thermal_ctrl_sample.addMeasure(INFO_STR, thermal_ctrl_measure);
	parser.addSampleToPacket(thermal_ctrl_sample,STATIC_STR);
	// END of static sample
	samples_counter++;
	// when packets are filled with details push them into the send queues and remove them from
	// parser to prevent memory leak and keep the invariant that parser always keeps 3 packets ONLY!
	if (samples_counter == MAX_SAMPLES){
		send_queues[SENDQ_STATIC_INDEX]->enqueue(parser.getPacket(STATIC_STR)->packetToString());
		parser.removePacket(STATIC_STR);
		send_queues[SENDQ_ENERGY_INDEX]->enqueue(parser.getPacket(ENERGY_STR)->packetToString());
		parser.removePacket(ENERGY_STR);
		send_queues[SENDQ_TEMP_INDEX]->enqueue(parser.getPacket(TEMPERATURE_STR)->packetToString());
		parser.removePacket(TEMPERATURE_STR);
		samples_counter = 0;
	}
}

void LifeCycleTask::attitude_control(){
	printf(" * LifeCycle TASK:: attitude_control *\n");
	control_unit_samples();
	control_algorithmics();
	control_command();
}

void LifeCycleTask::logics(){
	printf(" * LifeCycle TASK:: logics *\n");
	// TODO Add logics when state machine is rdy
}

void LifeCycleTask::perform_cmd(){
	printf(" * LifeCycle TASK:: perform_cmd *\n");
	WorkDescription::WorkDescription work = rdy_works->dequeue();
	executor.execute(work);
}

void LifeCycleTask::monitoring(){
	printf(" * LifeCycle TASK:: monitoring *\n");
	int energy = hardware.getEnergy(false);
	int temp = hardware.getTemperature(false);

	//TODO check the condition of the samples (energy,temp and so on) and if the value is wrong
	//change something in order to invoke the right handling in the logics stage
}

void LifeCycleTask::module_ctrl(){

}

void LifeCycleTask::thermal_ctrl(){

}

void LifeCycleTask::body(rtems_task_argument argument){
	// TODO pay attention and act differently on each state using events
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


