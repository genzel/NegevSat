/*
 * ICommunicationHandler.hpp
 *
 *  Created on: Apr 8, 2014
 *      Author: Genzel
 */

#ifndef ICOMMUNICATIONHANDLER_HPP_
#define ICOMMUNICATIONHANDLER_HPP_

class ICommunicationHandler
{
public:
  virtual void send(char* buffer, int length) = 0;
  virtual void receive() = 0;
  virtual bool verifyBytes() = 0;
  virtual ~ICommunicationHandler() { }
};

#endif /* ICOMMUNICATIONHANDLER_HPP_ */
