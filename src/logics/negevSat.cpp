//============================================================================
// Name        : negevSat.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : NegevSat Airborne system
//============================================================================





/*
#define CONFIGURE_EXECUTIVE_RAM_SIZE        (512*1024)
#define CONFIGURE_MAXIMUM_SEMAPHORES        20
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES    20


#define CONFIGURE_MICROSECONDS_PER_TICK    10000
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 50
#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM

#define CONFIGURE_INIT_TASK_STACK_SIZE    (10*1024)
#define CONFIGURE_INIT_TASK_PRIORITY    50
#define CONFIGURE_INIT_TASK_INITIAL_MODES (RTEMS_PREEMPT | \
                                           RTEMS_NO_TIMESLICE | \
                                           RTEMS_NO_ASR | \
                                           RTEMS_INTERRUPT_LEVEL(0))
*/

/*
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_MAXIMUM_TASKS            20
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_EXTRA_TASK_STACKS 		(3* RTEMS_MINIMUM_STACK_SIZE)
*/
#define CONFIGURE_INIT

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS               8
#define CONFIGURE_MAXIMUM_TIMERS              1
#define CONFIGURE_MAXIMUM_SEMAPHORES          8
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES      1
#define CONFIGURE_MAXIMUM_PARTITIONS          1
#define CONFIGURE_MAXIMUM_REGIONS             1
#define CONFIGURE_MAXIMUM_PERIODS             1
#define CONFIGURE_MAXIMUM_USER_EXTENSIONS     0
#define CONFIGURE_TICKS_PER_TIMESLICE       100
#define CONFIGURE_MAXIMUM_POSIX_MUTEXES       8

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_INIT_TASK_STACK_SIZE      (4 * RTEMS_MINIMUM_STACK_SIZE)

#define CONFIGURE_EXTRA_TASK_STACKS         (13 * RTEMS_MINIMUM_STACK_SIZE)

#include <rtems/confdefs.h>

#include <tmacros.h>
#include <iostream>
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



using namespace std;
using namespace rapidxml;

/*void traverse_xml(const std::string& xml)
{
	xml_document<> doc;
	vector<char> xml_copy(xml.begin(), xml.end());
	xml_copy.push_back('\0');
	doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);
	cout << doc;
	CMDParser::CMDParser parser;
	parser.parsePacket(&doc);
}*/

extern "C"
{
  rtems_task Init(
    rtems_task_argument argument
    );
}

//int main() {
rtems_task Init(rtems_task_argument )
{
	/*UartCommunicationHandler::UartCommunicationHandler uart; // concrete implementation - should be changed to needed handler
	ICommunicationHandler::ICommunicationHandler*  ch =  &uart;
	ch->receive();*/

	/*char xml[] = "<?xml version='1.0'?>"
	"<packet>"
		"<upstreamPacket time='12332'>"
			"<mission opcode='5' priority='3'/>"
			"<mission opcode='4' priority='2'/>"
			"<mission opcode='2' priority='1'/>"
		"</upstreamPacket>"
	"</packet>";
	XMLValidator::XMLValidator validator;
	validator.buildPacket(xml);
	CMDParser::CMDParser parser;
	vector<WorkDescription::WorkDescription> works = parser.parsePacket(validator.getRoot());*/
	//traverse_xml(xml);
	TLMParser::TLMParser parser;
	parser.createPacket("operational");
	//cout << parser.packetToString() << endl;
	Sample::Sample sample("Temperature", "122");
	map<const char*,const char*> measure;
	measure.insert(pair<const char*,const char*>("voltage", "12"));
	measure.insert(pair<const char*,const char*>("current", "1"));
	sample.addMeasure("Battery1", measure);
	parser.addSampleToPacket(sample);
	//cout << parser.packetToString();

	SendReceiveQueue::SendReceiveQueue send;
	send.enqueue(parser.packetToString());
	SendTask::SendTask sendTask(&send);
	printf("create\n");
	sendTask.create("TA1 ", 0, RTEMS_MINIMUM_STACK_SIZE);
	sendTask.restart(0);
	printf("start\n");
	sendTask.start(0xDEADDEAD);

	//return 0;
}




