/*
 * Validator.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */

#include "data_protocol/IValidator.hpp"
#include "third_party/rapidxml.hpp"
#include "third_party/rapidxml_print.hpp"
#include "XMLValidator.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace rapidxml;

XMLValidator::XMLValidator() {

}

void XMLValidator::buildPacket(const string& packet){
	vector<char> xml_copy(packet.begin(), packet.end());
	xml_copy.push_back('\0');
	root.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);
	cout << root << endl;
}

bool XMLValidator::validate(){
	//TODO find out how ?!?!
	return true;
}

xml_document<>* XMLValidator::getRoot(){
	return &root;
}
