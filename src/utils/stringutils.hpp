/*
 * stringutils.hpp
 *
 *  Created on: May 9, 2014
 *      Author: dariaz
 */

#ifndef STRINGUTILS_HPP_
#define STRINGUTILS_HPP_

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include "logics/NegevSatStates.hpp"

using namespace std;

namespace stringutils{

#define str_to_chars(str) &str[0]

string int_to_string(int number, string str);
const char* state_to_chars (int state);


}

#endif /* STRINGUTILS_HPP_ */









