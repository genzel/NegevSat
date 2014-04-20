/*
 * IValidator.hpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Genzel
 */

#ifndef IVALIDATOR_HPP_
#define IVALIDATOR_HPP_

#include <string>

using namespace std;

class IValidator
{
public:
  virtual void buildPacket(const string& packet) = 0;
  virtual bool validate() = 0;
};

#endif /* IVALIDATOR_HPP_ */
