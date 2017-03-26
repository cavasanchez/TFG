/*
 * TimeMoment.cpp
 *
 *  Created on: 2/2/2016
 *      Author: carlos
 */
#include "TimeMoment.h"
#include <stdlib.h>

TimeMoment::TimeMoment(int **numFlightsMatrix, int* numFlightsSector, int numWaypoints) {
	_numFlightsMatrix = numFlightsMatrix;
	_numFlightsSector = numFlightsSector;
	_numWaypoints = numWaypoints;
}

TimeMoment::~TimeMoment() {

	for (int i = 0; i < _numWaypoints; i++) {
		free(_numFlightsMatrix[i]);
	}

	free(_numFlightsMatrix);

	free(_numFlightsSector);


}
