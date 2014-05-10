/*
 * Sample.cpp
 *
 *  Created on: Apr 19, 2014
 *      Author: Genzel
 */

#include "Sample.hpp"


using namespace std;

Sample::Sample(string _name, string _time){
	name = _name;
	time = _time;
}

/*usage example:
 	Sample::Sample sample("Temperature", "122");
	map<string,string> measure;
	measure.insert(pair<string,string>("voltage", "12"));
	measure.insert(pair<string,string>("current", "1"));
	sample.addMeasure("Battery1", measure);*/

void Sample::addMeasure(string name, map<string,string> values){
	measures.insert(pair<string,map<string,string> >(name,values));
}

string Sample::getName(){
	return name;
}

string Sample::getTime(){
	return time;
}

map<string,map<string,string> >* Sample::getMeasures(){
	return &measures;
}
