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

	Waypoint(int id, std::string name, std::string sector1);

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

	const std::string& getSector1() const {
		return _sector1;
	}

	void setSector1(const std::string& sector1) {
		_sector1 = sector1;
	}

	const std::string& getSector2() const {
		return _sector2;
	}

	void setSector2(const std::string& sector2) {
		_sector2 = sector2;
	}

	int getIsAirport() const {
		return _isAirport;
	}

	void setIsAirport(int isAirport) {
		_isAirport = isAirport;
	}

private:

	int _id;
	std::string _name;
	std::string _sector1;
	std::string _sector2;
	int _isAirport;

};

#endif /* WAYPOINT_H_ */
