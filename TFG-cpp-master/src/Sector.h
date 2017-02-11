/*
 * Sector.h
 *
 *  Created on: 30/1/2016
 *      Author: carlos
 */

#ifndef SECTOR_H_
#define SECTOR_H_

#include <string>

class Sector {
public:
	Sector();

	Sector(int id, std::string name, int capacity);

	int getCapacity() const {
		return _capacity;
	}

	void setCapacity(int capacity) {
		_capacity = capacity;
	}

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

private:

	int _id;
	std::string _name;
	int _capacity;

};

#endif /* SECTOR_H_ */
