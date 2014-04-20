/*
 * Sample.hpp
 *
 *  Created on: Apr 19, 2014
 *      Author: Genzel
 */

#ifndef SAMPLE_HPP_
#define SAMPLE_HPP_

#include <string>
#include <map>

using namespace std;

class Sample {
private:
	const char* name;
	const char* time;
	map<const char*,map<const char*,const char*> > measures;

public:
	Sample(const char* _name, const char* time);
	~Sample(){}
	void addMeasure(const char* name, map<const char*,const char*> values);
	const char* getName();
	const char* getTime();
	map<const char*,map<const char*,const char*> >* getMeasures();

};


#endif /* SAMPLE_HPP_ */
