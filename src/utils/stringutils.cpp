/*
 * stringutils.cpp
 *
 *  Created on: May 9, 2014
 *      Author: dariaz
 */

#include <utils/stringutils.hpp>
using namespace std;

namespace stringutils{

string int_to_string(int number, string str){
	stringstream out;
	out << number;
	str = out.str();
	return str;
}

char* int_to_chars(int number, char* buf){
	sprintf(buf, "%d", number);
	return buf;
}

const char* state_to_chars (int state){
	switch (state){
	case INIT_STATE:
		return INIT_STATE_STR;
	case STANDBY_STATE:
		return STANDBY_STATE_STR;
	case SAFE_STATE:
		return SAFE_STATE_STR;
	case REGULAR_OPS_STATE:
		return REGULAR_OPS_STATE_STR;
	case FACING_GROUND_STATE:
		return FACING_GROUND_STATE_STR;
	default:
		printf("ILLEGAL STATE");
		return "ILLEGAL_STATE";
	}
}

}


