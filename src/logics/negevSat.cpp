//============================================================================
// Name        : negevSat.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#define CONFIGURE_MAXIMUM_SEMAPHORES    2
#include <iostream>
#include "communication/UartCommunicationHandler.hpp"
using namespace std;

int main() {
	UartCommunicationHandler::UartCommunicationHandler uart; // concrete implementation - should be changed to needed handler
	ICommunicationHandler::ICommunicationHandler*  ch =  &uart;
	ch->receive();
	return 0;
}
