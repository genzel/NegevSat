/*
 * TLMParserTests.cpp
 *
 *  Created on: May 6, 2014
 *      Author: dariaz
 */

#include <tests/TLMParserTests.hpp>
#include "utils/stringutils.hpp"
#include "logics/NegevSatConstants.hpp"
#include <stdio.h>
#include <string>

using namespace stringutils;

TLMParserTests::TLMParserTests() {
	// TODO Auto-generated constructor stub

}

TLMParserTests::~TLMParserTests() {
	// TODO Auto-generated destructor stub
}

char* TLMParserTests::runTests(){
	int state = REGULAR_OPS_STATE;
	int time = 10;
	sampler.setHardware(&hardware);

	hardware.setEnergy(100);
	hardware.setEnergyCurrent(3);
	hardware.setTemperature(40);
	hardware.setPayloadStatus(MODULE_ON);
	hardware.setSbandStatus(MODULE_STANDBY);

	parser.createPacket("",ENERGY_STR);
	parser.createPacket("", TEMPERATURE_STR);
	parser.createPacket(state_to_chars(state),STATIC_STR);
	printf("%s\n",&parser.getPacket(STATIC_STR)->packetToString()[0]);

	Sample::Sample energy_sample = sampler.createSample(ENERGY_STR, true, time, HW_ENERGY_MODULE);
	parser.addSampleToPacket(energy_sample,ENERGY_STR);

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

	string static_packet = parser.getPacket(STATIC_STR)->packetToString();
	string energy_packet = parser.getPacket(ENERGY_STR)->packetToString();
	string temp_packet = parser.getPacket(TEMPERATURE_STR)->packetToString();

	printf("static packet:\n %s\n", &static_packet[0]);
	printf("energy packet:\n %s\n", &energy_packet[0]);
	printf("temp packet:\n %s\n", &temp_packet[0]);

	// TODO FIX parser/sampler and add asserts to make the test fail

	return 0;
}

