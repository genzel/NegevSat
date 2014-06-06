/*
 * StateMachineTask.cpp
 *
 *  Created on: May 20, 2014
 *      Author: boris
 */

#include <logics/tasks/StateMachineTask.hpp>
#include "Macho.hpp"
#include <stdio.h>
#include "logics/NegevSatConstants.hpp"
#include <rtems++/rtemsEvent.h>
#include "logics/Global.hpp"
#include <stdlib.h>

// Basic state machine of the satellite
namespace Satellite {

//////////////////////////////////////////////////////////////////////
// State declarations

// Machine's top state
TOPSTATE(Top) {

	// Top state data (visible to all substates)
	struct Box {
		Box() : state(INIT_STATE), counter(0) {}

		void send_event(int type, int index) {
			rtems_event_set out;
			out = type;
			rtems_status_code status = event.send(*(task_table[index]),out);
			printf(" * StateMachine TASK:: send event returned with %d *\n", status);
		}

		rtems_event_set receive_event(){
			rtems_event_set out;
			// TODO consider adding timeout to wait for receive
			rtems_status_code status = event.receive(RTEMS_ALL_EVENTS , out, 0, rtemsEvent::no_wait, rtemsEvent::any);
			if (status != RTEMS_SUCCESSFUL){
				return NO_EVENT_RECEIVED;
			}
			return out;
		}

	private:
		int state;
		int counter;
		rtemsEvent event;
	};

	STATE(Top)

	// Machine's event protocol
	virtual void work() {}		// Do operations

private:
	// Initial init action
	void init();
};

// Satellite's initialize state
SUBSTATE(InitState, Top) {
	STATE(InitState)
																								void work();
private:
	void init();
};


// Satellite is ready to work
SUBSTATE(Operational, Top) {
	STATE(Operational)

																										void work();
private:
	void init();
};

// Satellite is facing the ground station
SUBSTATE(FacingGroundStation, Operational) {
	STATE(FacingGroundStation)

																																	void work();

private:
	void init();
};

// Satellite is facing the ground station
SUBSTATE(RegularOperations, Operational) {
	STATE(RegularOperations)

																																			void work();

private:
	void init();
};

// Satellite is in safe mode
SUBSTATE(Safe, Top) {
	STATE(Safe)

																																			void work();

private:
	void init();
};

// Satellite is in standby mode
SUBSTATE(Standby, Top) {
	STATE(Standby)

																																			void work();

private:
	void init();
};

//////////////////////////////////////////////////////////////////////
// Event handler and box implementations

// Top state
void Top::init() {
	//printf(" * StateMachine TASK:: TopState::init *\n");
	setState<InitState>();
}

// InitState state
void InitState::init() {
	printf(" * StateMachine TASK:: Entering Init State *\n");
}

void InitState::work() {
	//printf(" * StateMachine TASK:: InitState::work *\n");
	setState<Operational>();
}
// State Operational
void Operational::init() {
	printf(" * StateMachine TASK:: Entering Operational State *\n");

}
void Operational::work(){
	//printf(" * StateMachine TASK:: Operational::work *\n");
	setState<RegularOperations>();
}

// State RegularOperations
void RegularOperations::init() {
	printf(" * StateMachine TASK:: Entering RegularOperations State *\n");
	int i;
	for (i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(REGULAR_OPS_STATE_EVENT, i);
	}
}

void RegularOperations::work() {
	//printf(" * StateMachine TASK:: RegularOperations::work *\n");
	rtems_task_wake_after(
			2 * 5 * rtems_clock_get_ticks_per_second());
	rtems_event_set set = TOP::box().receive_event();
	//printf(" * StateMachine TASK:: set received: %d *\n", (int)set);
	if (set != NO_EVENT_RECEIVED){
		if (set & MOVE_TO_SAFE_EVENT){
			setState<Safe>();
		}
		else if (set & RECEIVED_COMMUNICATION_EVENT){
			setState<FacingGroundStation>();
		}
		else if (set & MOVE_TO_STANDBY_EVENT){
			setState<Standby>();
		}
	}

	/*switch (set){
	case MOVE_TO_SAFE_EVENT:
		setState<Safe>();
		break;
	case MOVE_TO_STANDBY_EVENT:
		setState<Standby>();
		break;
	case RECEIVED_COMMUNICATION_EVENT:
		setState<FacingGroundStation>();
		break;
	}*/
}

// State FacingGroundStation
void FacingGroundStation::init() {
	printf(" * StateMachine TASK:: Entering FacingGroundStation State *\n");
	int i;
	for (i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(FACING_GROUND_STATE_EVENT, i);
	}
}

void FacingGroundStation::work() {
	//printf(" * StateMachine TASK:: FacingGroundStation::work *\n");
	rtems_task_wake_after(
			2 * 5 * rtems_clock_get_ticks_per_second());
	rtems_event_set set = TOP::box().receive_event();
	//printf(" * StateMachine TASK:: set received: %d *\n", (int)set);
	if (set != NO_EVENT_RECEIVED){
		if (set & MOVE_TO_SAFE_EVENT){
			setState<Safe>();
		}
		else if (set & LOST_COMMUNICATION_EVENT){
			setState<RegularOperations>();
		}
		else if (set & MOVE_TO_STANDBY_EVENT){
			setState<Standby>();
		}
	}

	/*switch (set){
	case MOVE_TO_SAFE_EVENT:
		setState<Safe>();
		break;
	case MOVE_TO_STANDBY_EVENT:
		setState<Standby>();
		break;
	case LOST_COMMUNICATION_EVENT:
		setState<RegularOperations>();
		break;
	}*/
}

// State Safe
void Safe::init() {
	printf(" * StateMachine TASK:: Entering Safe State *\n");
	int i;
	for (i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(SAFE_STATE_EVENT, i);
	}
}

void Safe::work() {
	//printf(" * StateMachine TASK:: FacingGroundStation::work *\n");
	rtems_task_wake_after(
			2 * 5 * rtems_clock_get_ticks_per_second());
	rtems_event_set set = TOP::box().receive_event();
	if (set != NO_EVENT_RECEIVED){
		if (set & MOVE_TO_OP_EVENT){
			setState<Operational>();
		}
		else if (set & MOVE_TO_STANDBY_EVENT){
			setState<Standby>();
		}
	}
	/*switch (set){
	case MOVE_TO_OP_EVENT:
		setState<Operational>();
		break;
	case MOVE_TO_STANDBY_EVENT:
		setState<Standby>();
		break;
	}*/
}

// State Standby
void Standby::init() {
	printf(" * StateMachine TASK:: Entering Standby State *\n");
	int i;
	for (i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(STANDBY_STATE_EVENT, i);
	}
}

void Standby::work() {
	//printf(" * StateMachine TASK:: Standby::work *\n");
	rtems_task_wake_after(
			2 * 5 * rtems_clock_get_ticks_per_second());
	rtems_event_set set = TOP::box().receive_event();
	if (set != NO_EVENT_RECEIVED){
		if (set & MOVE_TO_STANDBY_EVENT){
			setState<Standby>();
		}
	}
	/*switch (set){
	case MOVE_TO_SAFE_EVENT:
		setState<Safe>();
		break;
	}*/
}

} // namespace Satellite


StateMachineTask::StateMachineTask() {
	// TODO Auto-generated constructor stub

}

StateMachineTask::~StateMachineTask() {
	// TODO Auto-generated destructor stub
}

void StateMachineTask::body(rtems_task_argument argument){

	Macho::Machine<Satellite::Top> m;

	for (;;){

		m->work();

	}
	exit(0);
}
