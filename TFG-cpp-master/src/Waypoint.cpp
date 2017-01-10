/*
 * Waypoint.cpp
 *
 *  Created on: 1/2/2016
 *      Author: carlos
 */

#include "Waypoint.h"
#include "Sector.h"

Waypoint::Waypoint(int id, std::string name, Sector *sector1) {
	_id = id;
	_name = name;
	_sector1 = sector1;
	_isAirport = 0;

}
