/*
 * TLMParser.hpp
 *
 *  Created on: Apr 19, 2014
 *      Author: Genzel
 */

#ifndef TLMPARSER_HPP_
#define TLMPARSER_HPP_

#include <vector>
#include "third_party/rapidxml.hpp"
#include "Sample.hpp"
#include <string>

using namespace std;
using namespace rapidxml;

class TLMParser {
private:
	xml_document<> root;
	xml_node<>* sampling_node;

public:
	TLMParser ();
	~TLMParser(){}
	void createPacket(const char* state);
	void addSampleToPacket(Sample::Sample& sample);
	string packetToString();
};

#endif /* TLMPARSER_HPP_ */
