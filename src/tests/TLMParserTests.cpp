/*
 * TLMParserTests.cpp
 *
 *  Created on: May 6, 2014
 *      Author: dariaz
 */

#include <tests/TLMParserTests.hpp>

TLMParserTests::TLMParserTests() {
	// TODO Auto-generated constructor stub

}

TLMParserTests::~TLMParserTests() {
	// TODO Auto-generated destructor stub
}

char* TLMParserTests::runTests(){
	/*MPTask::MPTask task;
	SendReceiveQueue::SendReceiveQueue send;
	SendTask::SendTask sendTask(&send);

	TLMParser::TLMParser parser;
	parser.createPacket("operational", "Static");
	printf("%s\n",&parser.getPacket("Static")->packetToString()[0]);
	//printf("%s\n",&parser.packetToString()[0]);

	Sample::Sample sample("Module", "122");
	map<const char*,const char*> measure;
	measure.insert(pair<const char*,const char*>("name", "X"));
	measure.insert(pair<const char*,const char*>("status", "OK"));
	sample.addMeasure("Info", measure);

	Sample::Sample sample2("Module", "124");
	map<const char*,const char*> measure2;
	measure2.insert(pair<const char*,const char*>("name", "Y"));
	measure2.insert(pair<const char*,const char*>("status", "CRIT"));
	sample2.addMeasure("Info", measure2);

	parser.addSampleToPacket(sample, "Static");
	parser.addSampleToPacket(sample2, "Static");
	printf("%s\n",&parser.getPacket("Static")->packetToString()[0]);

	send.enqueue(&parser.getPacket("Static")->packetToString()[0]);

	parser.createPacket("", "Energy");
	Sample::Sample sample3("EnergySample", "144");
	map<const char*,const char*> measure3;
	measure3.insert(pair<const char*,const char*>("voltage", "2"));
	measure3.insert(pair<const char*,const char*>("current", "3"));
	sample3.addMeasure("Battery1", measure3);
	parser.addSampleToPacket(sample3, "Energy");
	printf("%s\n",&parser.getPacket("Energy")->packetToString()[0]);*/
}

