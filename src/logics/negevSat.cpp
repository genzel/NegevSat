//============================================================================
// Name        : negevSat.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : NegevSat Airborne system
//============================================================================
#define CONFIGURE_MAXIMUM_SEMAPHORES    2
#include <iostream>
#include "communication/UartCommunicationHandler.hpp"
#include "third_party/rapidxml.hpp"
#include "data_protocol/CMDParser.hpp"
#include "third_party/rapidxml_print.hpp"
#include "data_protocol/XMLValidator.hpp"
#include "data_protocol/WorkDescription.hpp"
#include "data_protocol/TLMParser.hpp"
#include "data_protocol/Sample.hpp"
#include <string>
#include <vector>
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

int main() {
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
	cout << parser.packetToString() << endl;
	Sample::Sample sample("Temperature", "122");
	map<const char*,const char*> measure;
	measure.insert(pair<const char*,const char*>("voltage", "12"));
	measure.insert(pair<const char*,const char*>("current", "1"));
	sample.addMeasure("Battery1", measure);
	parser.addSampleToPacket(sample);
	cout << parser.packetToString();
	return 0;
}


