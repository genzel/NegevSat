/*
 * UartCommunicationHandlerTests.cpp
 *
 *  Created on: May 6, 2014
 *      Author: dariaz
 */

#include <tests/UartCommunicationHandlerTests.hpp>

UartCommunicationHandlerTests::UartCommunicationHandlerTests() {
	// TODO Auto-generated constructor stub

}

UartCommunicationHandlerTests::~UartCommunicationHandlerTests() {
	// TODO Auto-generated destructor stub
}

void UartCommunicationHandlerTests::runTests(){
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
}
