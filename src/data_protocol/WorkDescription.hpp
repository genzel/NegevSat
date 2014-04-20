/*
 * WorkDescription.hpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Genzel
 */

#ifndef WORKDESCRIPTION_HPP_
#define WORKDESCRIPTION_HPP_

class WorkDescription {
private:
	int code;
	int priority;
	//TODO: check which data structure should we store the timestamp
	int timestamp;
	//TODO: add work params

public:
	WorkDescription ();
	~WorkDescription(){}
	void setCode(int _code);
	int getCode();
	void setPriority(int _priority);
	int getPriority();
	void setTimeStamp(int _timestamp);
	int getTimestamp();
};


#endif /* WORKDESCRIPTION_HPP_ */
