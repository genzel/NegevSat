/*
 * TempPacket.hpp
 *
 *  Created on: May 6, 2014
 *      Author: dariaz
 */

#ifndef TEMPPACKET_HPP_
#define TEMPPACKET_HPP_

#include "third_party/rapidxml.hpp"
#include <string>

using namespace std;
using namespace rapidxml;

class TempPacket {

private:

	const char* type;
	xml_document<> root;
	xml_node<>* sampling_node;

public:
	TempPacket(const char* _type);

	xml_document<>* getRoot(){
		return &root;
	}

	void setSamplingNode(xml_node<>* node){
		sampling_node = node;
	}

	const char* getType(){
		return type;
	}

	xml_node<>* getSamplingNode(){
		return sampling_node;
	}

	string packetToString();

	virtual ~TempPacket();
};

#endif /* TEMPPACKET_HPP_ */
