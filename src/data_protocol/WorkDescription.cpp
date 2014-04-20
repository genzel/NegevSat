/*
 * WorkDescription.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */

using namespace std;

#include "WorkDescription.hpp"

WorkDescription::WorkDescription(){

}

void WorkDescription::setCode(int _code){
	code = _code;
}

int WorkDescription::getCode(){
	return code;
}

void WorkDescription::setPriority(int _priority){
	priority = _priority;
}

int WorkDescription::getPriority(){
	return priority;
}

void WorkDescription::setTimeStamp(int _timestamp){
	timestamp = _timestamp;
}

int WorkDescription::getTimestamp(){
	return timestamp;
}
