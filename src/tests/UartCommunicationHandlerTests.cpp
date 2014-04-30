// communicationHandler Unit Tests

#define CONFIGURE_MAXIMUM_SEMAPHORES    2

#include <iostream>
#include <string>

/*int uartCommunicationHandlerSendTest() {
	
	UartCommunicationHandler::UartCommunicationHandler uart; // concrete implementation - should be changed to needed handler
	ICommunicationHandler::ICommunicationHandler*  ch =  &uart;
	char buffer[3];
	buffer[0] = 'b';
	buffer[1] = 'a';
	buffer[2] = '\0';
	
	ch->send(buffer, 3);
	
	return 0;
}

int uartCommunicationHandlerReceiveTest() {
	
	UartCommunicationHandler::UartCommunicationHandler uart; // concrete implementation - should be changed to needed handler
	ICommunicationHandler::ICommunicationHandler*  ch =  &uart;
	char buffer[256];
	string receivedString;
	
	ch->receive();
	
	receivedString = getInput();
	cout << "received data is : " << receivedString << "\n";
	
	return 0;
}*/
