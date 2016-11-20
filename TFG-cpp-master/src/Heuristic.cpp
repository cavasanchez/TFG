/*
 * Heuristic.cpp
 *
 *  Created on: 22 oct. 2016
 *      Author: carlos
 */

#include "Heuristic.h"

Heuristic::Heuristic(int numberRoutes, int numberWaypointRoutes) {
	this->_numberRoutes = numberRoutes;
	this->_numberWaypointRoutes = numberWaypointRoutes;

}

Heuristic::~Heuristic() {
	// TODO Auto-generated destructor stub
}

/**
 *
 */
double Heuristic::getHeuristicNumberwaypoints() {
	double heuristic_decrease = (this->_numberWaypointRoutes) / this->_numberRoutes;

	double result = MAX_HEURISTIC_QUALITY - heuristic_decrease;

	return result;

}

