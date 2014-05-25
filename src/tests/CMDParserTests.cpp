/*
 * CMDParserTests.cpp
 *
 *  Created on: May 25, 2014
 *      Author: boris
 */

#include <tests/CMDParserTests.hpp>
#include "communication/SendReceiveQueue.hpp"
#include "minunit.h"
#include "data_protocol/ValidatorFactory.hpp"
#include "data_protocol/WorkDescription.hpp"
#include <vector>

CMDParserTests::CMDParserTests() {
	ValidatorFactory::ValidatorFactory factory;
	validator = factory.createValidator("XML");
}

CMDParserTests::~CMDParserTests() {
	// TODO Auto-generated destructor stub
}

char* assert_mission_is_correct(WorkDescription::WorkDescription* work, int code, int priority, int time){
	mu_assert("error", work->getCode() == code);
	mu_assert("error", work->getPriority() == priority);
	mu_assert("error", work->getTimestamp() == time);
	return 0;
}

char* CMDParserTests::runTests(){
	SendReceiveQueue::SendReceiveQueue* receive_queue = new SendReceiveQueue::SendReceiveQueue();
	char missions[] = "<?xml version='1.0'?>"
			"<packet>"
			"<upstreamPacket time='12332'>"
			"<mission opcode='5' priority='3' time='12334'/>"
			"<mission opcode='4' priority='2' time='12335'/>"
			"<mission opcode='2' priority='1' time='12336'/>"
			"</upstreamPacket>"
			"</packet>";
	int numBytes = 261;
	string data(missions, numBytes);
	receive_queue->enqueue(data);
	string packet = receive_queue->dequeue();
	validator->buildPacket(packet);
	vector<WorkDescription::WorkDescription> parsed_works;
	if (validator->validate()){
		parsed_works = parser.parsePacket(validator->getRoot());
	}
	mu_assert("error, length should be 3", parsed_works.size() == 3);
	WorkDescription::WorkDescription work1 = parsed_works.at(0);
	WorkDescription::WorkDescription work2 = parsed_works.at(1);
	WorkDescription::WorkDescription work3 = parsed_works.at(2);

	if (assert_mission_is_correct(&work1, 5, 3, 12334) != 0){
		return fail_assert;
	}
	if (assert_mission_is_correct(&work2, 4, 2, 12335) != 0){
		return fail_assert;
	}
	if (assert_mission_is_correct(&work3, 2, 1, 12336) != 0){
		return fail_assert;
	}
	return 0;
}



