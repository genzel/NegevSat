/*
 * CommandExecutor.hpp
 *
 *  Created on: May 10, 2014
 *      Author: dariaz
 */

#ifndef COMMANDEXECUTOR_HPP_
#define COMMANDEXECUTOR_HPP_

#include "data_protocol/CMDDictionary.hpp"
#include "data_protocol/WorkDescription.hpp"
#include "logics/NegevSatConstants.hpp"
#include "logics/Global.hpp"
#include "hardware/HardwareState.hpp"

class CommandExecutor {
private:
	HardwareState::HardwareState* hardware;
public:
	CommandExecutor();
	virtual ~CommandExecutor();
	void execute(WorkDescription::WorkDescription work);
	void setHardawre(HardwareState::HardwareState* _hardware);
};

#endif /* COMMANDEXECUTOR_HPP_ */
