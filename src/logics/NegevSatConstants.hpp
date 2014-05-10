/*
 * NegevSatStates.hpp
 *
 *  Created on: May 9, 2014
 *      Author: dariaz
 */

#ifndef NEGEVSATSTATES_HPP_
#define NEGEVSATSTATES_HPP_

// satellite states enums
#define INIT_STATE				0
#define STANDBY_STATE			1
#define SAFE_STATE				2
#define REGULAR_OPS_STATE		3
#define FACING_GROUND_STATE		4

//satellite states as chars
static const char INIT_STATE_STR[] = "INIT_STATE";
static const char STANDBY_STATE_STR[] = "STAND_BY_STATE";
static const char SAFE_STATE_STR[] = "SAFE_STATE";
static const char REGULAR_OPS_STATE_STR[] = "OPERATIONAL_STATE";
static const char FACING_GROUND_STATE_STR[] = "OPERATIONAL_STATE";

//satellite modules states enums
#define MODULE_OK				0
#define MODULE_CRIT				1
#define MODULE_OFF				2
#define MODULE_STANDBY			3

//satellite modules states as chars
static const char OK_STR[] = "OK";
static const char CRIT_STR[] = "CRIT";
static const char OFF_STR[] = "OFF";
static const char STAND_BY_STR[] = "STANDBY";

//negevSat reserved words as chars
static const char TEMPERATURE_STR[] = "INIT_STATE";
static const char ENERGY_STR[] = "STAND_BY_STATE";
static const char STATIC_STR[] = "SAFE_STATE";
static const char REGULAR_OPS_STATE_STR[] = "OPERATIONAL_STATE";
static const char FACING_GROUND_STATE_STR[] = "OPERATIONAL_STATE";

#endif /* NEGEVSATSTATES_HPP_ */
