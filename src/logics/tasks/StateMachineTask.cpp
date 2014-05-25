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
		Box() : state(INIT_STATE) {}

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
		rtemsEvent event;
	};

	STATE(Top)

	// Machine's event protocol
	virtual void work() {}		// Do operations


private:
	// Initial entry action
	void init();
};

// Satellite's initialize state
SUBSTATE(InitState, Top) {
	STATE(InitState)

private:
	void entry();
};


// Satellite is ready to work
SUBSTATE(Operational, Top) {
	STATE(Operational)


private:
	void entry();
};

// Satellite is facing the ground station
SUBSTATE(FacingGroundStation, Operational) {
	STATE(FacingGroundStation)

									void work();

private:
	void entry();
};

// Satellite is facing the ground station
SUBSTATE(RegularOperations, Operational) {
	STATE(RegularOperations)

											void work();

private:
	void entry();
};

// Satellite is in safe mode
SUBSTATE(Safe, Top) {
	STATE(Safe)

											void work();

private:
	void entry();
};

// Satellite is in standby mode
SUBSTATE(Standby, Top) {
	STATE(Standby)

											void work();

private:
	void entry();
};

//////////////////////////////////////////////////////////////////////
// Event handler and box implementations

// Top state
void Top::init() {
	printf(" * StateMachine TASK:: TopState::init *\n");
	setState<InitState>();
}

// InitState state
void InitState::entry() {
	printf(" * StateMachine TASK:: InitState::entry *\n");
	setState<Operational>();
}

// State Operational
void Operational::entry() {
	printf(" * StateMachine TASK:: Operational::entry *\n");
	setState<RegularOperations>();
}

// State RegularOperations
void RegularOperations::entry() {
	printf(" * StateMachine TASK:: RegularOperations::entry *\n");
	int i;
	for (i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(REGULAR_OPS_STATE_EVENT, i);
	}
}

void RegularOperations::work() {
	printf(" * StateMachine TASK:: RegularOperations::work *\n");
	rtems_event_set set = TOP::box().receive_event();
	switch (set){
	case MOVE_TO_SAFE_EVENT:
		setState<Safe>();
		break;
	case MOVE_TO_STANDBY_EVENT:
		setState<Standby>();
		break;
	case RECEIVED_COMMUNICATION_EVENT:
		setState<FacingGroundStation>();
		break;
	}
}

// State FacingGroundStation
void FacingGroundStation::entry() {
	printf(" * StateMachine TASK:: FacingGroundStation::entry *\n");
	int i;
	for (i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(FACING_GROUND_STATE_EVENT, i);
	}
}

void FacingGroundStation::work() {
	printf(" * StateMachine TASK:: FacingGroundStation::work *\n");
	rtems_event_set set = TOP::box().receive_event();
	switch (set){
	case MOVE_TO_SAFE_EVENT:
		setState<Safe>();
		break;
	case MOVE_TO_STANDBY_EVENT:
		setState<Standby>();
		break;
	case LOST_COMMUNICATION_EVENT:
		setState<RegularOperations>();
		break;
	}
}

// State Safe
void Safe::entry() {
	printf(" * StateMachine TASK:: Safe::entry *\n");
	int i;
	for (i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(SAFE_STATE_EVENT, i);
	}
}

void Safe::work() {
	printf(" * StateMachine TASK:: FacingGroundStation::work *\n");
	rtems_event_set set = TOP::box().receive_event();
	switch (set){
	case MOVE_TO_OP_EVENT:
		setState<Operational>();
		break;
	case MOVE_TO_STANDBY_EVENT:
		setState<Standby>();
		break;
	}
}

// State Standby
void Standby::entry() {
	printf(" * StateMachine TASK:: Standby::entry *\n");
	int i;
	for (i=0; i < NUMBER_OF_ACTIVE_TASKS; i++){
		TOP::box().send_event(STANDBY_STATE_EVENT, i);
	}
}

void Standby::work() {
	printf(" * StateMachine TASK:: Standby::work *\n");
	rtems_event_set set = TOP::box().receive_event();
	switch (set){
	case MOVE_TO_SAFE_EVENT:
		setState<Safe>();
		break;
	}
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