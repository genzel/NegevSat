/*
 * CommandExecutor.cpp
 *
 *  Created on: May 10, 2014
 *      Author: dariaz
 */

#include <logics/CommandExecutor.hpp>
#include <stdio.h>
#include <rtems++/rtemsEvent.h>
#include "logics/tasks/SendTask.hpp"


CommandExecutor::CommandExecutor() {
}

CommandExecutor::~CommandExecutor() {
	// TODO Auto-generated destructor stub
}

void CommandExecutor::setHardawre(HardwareState::HardwareState* _hardware){
	hardware = _hardware;
}

void CommandExecutor::execute(WorkDescription::WorkDescription work){
	if (hardware == 0){
		printf (" * LifeCycle TASK::CommandExecutor:please set the hardware! exiting... *\n");
		return;
	}
	int opcode = work.getCode();
	rtemsEvent send_event;
	rtems_event_set out;
	rtems_status_code status;
	switch (opcode){
	case MOVE_TO_SAFE:
		//TODO move to safe!
		printf(" * LifeCycle TASK::CommandExecutor: moving to safe mode! *\n");
		break;
	case MOVE_TO_STANDBY:
		//TODO move to standby!
		printf(" * LifeCycle TASK::CommandExecutor: moving to standby mode! *\n");
		break;
	case MOVE_TO_OP:
		//TODO move to operational!
		printf(" * LifeCycle TASK::CommandExecutor: moving to operational mode! *\n");
		break;
	case FORMAT_ENERGY:
		printf(" * LifeCycle TASK::CommandExecutor: changing format to ENERGY! *\n");
		out = ENERGY_SEND;
		status = send_event.send(*(task_table[SEND_TASK_INDEX]),out);
		printf(" * LifeCycle TASK::CommandExecutor:  send event returned with %d *\n", status);
		break;
	case FORMAT_TEMP:
		printf(" * LifeCycle TASK::CommandExecutor: changing format to Temperature! *\n");
		out = TEMP_SEND;
		status = send_event.send(*(task_table[SEND_TASK_INDEX]),out);
		printf(" * LifeCycle TASK::CommandExecutor:  send event returned with %d *\n", status);
		break;
	case FORMAT_STATIC:
		printf(" * LifeCycle TASK::CommandExecutor: changing format to Static! *\n");
		out = STATIC_SEND;
		status = send_event.send(*(task_table[SEND_TASK_INDEX]),out);
		printf(" * LifeCycle TASK::CommandExecutor:  send event returned with %d *\n", status);
		break;
	case FORMAT_MIXED:
		printf(" * LifeCycle TASK::CommandExecutor: changing format to Mixed! *\n");
		out = MIXED_SEND;
		status = send_event.send(*(task_table[SEND_TASK_INDEX]),out);
		printf(" * LifeCycle TASK::CommandExecutor:  send event returned with %d *\n", status);
		break;
	case SBAND_ON:
		printf(" * LifeCycle TASK::CommandExecutor: turning SBAND on! *\n");
		hardware->setSbandStatus(MODULE_OK);
		break;
	case SBAND_OFF:
		printf(" * LifeCycle TASK::CommandExecutor: turning SBAND off! *\n");
		hardware->setSbandStatus(MODULE_OFF);
		break;
	case PAYLOAD_ON:
		printf(" * LifeCycle TASK::CommandExecutor: turning PAYLOAD on! *\n");
		hardware->setPayloadStatus(MODULE_OK);
		break;
	case PAYLOAD_OFF:
		printf(" * LifeCycle TASK::CommandExecutor: turning PAYLOAD off! *\n");
		hardware->setPayloadStatus(MODULE_OFF);
		break;
	case THERMAL_CTRL_ON:
		printf(" * LifeCycle TASK::CommandExecutor: turning THERMAL_CTRL on! *\n");
		hardware->setThermalControlStatus(MODULE_OK);
		break;
	case THERMAL_CTRL_OFF:
		printf(" * LifeCycle TASK::CommandExecutor: turning THERMAL_CTRL off! *\n");
		hardware->setThermalControlStatus(MODULE_OFF);
		break;
	default:
		printf(" * LifeCycle TASK::CommandExecutor: Illegal command in work! *\n");
	}
}
