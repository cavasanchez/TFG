/*
 * WaypointRoute.cpp
 *
 *  Created on: 13/2/2016
 *      Author: carlos
 */

#include "WaypointRoute.h"
#include "Waypoint.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
WaypointRoute::WaypointRoute() {

}

WaypointRoute::~WaypointRoute() {

}

WaypointRoute::WaypointRoute(int id, int inTime, Waypoint *waypointFather) {
	_id = id;
	_inTime = inTime;
	_waypointFather = waypointFather;
}

bool WaypointRoute::isSameWaypointRoute(int inTime, int idFather) {
	bool isSame = false;
	if (this->_inTime == inTime && this->_waypointFather->getId() == idFather) {
		isSame = true;
	}
	return isSame;
}

std::string WaypointRoute::getCompleteName() {
	std::ostringstream strs;
	strs << this->getWaypointFather()->getName() << "-" << this->getInTime();
	std::string str = strs.str();
	return str;
}

std::string WaypointRoute::getName() {
	return (this->getWaypointFather()->getName());
}

bool WaypointRoute::isAirport() {
	return (this->getWaypointFather()->getIsAirport());
}

int WaypointRoute::getIdSector() {
	return this->getWaypointFather()->getSector1()->getId();
}

