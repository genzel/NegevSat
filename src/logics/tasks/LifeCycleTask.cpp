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
	sampler.setHardware(&hardware);
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
	if (samples_counter == 0){
		parser.createPacket("",ENERGY_STR);
		parser.createPacket("", TEMPERATURE_STR);
		parser.createPacket(state_to_chars(state),STATIC_STR);
	}
	int time = 10;
	// create energy sample
	Sample::Sample energy_sample = sampler.createSample(ENERGY_STR, true, time, HW_ENERGY_MODULE);
	parser.addSampleToPacket(energy_sample,ENERGY_STR);
	// create temperature sample
	Sample::Sample temp_sample = sampler.createSample(TEMPERATURE_STR, true, time, HW_TEMP_MODULE);
	parser.addSampleToPacket(temp_sample,TEMPERATURE_STR);

	// create static samples
	Sample::Sample static_sband_sample = sampler.createSample(STATIC_STR, true, time, HW_SBAND_MODULE);
	parser.addSampleToPacket(static_sband_sample,STATIC_STR);
	Sample::Sample static_temp_sample = sampler.createSample(STATIC_STR, true, time, HW_TEMP_MODULE);
	parser.addSampleToPacket(static_temp_sample,STATIC_STR);
	Sample::Sample static_energy_sample = sampler.createSample(STATIC_STR, true, time, HW_ENERGY_MODULE);
	parser.addSampleToPacket(static_energy_sample,STATIC_STR);
	Sample::Sample static_solarp_sample = sampler.createSample(STATIC_STR, true, time, HW_SOLARP_MODULE);
	parser.addSampleToPacket(static_solarp_sample,STATIC_STR);
	Sample::Sample static_payload_sample = sampler.createSample(STATIC_STR, true, time, HW_PAYLOAD_MODULE);
	parser.addSampleToPacket(static_payload_sample,STATIC_STR);
	Sample::Sample static_thermal_ctrl_sample = sampler.createSample(STATIC_STR, true, time, HW_TERMAL_CTRL_MODULE);
	parser.addSampleToPacket(static_thermal_ctrl_sample,STATIC_STR);

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
	int voltage = hardware.getEnergy(false);
	int current = hardware.getEnergyCurrent(false);
	int temp = hardware.getTemperature(false);

	//TODO check the condition of the samples (energy,temp and so on) and if the value is wrong
	//change something in order to invoke the right handling in the logics stage
	if (voltage < MIN_PROPER_VOLTAGE || current < MIN_PROPER_CURRENT){
		hardware.setEnergyStatus(MODULE_MALFUNCTION);
	}
	if (temp < MIN_PROPER_TEMPERATURE || temp > MAX_PROPER_TEMPERATURE){
		hardware.setTemperatureStatus(MODULE_MALFUNCTION);
	}
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


