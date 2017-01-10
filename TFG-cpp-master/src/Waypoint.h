/*
 * waypoint.h
 *
 *  Created on: 30/1/2016
 *      Author: carlos
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include <string>
#include "Sector.h"

class Waypoint {
public:

	Waypoint(int id, std::string name, Sector *sector1);

	int getId() const {
		return _id;
	}

	void setId(int id) {
		_id = id;
	}

	const std::string& getName() const {
		return _name;
	}

	void setName(const std::string& name) {
		_name = name;
	}

	int getIsAirport() const {
		return _isAirport;
	}

	void setIsAirport(int isAirport) {
		_isAirport = isAirport;
	}

	const Sector* getSector1() const {
		return _sector1;
	}

//	const Sector* getSector2() const {
//		return _sector2;
//	}


private:

	int _id;
	std::string _name;
	Sector *_sector1;
//	Sector *_sector2;
	int _isAirport;

};

#endif /* WAYPOINT_H_ */
