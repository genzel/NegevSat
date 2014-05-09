/*
 * HWModule.hpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#ifndef HWMODULE_HPP_
#define HWMODULE_HPP_

#include <string>

using namespace std;

class HWModule {

private:
	int value;
	int status;
	string name;
public:
	HWModule(string _name){
		name = _name;
	}
	virtual ~HWModule(){}
	void setValue(int _value){
		value = _value;
	}

	int getValue(){
		return value;
	}

	void setStatus(int _status) {
		status = _status;
	}

	int getStatus(){
		return status;
	}

	void setName(string _name){
		name = _name;
	}

	string getName(){
		return name;
	}
};

#endif /* HWMODULE_HPP_ */
