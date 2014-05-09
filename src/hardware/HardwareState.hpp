/*
 * HardwareState.hpp
 *
 *  Created on: May 8, 2014
 *      Author: dariaz
 */

#ifndef HARDWARESTATE_HPP_
#define HARDWARESTATE_HPP_

#include "EnergyModule.hpp"
#include "PayloadModule.hpp"
#include "SbandModule.hpp"
#include "TemperatureModule.hpp"
#include "SolarPanelsModule.hpp"
#include "ThermalControlModule.hpp"

class HardwareState {
private:
	TemperatureModule::TemperatureModule temperature;
	EnergyModule::EnergyModule energy;
	SbandModule::SbandModule sband;
	SolarPanelsModule::SolarPanelsModule solar_panels;
	PayloadModule::PayloadModule payload;
	ThermalControlModule::ThermalControlModule thermal_control;

public:
	HardwareState();
	virtual ~HardwareState();


	// getters and setters to value
	void setTemperature(int value){
		temperature.setValue(value);
	}

	int getTemperature(){
		return temperature.getValue();
	}

	void setEnergy(int value){
		energy.setValue(value);
	}

	int getEnergy(){
		return energy.getValue();
	}

	int getEnergyCurrent(){
		return energy.getCurrent();
	}

	void setEnergyCurrent(int current){
		energy.setCurrent(current);
	}

	void setSband(int value){
		sband.setValue(value);
	}

	int getSband(){
		return sband.getValue();
	}

	void setSolarPanels(int value){
		solar_panels.setValue(value);
	}

	int getSolarPanels(){
		return solar_panels.getValue();
	}

	void setPayload(int value){
		payload.setValue(value);
	}

	int getPayload(){
		return payload.getValue();
	}

	void setThermalControl(int value){
		thermal_control.setValue(value);
	}

	int getThermalControl(){
		return thermal_control.getValue();
	}

	// end of getters and setters to value

	// getters and setters to status
	void setTemperatureStatus(int status){
		temperature.setStatus(status);
	}

	int getTemperatureStatus(){
		return temperature.getStatus();
	}

	void setEnergyStatus(int status){
		energy.setStatus(status);
	}

	int getEnergyStatus(){
		return energy.getStatus();
	}

	void setSbandStatus(int status){
		sband.setStatus(status);
	}

	int getSbandStatus(){
		return sband.getStatus();
	}

	void setSolarPanelsStatus(int status){
		solar_panels.setStatus(status);
	}

	int getSolarPanelsStatus(){
		return solar_panels.getStatus();
	}

	void setPayloadStatus(int status){
		payload.setStatus(status);
	}

	int getPayloadStatus(){
		return payload.getStatus();
	}

	void setThermalControlStatus(int status){
		thermal_control.setStatus(status);
	}

	int getThermalControlStatus(){
		return thermal_control.getStatus();
	}
	// end of getters and setters to status

	//getters of names

	string getTemperatureName(){
		return temperature.getName();
	}

	string getEnergyName(){
		return energy.getName();
	}

	string getSbandName(){
		return sband.getName();
	}

	string getSolarPanelsName(){
		return solar_panels.getName();
	}

	string getPayloadName(){
		return payload.getName();
	}

	string getThermalControlName(){
		return thermal_control.getName();
	}
};

#endif /* HARDWARESTATE_HPP_ */
