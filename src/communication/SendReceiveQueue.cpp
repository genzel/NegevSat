/*
 * SendReceiveQueue.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: Genzel
 */

#include "SendReceiveQueue.hpp"
#include <assert.h>

using namespace std;

SendReceiveQueue::SendReceiveQueue(){
	rtems_status_code status;
	// create semaphore with 1 permit
	status = rtems_semaphore_create(
			rtems_build_name( 'S', 'R', 'Q', '1' ),
			1,
			RTEMS_DEFAULT_ATTRIBUTES,
			0,
			&mutex_id
	);

	assert( status == RTEMS_SUCCESSFUL );
	status = rtems_semaphore_create(
				rtems_build_name( 'S', 'R', 'Q', '2' ),
				0,  /* created locked */
				RTEMS_DEFAULT_ATTRIBUTES,
				0,
				&produced_count_id
		);
	assert( status == RTEMS_SUCCESSFUL );
}

void SendReceiveQueue::enqueue(string message){
	rtems_status_code status;
	/* Semaphore not available, ensured to block */
	status = rtems_semaphore_obtain(
			mutex_id,
			RTEMS_DEFAULT_OPTIONS,
			RTEMS_NO_TIMEOUT
	);
	pending_messages.push(message);
	status = rtems_semaphore_release( produced_count_id );
	status = rtems_semaphore_release( mutex_id );
}

string SendReceiveQueue::dequeue(){
	rtems_status_code status;
	status = rtems_semaphore_obtain(
				produced_count_id,
				RTEMS_DEFAULT_OPTIONS,
				RTEMS_NO_TIMEOUT
	);

	status = rtems_semaphore_obtain(
			mutex_id,
			RTEMS_DEFAULT_OPTIONS,
			RTEMS_NO_TIMEOUT
	);
	string message = pending_messages.front();
	pending_messages.pop();
	status = rtems_semaphore_release( mutex_id );
	return message;
}
