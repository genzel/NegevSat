/*
 * CommunicationHandler.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */
/* configuration information */
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_MAXIMUM_TASKS             4
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "UartCommunicationHandler.hpp"

using namespace std;

UartCommunicationHandler::UartCommunicationHandler(){

}

void UartCommunicationHandler::send(char* buffer, int length){

	cout << "*** openning uart ***\n";

	int fd = open("/dev/console_b", O_RDWR | O_NOCTTY | _FNDELAY);

	printf("\nOpened COM1, fd=%d\n\n", fd);

	int numBytes = write(fd, buffer, length);

	if (numBytes < 0) {
		cout << "\nFailed to send from COM1!\n";
		//TODO: add exception handling
	}
	close(fd);
}

//TODO receive until a specific char arrived
void UartCommunicationHandler::receive(){
	int numBytes = 0;
	char buffer[BUFF_SIZE];
	cout << "*** openning uart ***\n";
	int fd = open("/dev/console_b", O_RDWR | O_NOCTTY | _FNDELAY);
	cout << "\nOpened COM1, fd=" << fd << "\n\n";
	numBytes = read(fd,buffer,BUFF_SIZE);
	if (numBytes < 0) {
		cout << "read error!!!";
		// TODO exception handling
	}
	close(fd);
	cout << buffer;
	string data(buffer, numBytes);
	cout << "pushing to input this data: " << data;
	input.push_back(data);
}

bool UartCommunicationHandler::verifyBytes(){
	return true;
}

