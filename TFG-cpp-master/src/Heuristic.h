/*
 * Heuristic.h
 *
 *  Created on: 22 oct. 2016
 *      Author: carlos
 */

#ifndef HEURISTIC_H_
#define HEURISTIC_H_


const double MAX_HEURISTIC_QUALITY = 100;

class Heuristic {
public:
	Heuristic(int numberRoutes, int numberWaypointRoutes);
	virtual ~Heuristic();

	int getNumberRoutes() const {
		return _numberRoutes;
	}

	void setNumberRoutes(int numberRoutes) {
		this->_numberRoutes = numberRoutes;
	}

	int getNumberWaypointRoutes() const {
		return _numberWaypointRoutes;
	}

	void setNumberWaypointRoutes(int numberWaypointRoutes) {
		this->_numberWaypointRoutes = numberWaypointRoutes;
	}

	double getHeuristicNumberwaypoints();

private:
	int _numberRoutes;
	int _numberWaypointRoutes;

};

#endif /* HEURISTIC_H_ */
