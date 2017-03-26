/*
 * TimeMoment.h
 *
 *  Created on: 2/2/2016
 *      Author: carlos
 */

#ifndef TIMEMOMENT_H_
#define TIMEMOMENT_H_

class TimeMoment {
public:

	TimeMoment(int **numFlightsMatrix, int* numFlightsSector, int numWaypoints);

	virtual ~TimeMoment();

	int** getNumFlightsMatrix() const {
		return _numFlightsMatrix;
	}

	void setNumFlightsMatrix(int** numFlightsMatrix) {
		_numFlightsMatrix = numFlightsMatrix;
	}

	int* getNumFlightsSector() const {
		return _numFlightsSector;
	}

	void setNumFlightsSector(int* numFlightsSector) {
		_numFlightsSector = numFlightsSector;
	}

private:
	int **_numFlightsMatrix;
	int *_numFlightsSector;
	int _numWaypoints;
};

#endif /* TIMEMOMENT_H_ */
