/*
 * TLMParserTests.hpp
 *
 *  Created on: May 6, 2014
 *      Author: dariaz
 */

#ifndef TLMPARSERTESTS_HPP_
#define TLMPARSERTESTS_HPP_

#include "data_protocol/TLMParser.hpp"
#include "minunit.h"
#include "logics/Sampler.hpp"
#include "hardware/HardwareState.hpp"

class TLMParserTests {
private:
	TLMParser::TLMParser parser;
	Sampler::Sampler sampler;
	HardwareState::HardwareState hardware;
public:
	TLMParserTests();
	virtual ~TLMParserTests();
	char* runTests();
};

#endif /* TLMPARSERTESTS_HPP_ */
