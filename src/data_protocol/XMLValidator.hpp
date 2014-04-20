/*
 * XMLValidator.hpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Genzel
 */

#ifndef XMLVALIDATOR_HPP_
#define XMLVALIDATOR_HPP_

#include "data_protocol/IValidator.hpp"
#include "third_party/rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class XMLValidator : public IValidator {
private:
	xml_document<> root;
public:
	XMLValidator ();
	~XMLValidator(){}
	void buildPacket(const string& packet);
	bool validate();
	xml_document<>* getRoot();
};

#endif /* XMLVALIDATOR_HPP_ */
