/*
 * TLMParser.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */

#include "TLMParser.hpp"
#include "third_party/rapidxml.hpp"
#include "third_party/rapidxml_print.hpp"
#include <iostream>
#include <sstream>
#include "Sample.hpp"

using namespace std;
using namespace rapidxml;

TLMParser::TLMParser (){

}

void TLMParser::createPacket(const char* state){
	// xml declaration
	xml_node<>* dec = root.allocate_node(node_declaration);
	dec->append_attribute(root.allocate_attribute("version", "1.0"));
	dec->append_attribute(root.allocate_attribute("encoding", "utf-8"));
	root.append_node(dec);

	// packet node
	xml_node<>* first_node = root.allocate_node(node_element,"packet");
	root.append_node(first_node);

	// downstreamPacket node
	xml_node<>* downstreamPacket_node = root.allocate_node(node_element,"downstreamPacket");
	first_node->append_node(downstreamPacket_node);

	// state node
	xml_node<>* state_node = root.allocate_node(node_element,"state");
	state_node->append_attribute(root.allocate_attribute("mode", state));
	downstreamPacket_node->append_node(state_node);

	// sampling data node
	sampling_node = root.allocate_node(node_element,"samplingData");
	downstreamPacket_node->append_node(sampling_node);

	//cout << "printing xml: " << endl << root;
}

void TLMParser::addSampleToPacket(Sample::Sample& sample){
	// create sample node
	xml_node<>* sample_node = root.allocate_node(node_element,sample.getName());
	sample_node->append_attribute(root.allocate_attribute("time", sample.getTime()));
	map<const char* , map<const char*,const char*> >::iterator pos;
	map<const char* , map<const char*,const char*> >* measures = sample.getMeasures();
	for (pos = measures->begin(); pos != measures->end(); ++pos){
		xml_node<>* node = root.allocate_node(node_element,pos->first);
		map<const char* , const char*>::iterator attr_pos;
		map<const char* , const char*>* attrs = &pos->second;
		for (attr_pos = attrs->begin(); attr_pos != attrs->end(); ++attr_pos){
			node->append_attribute(root.allocate_attribute(attr_pos->first, attr_pos->second));
		}
		sample_node->append_node(node);
	}
	sampling_node->append_node(sample_node);
}

string TLMParser::packetToString(){
	string xml_as_string;
	//print(back_inserter(xml_as_string),root);
	return "sadasa";
}
