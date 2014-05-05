/*
 * MPTask.hpp
 *
 *  Created on: May 3, 2014
 *      Author: dariaz
 */

#ifndef MPTASK_HPP_
#define MPTASK_HPP_

#include <rtems++/rtemsEvent.h>
#include <rtems++/rtemsMessageQueue.h>
#include <rtems++/rtemsTask.h>
#include <rtems++/rtemsTaskMode.h>

class MPTask : public rtemsTask  {

	void printBlaBla(void);


protected:
	virtual void body(rtems_task_argument argument);

public:
	MPTask();
	virtual ~MPTask();
};

#endif /* MPTASK_HPP_ */
