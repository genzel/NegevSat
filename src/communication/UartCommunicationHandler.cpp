/*
 * CommunicationHandler.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Genzel
 */
/* configuration information */
/*
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_MAXIMUM_TASKS             4
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "UartCommunicationHandler.hpp"

using namespace std;

UartCommunicationHandler::UartCommunicationHandler(){

}

void UartCommunicationHandler::send(char* buffer, int length){

	printf ("*** openning uart ***\n");

	int fd = open("/dev/console_b", O_RDWR /*| O_NOCTTY | _FNDELAY*/);

	printf("\nOpened COM1, fd=%d\n\n", fd);

	int numBytes = write(fd, buffer, length);

	if (numBytes < 0) {
		printf ("\nFailed to send from COM1!\n");
		//TODO: add exception handling
	}
	close(fd);
}

//TODO receive until a specific char arrived
string UartCommunicationHandler::receive(){
	int numBytes = 0;
	char buffer[BUFF_SIZE];
	printf ("*** openning uart ***\n");
	int fd = open("/dev/console_b", O_RDWR /*| O_NOCTTY | _FNDELAY*/);
	printf ("\nOpened COM1, fd=%d\n", fd);
	numBytes = read(fd,buffer,BUFF_SIZE);
	if (numBytes < 0) {
		printf ("read error!!!\n");
		close(fd);
		return "";
		// TODO exception handling
	}
	close(fd);
	string data(buffer, numBytes);
	return data;
}

bool UartCommunicationHandler::verifyBytes(string msg){
	// TODO check out to implement
	if (msg.compare("") == 0){
		return false;
	}
	return true;
}

