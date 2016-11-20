/*
 * sector.cpp
 *
 *  Created on: 2/2/2016
 *      Author: carlos
 */

#include <string>

#include "Sector.h"

Sector::Sector(int id, std::string name, int capacity) {
	_id = id;
	_name = name;
	_capacity = capacity;
}



