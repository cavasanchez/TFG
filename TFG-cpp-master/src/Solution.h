/*
 * Solution.h
 *
 *  Created on: 12 feb. 2017
 *      Author: carlos
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <map>

using namespace std;


class Solution {
public:
	Solution();
	Solution(int, map<int, pair<int, vector<int> > >, int);

	virtual ~Solution();

	const map<int, pair<int, vector<int> > >& getFlightSolutions() const {
		return _flightSolutions;
	}

	void setFlightSolutions(const map<int, pair<int, vector<int> > >& flightSolutions) {
		_flightSolutions = flightSolutions;
	}

	int getIteration() const {
		return _iteration;
	}

	void setIteration(int iteration) {
		_iteration = iteration;
	}

	int getValue() const {
		return _value;
	}

	void setValue(int value) {
		_value = value;
	}

private:
	int _iteration;
	//map with flightId, <flightStatus, flightSolution>
	map<int, pair<int, vector<int> > >_flightSolutions;
	int _value;
};

#endif /* SOLUTION_H_ */
