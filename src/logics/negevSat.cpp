//============================================================================
// Name        : negevSat.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : NegevSat Airborne system
//============================================================================

#define CONFIGURE_INIT
#define TEST_AMOUNT 20
/* configuration information */
#define CONFIGURE_INIT_TASK_INITIAL_MODES (RTEMS_PREEMPT | \
		RTEMS_TIMESLICE | \
		RTEMS_NO_ASR | \
		RTEMS_INTERRUPT_LEVEL(0))

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_MAXIMUM_PORTS				  TEST_AMOUNT
#define CONFIGURE_MAXIMUM_TASKS               TEST_AMOUNT
#define CONFIGURE_MAXIMUM_TIMERS              TEST_AMOUNT
#define CONFIGURE_MAXIMUM_SEMAPHORES          TEST_AMOUNT
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES      TEST_AMOUNT
#define CONFIGURE_MAXIMUM_PARTITIONS          TEST_AMOUNT
#define CONFIGURE_MAXIMUM_REGIONS             TEST_AMOUNT
#define CONFIGURE_MAXIMUM_PERIODS             TEST_AMOUNT
#define CONFIGURE_MAXIMUM_USER_EXTENSIONS     TEST_AMOUNT
#define CONFIGURE_TICKS_PER_TIMESLICE       100
#define CONFIGURE_MAXIMUM_POSIX_MUTEXES       TEST_AMOUNT

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_INIT_TASK_STACK_SIZE      (4 * RTEMS_MINIMUM_STACK_SIZE)
#define CONFIGURE_EXTRA_TASK_STACKS         (13 * RTEMS_MINIMUM_STACK_SIZE)

#include <rtems/confdefs.h>

/*
#include "communication/UartCommunicationHandler.hpp"
#include "communication/SendReceiveQueue.hpp"
#include "third_party/rapidxml.hpp"
#include "data_protocol/CMDParser.hpp"
#include "third_party/rapidxml_print.hpp"
#include "data_protocol/XMLValidator.hpp"
#include "data_protocol/WorkDescription.hpp"
#include "data_protocol/TLMParser.hpp"
#include "data_protocol/Sample.hpp"
#include "logics/tasks/SendTask.hpp"
#include "logics/tasks/CMDTask.hpp"
#include "logics/tasks/MPTask.hpp"
#include <stdio.h>
#include <rtems++/rtemsEvent.h>
#include "utils/stringutils.hpp"
#include "logics/Global.hpp"
#include "CommandExecutor.hpp"
*/

#include "logics/NegevSatConstants.hpp"
#include "logics/SendReceiveConf.hpp"
#include "communication/SendReceiveQueue.hpp"
#include "logics/tasks/SendTask.hpp"
#include "logics/tasks/ReceiveTask.hpp"
#include "logics/tasks/CMDTask.hpp"
#include "logics/tasks/MPTask.hpp"
#include "logics/tasks/StateMachineTask.hpp"
#include "logics/tasks/LifeCycleTask.hpp"
#include "data_protocol/WorkQueue.hpp"
#include <stdio.h>

using namespace std;

rtemsTask::rtemsTask* task_table[NUMBER_OF_TASKS];

extern "C"
{
rtems_task Init(
		rtems_task_argument argument
);
}

