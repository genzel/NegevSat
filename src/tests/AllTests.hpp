/*
 * AllTests.hpp
 *
 *  Created on: May 25, 2014
 *      Author: boris
 */

#ifndef ALLTESTS_HPP_
#define ALLTESTS_HPP_

#include <stdio.h>
#include "minunit.h"
#include "CMDParserTests.hpp"
#include "TLMParserTests.hpp"
#include "UartCommunicationHandlerTests.hpp"

#define ALL_TESTS					 	0xFFFF

#define CMD_PARSER_TESTS				0x0001
#define TLM_PARSER_TESTS				0x0002
#define COMMUNICATION_HANDLER_TESTS		0x0004
#define VALIDATOR_TESTS					0x0008
#define WORK_QUEUE_TESTS				0x0010
#define SEND_RECEIVE_TESTS				0x0020


class AllTests {
private:
	int type_tests;
	CMDParserTests::CMDParserTests cmdtests;
	TLMParserTests::TLMParserTests tlmtests;
	UartCommunicationHandlerTests::UartCommunicationHandlerTests chtests;
public:
	AllTests(int _type);
	virtual ~AllTests();
	void run_all_tests();
	char* all_tests();
};

#endif /* ALLTESTS_HPP_ */
