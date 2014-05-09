/*
 * LifeCycleTask.hpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#ifndef LIFECYCLETASK_HPP_
#define LIFECYCLETASK_HPP_

#include <rtems++/rtemsTask.h>
#include "data_protocol/WorkDescription.hpp"
#include "data_protocol/WorkQueue.hpp"
#include "communication/SendReceiveQueue.hpp"
#include "data_protocol/TLMParser.hpp"
#include "hardware/HardwareState.hpp"
#include "data_protocol/Sample.hpp"
#include <string>
#include <vector>

#define MAX_SAMPLES 	10

using namespace std;

class LifeCycleTask : public rtemsTask {

private:
	WorkQueue::WorkQueue* rdy_works;
	SendReceiveQueue::SendReceiveQueue** send_queues;
	TLMParser::TLMParser parser;
	HardwareState::HardwareState hardware;
	int samples_counter;
	int state;

protected:
	virtual void body(rtems_task_argument argument);

public:
	LifeCycleTask(WorkQueue::WorkQueue* _rdy_works, SendReceiveQueue::SendReceiveQueue** _send_queues);
	virtual ~LifeCycleTask();
	void control_unit_samples();
	void attitude_control();
	void logics();
	void perform_cmd();
	void monitoring();
	void module_ctrl();
	void thermal_ctrl();
};

#endif /* LIFECYCLETASK_HPP_ */