/*
 * Sample.cpp
 *
 *  Created on: Apr 19, 2014
 *      Author: Genzel
 */

#include "Sample.hpp"


using namespace std;

Sample::Sample(const char* _name, const char* _time){
	name = _name;
	time = _time;
}

/*usage example:
 	Sample::Sample sample("Temperature", "122");
	map<const char*,const char*> measure;
	measure.insert(pair<const char*,const char*>("voltage", "12"));
	measure.insert(pair<const char*,const char*>("current", "1"));
	sample.addMeasure("Battery1", measure);*/

void Sample::addMeasure(const char* name, map<const char*,const char*> values){
	measures.insert(pair<const char*,map<const char*,const char*> >(name,values));
}

const char* Sample::getName(){
	return name;
}

const char* Sample::getTime(){
	return time;
}

map<const char*,map<const char*,const char*> >* Sample::getMeasures(){
	return &measures;
}
