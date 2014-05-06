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
#include "TempPacket.hpp"

using namespace std;
using namespace rapidxml;

class TLMParser {
private:

	vector<TempPacket::TempPacket*> packets;

public:
	TLMParser ();
	~TLMParser(){}
	void createPacket(const char* state, const char* type);
	void addSampleToPacket(Sample::Sample& sample,const char* type);
	TempPacket::TempPacket* getPacket(const char* type);
	void removePacket(const char* type);
};

#endif /* TLMPARSER_HPP_ */
