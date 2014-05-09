/*
 * TempPacket.cpp
 *
 *  Created on: May 6, 2014
 *      Author: dariaz
 */

#include <data_protocol/TempPacket.hpp>
#include <sstream>
#include "third_party/rapidxml_print.hpp"

TempPacket::TempPacket(const char* _type) {
	type = _type;
}

TempPacket::~TempPacket() {
	// TODO Auto-generated destructor stub
}

string TempPacket::packetToString(){
	string xml_as_string;
	print(back_inserter(xml_as_string),root);
	return xml_as_string;
}
