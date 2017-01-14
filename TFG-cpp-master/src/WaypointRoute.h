/*
 * WaypointRoute.h
 *
 *  Created on: 13/2/2016
 *      Author: carlos
 */

#include <string>

#include "Waypoint.h"

#ifndef WAYPOINTROUTE_H_
#define WAYPOINTROUTE_H_

class WaypointRoute {
public:
	WaypointRoute();

	WaypointRoute(int id, int inTime, Waypoint *waypointFather);

	int getId() const {
		return _id;
	}

	void setId(int id) {
		_id = id;
	}

	int getInTime() const {
		return _inTime;
	}

	void setInTime(int inTime) {
		_inTime = inTime;
	}

	 Waypoint* getWaypointFather() const {
		return _waypointFather;
	}

	std::string getName();

	bool isSameWaypointRoute(int inTime, int idFather);
	bool isAirport();

	std::string getCompleteName();

	int getIdSector();


private:
	int _id;
	int _inTime;
	Waypoint* _waypointFather;
};

#endif /* WAYPOINTROUTE_H_ */
