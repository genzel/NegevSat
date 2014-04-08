/*
 * ICommunicationHandler.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: Genzel
 */

class ICommunicationHandler
{
public:
  virtual void send(char* buffer, int length) = 0;
  virtual void receive() = 0;
  virtual bool verifyBytes() = 0;
  virtual ~ICommunicationHandler() { }
};
