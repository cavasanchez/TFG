/*
 * Solution.cpp
 *
 *  Created on: 12 feb. 2017
 *      Author: carlos
 */

#include "Solution.h"

Solution::Solution() {
	// TODO Auto-generated constructor stub

}

Solution::Solution(int iteration, map<int, pair<int, vector<int> > > flights, int value) {
	_iteration = iteration;
	_flightSolutions = flights;
	_value = value;
}

Solution::~Solution() {
	// TODO Auto-generated destructor stub
}

