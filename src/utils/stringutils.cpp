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

string state_to_string (int state){
	string state_str;
	switch (state){
	case INIT_STATE:
		state_str = "INIT_STATE";
		break;
	case STANDBY_STATE:
		state_str = "STANDBY_STATE";
		break;
	case SAFE_STATE:
		state_str = "SAFE_STATE";
		break;
	case REGULAR_OPS_STATE:
		state_str = "OPERATIONAL_STATE";
		break;
	case FACING_GROUND_STATE:
		state_str = "OPERATIONAL_STATE";
		break;
	default:
		printf("ILLEGAL STATE");
		state_str = "UNKNOWN_STATE";
	}
	return state_str;
}

}


