/*
 * ModulesOperationRequest.hpp
 *
 *  Created on: May 21, 2014
 *      Author: boris
 */

#ifndef MODULESOPERATIONREQUEST_HPP_
#define MODULESOPERATIONREQUEST_HPP_

#define NO_CHANGE		0
#define TURN_ON			1
#define STANDBY			2

class ModulesOperationRequest {

private:
	int payload_request;
	int sband_request;
	int thermal_ctrl_request;

public:
	ModulesOperationRequest(){
		payload_request = NO_CHANGE;
		sband_request = NO_CHANGE;
		thermal_ctrl_request = NO_CHANGE;
	}

	void request_payload(int action){
		payload_request = action;
	}

	void request_sband(int action){
		sband_request = action;
	}

	void request_thermal_ctrl(int action){
		thermal_ctrl_request = action;
	}

	int get_payload_request(){
		return payload_request;
	}

	int get_sband_request(){
		return sband_request;
	}

	int get_thermal_ctrl_request(){
		return thermal_ctrl_request;
	}

	virtual ~ModulesOperationRequest();
};

#endif /* MODULESOPERATIONREQUEST_HPP_ */
