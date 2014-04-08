/*
 * CommunicationHandler.hpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */

#ifndef UARTCOMMUNICATIONHANDLER_HPP_
#define UARTCOMMUNICATIONHANDLER_HPP_
using namespace std;
#include <vector>
#include <string>

#define BUFF_SIZE 256
#include "communication/ICommunicationHandler.hpp"
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
