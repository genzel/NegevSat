/*
 * CommunicationHandler.hpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */

#ifndef UARTCOMMUNICATIONHANDLER_HPP_
#define UARTCOMMUNICATIONHANDLER_HPP_

#include <vector>
#include <string>
#include "communication/ICommunicationHandler.hpp"

using namespace std;
#define BUFF_SIZE 256

class UartCommunicationHandler : public ICommunicationHandler {

private:
	vector<string> input;
public:
	UartCommunicationHandler ();
	~UartCommunicationHandler(){}
	void send(char* buffer, int length);
	void receive();
	bool verifyBytes();
};


#endif /* UARTCOMMUNICATIONHANDLER_HPP_ */