rtems_task Init(rtems_task_argument )
{

	// create send task
	SendReceiveQueue::SendReceiveQueue** send_queue_arr = new SendReceiveQueue::SendReceiveQueue* [SENDQ_SIZE];
	for (int i=0 ; i<SENDQ_SIZE; i++){
		send_queue_arr[i] = new SendReceiveQueue::SendReceiveQueue();
	}
	SendTask::SendTask send_task(send_queue_arr);
	send_task.create("SND ", 1, RTEMS_MINIMUM_STACK_SIZE * 2, 0, 0, 0);
	printf("%s\n", send_task.last_status_string());
	send_task.start(0xDEADDEAD);
	printf("%s\n", send_task.last_status_string());

	// create receive task
	SendReceiveQueue::SendReceiveQueue* receive_queue = new SendReceiveQueue::SendReceiveQueue();
	ReceiveTask::ReceiveTask recieve_task(receive_queue);
	recieve_task.create("RCV ", 1, RTEMS_MINIMUM_STACK_SIZE * 2, 0, 0, 0);
	printf("%s\n", recieve_task.last_status_string());
	recieve_task.start(0xDEADDEAD);
	printf("%s\n", recieve_task.last_status_string());

	// create MP task
	WorkQueue::WorkQueue* work_queue = new WorkQueue::WorkQueue();
	MPTask::MPTask mp_task(receive_queue, work_queue);
	mp_task.create("MPT ", 1, RTEMS_MINIMUM_STACK_SIZE * 2, 0, 0, 0);
	printf("%s\n", mp_task.last_status_string());
	mp_task.start(0xDEADDEAD);
	printf("%s\n", mp_task.last_status_string());

	// create CMD task
	WorkQueue::WorkQueue* rdy_work_queue = new WorkQueue::WorkQueue();
	CMDTask::CMDTask cmd_task(work_queue, rdy_work_queue);
	cmd_task.create("CMD ", 1, RTEMS_MINIMUM_STACK_SIZE * 2, 0, 0, 0);
	printf("%s\n", cmd_task.last_status_string());
	cmd_task.start(0xDEADDEAD);
	printf("%s\n", cmd_task.last_status_string());

	// create LifeCycle task
	LifeCycleTask::LifeCycleTask life_cycle_task(rdy_work_queue, send_queue_arr);
	life_cycle_task.create("LFC ", 1, RTEMS_MINIMUM_STACK_SIZE * 2, 0, 0, 0);
	printf("%s\n", life_cycle_task.last_status_string());
	life_cycle_task.start(0xDEADDEAD);
	printf("%s\n", life_cycle_task.last_status_string());

	// create StateMachine task
	StateMachineTask::StateMachineTask state_machine_task;
	state_machine_task.create("STM ", 1, RTEMS_MINIMUM_STACK_SIZE * 2, 0, 0, 0);
	printf("%s\n", state_machine_task.last_status_string());
	state_machine_task.start(0xDEADDEAD);
	printf("%s\n", state_machine_task.last_status_string());

	// create simulator task
	// TODO create it!

	task_table[SEND_TASK_INDEX] = &send_task;
	task_table[RECEIVE_TASK_INDEX] = &recieve_task;
	task_table[MP_TASK_INDEX] = &mp_task;
	task_table[CMD_TASK_INDEX] = &cmd_task;
	task_table[LIFE_CYCLE_TASK_INDEX] = &life_cycle_task;
	task_table[STATE_MACHINE_TASK_INDEX] = &state_machine_task;
	// TODO simulator
	//task_table[SIMULATOR_TASK_INDEX] = &simulator_task;

	printf("INIT - Destroy it's self\n");
	rtems_status_code status  = rtems_task_delete( RTEMS_SELF );
	printf("rtems returned with %d\n", status);
	exit(1);

	/*SendReceiveQueue::SendReceiveQueue* receive_q = new SendReceiveQueue();
	SendReceiveQueue::SendReceiveQueue* send_q = new SendReceiveQueue();

	WorkQueue::WorkQueue* work_queue = new WorkQueue();
	WorkQueue::WorkQueue* rdy_work_queue = new WorkQueue();

	MPTask::MPTask task(receive_q, work_queue);
	SendReceiveQueue::SendReceiveQueue** send;

	SendTask::SendTask sendTask(send);
	task_table[SEND_TASK_INDEX] = &sendTask;
	TLMParser::TLMParser parser;
	parser.createPacket("operational", "Static");
	printf("%s\n",&parser.getPacket("Static")->packetToString()[0]);
	//printf("%s\n",&parser.packetToString()[0]);

	Sample::Sample sample("Module", "122");
	map<string,string> measure;
	measure.insert(pair<string,string>("name", "X"));
	measure.insert(pair<string,string>("status", "OK"));
	sample.addMeasure("Info", measure);

	Sample::Sample sample2("Module", "124");
	map<string,string> measure2;
	measure2.insert(pair<string,string>("name", "Y"));
	measure2.insert(pair<string,string>("status", "CRIT"));
	sample2.addMeasure("Info", measure2);

	parser.addSampleToPacket(sample, "Static");
	parser.addSampleToPacket(sample2, "Static");
	printf("%s\n",&parser.getPacket("Static")->packetToString()[0]);

	//send.enqueue(&parser.getPacket("Static")->packetToString()[0]);

	parser.createPacket("", "Energy");
	Sample::Sample sample3("EnergySample", "144");
	map<string,string> measure3;
	int x = 2;
	int y = 3;
	char* z = int_to_chars(x,z);
	char* l = int_to_chars(y,l);
	printf("x = %s\n",z);
	printf("y = %s\n",l);
	string v = "asd";
	string c = "asd";
	v = int_to_string(x , v);
	measure3.insert(pair<string,string>("voltage", v));
	c = int_to_string(y , c);
	measure3.insert(pair<string,string>("current", c));
	sample3.addMeasure("Battery1", measure3);
	parser.addSampleToPacket(sample3, "Energy");
	printf("%s\n",&parser.getPacket("Energy")->packetToString()[0]);


	printf( "INIT - Task.create() - " );
	task.create("MPT ", 1, RTEMS_MINIMUM_STACK_SIZE * 2, 0, 0,0);
	printf("%s\n", task.last_status_string());

	printf( "INIT - Task.start() - " );
	task.start(0xDEADDEAD);
	printf("%s\n", task.last_status_string());

	printf( "INIT - SendTask.create() - " );
	sendTask.create("ST1 ", 1, RTEMS_MINIMUM_STACK_SIZE * 2, 0, 0, 0);
	printf("%s\n", sendTask.last_status_string());

	printf( "INIT - SendTask.start() - " );
	sendTask.start(0xDEADDEAD);
	printf("%s\n", sendTask.last_status_string());

	rtemsEvent send_event;
	rtems_event_set out = TEMP_SEND;
	//rtems_status_code status = send_event.send(sendTask,out);
	//printf("rtems send event returned with %d\n", status);

	CommandExecutor::CommandExecutor executor;
	WorkDescription::WorkDescription work1;
	work1.setCode(4);
	work1.setPriority(0);
	work1.setTimeStamp(111);
	executor.execute(work1);

	printf("INIT - Destroy it's self\n");
	//rtems_task_wake_after(10000);
	rtems_status_code status  = rtems_task_delete( RTEMS_SELF );
	printf("rtems returned with %d\n", status);
	exit(1);*/
}




