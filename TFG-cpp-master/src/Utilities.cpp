/*
 * Aux.cpp
 *
 *  Created on: 30/1/2016
 *      Author: carlos
 */

#include "Utilities.h"

#include <stdlib.h>
#include <algorithm>    // std::sort
#include <cstdio>
#include <ctime>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
int linesFile(string routeString) {
	const char *route = routeString.c_str();

	int numLines = 0;
	std::ifstream f(route);
	std::string line;
	for (int i = 0; std::getline(f, line); ++i) {
		numLines++;
	}
	f.close();
	return numLines;
}

void printArrayInt(int *array, int size) {
	for (int row = 0; row < size; row++) {
		printf("%i -> %i  ", row, array[row]);
		printf("\n");
	}
}

void printProblemData(std::ofstream log, Problem *p) {
	log << "DATOS DEL PROBLEMA " << std::endl;
	log << "Número aeropuertos: " << p->getNumAirports() << std::endl;
	log << "Número vuelos: " << p->getNumFlights() << std::endl;
	log << "Número sectores: " << p->getNumSectors() << std::endl;
	log << "Número trayectorias: " << p->getNumTrajectories() << std::endl;
	log << "Número waypoints: " << p->getNumWaypoints() << std::endl;
}

void printMatrixInt(int **matrix, int size) {
	for (int row = 0; row < size; row++) {
		for (int columns = 0; columns < size; columns++)
			printf("%i  ", matrix[row][columns]);
		printf("\n");
	}
}

void inicializeMatrixTo0(int **matrix, int num) {
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			matrix[i][j] = 0;
		}
	}
}

void printMatrixString(std::string **matrix, int size) {
	for (int row = 0; row < size; row++) {
		for (int columns = 0; columns < size; columns++)
			cout << matrix[row][columns] << " ";
		cout << endl;
	}
}

std::string writeInLog(std::string text) {
	//Fecha de hoy
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	std::string str(buffer);

	cout << str + " " + text + "\n";
	return str + " " + text + "\n";

}

void printVectorString(vector<string> vectorStrings) {
	for (std::vector<string>::const_iterator i = vectorStrings.begin(); i != vectorStrings.end(); ++i)
		std::cout << *i << ' ';
}

void printVectorInt(vector<int> vectorInts) {
	for (std::vector<int>::const_iterator i = vectorInts.begin(); i != vectorInts.end(); ++i) {
		std::cout << *i << ' ';
	}
}

vector<string> removeDuplicatesVectorString(vector<string> vectorStrings) {
	sort(vectorStrings.begin(), vectorStrings.end());
	vectorStrings.erase(unique(vectorStrings.begin(), vectorStrings.end()), vectorStrings.end());
	return vectorStrings;
}

vector<int> removeDuplicatesVectorInt(vector<int> vectorInt) {
	sort(vectorInt.begin(), vectorInt.end());
	vectorInt.erase(unique(vectorInt.begin(), vectorInt.end()), vectorInt.end());
	return vectorInt;
}

vector<int> removeDuplicatesVectorIntWithoutSort(vector<int> vectorInt) {
	vector<int> result;

	for (std::vector<int>::iterator i = vectorInt.begin(); i != vectorInt.end(); ++i) {
		if (!checkVectorContainsElement(result, *i)) {
			result.push_back(*i);
		}
	}
	return result;
}

vector<string> joinVectorString(vector<string> vectorA, vector<string> vectorB, vector<string> &finalVector) {
	finalVector.reserve(vectorA.size() + vectorB.size()); // preallocate memory
	finalVector.insert(finalVector.end(), vectorA.begin(), vectorA.end());
	finalVector.insert(finalVector.end(), vectorB.begin(), vectorB.end());
	return finalVector;
}

vector<int> arrayIntToVector(int *array) {
	int test[3] = { 1, 2, 3 };
	printArrayInt(test, 3);
	vector<int> ve = (std::vector<int>(array, array + sizeof array / sizeof array[0]));
	printVectorInt(ve);
	exit(1);

	return (std::vector<int>(array, array + sizeof array / sizeof array[0]));
}

int** initializeMatrixRoutes() {
	int size = 1000;
	int **matrix = (int **) malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		matrix[i] = (int *) malloc(size * sizeof(int));
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = -1;
		}
	}
	return matrix;
}

vector<int> createVectorFromList(list<int> path) {
	vector<int> solution;
	int sizeList = path.size();
	for (int i = 0; i < sizeList; i++) {
		int currentValue = path.front();
		path.pop_front();
		solution.push_back(currentValue);
	}
	return solution;
}

vector<int> getFlightsThatBlocks(int value, map<int, vector<int> > original) {
	vector<int> flightsThatBlocks;

	for (map<int, vector<int> >::iterator it = original.begin(); it != original.end(); ++it) {
		int currentFlight = it->first;
		vector<int> candidates = it->second;
		for (std::vector<int>::iterator currentCandidate = candidates.begin(); currentCandidate != candidates.end();
				++currentCandidate) {
			if (*currentCandidate == value) {
				flightsThatBlocks.push_back(currentFlight);
			}
		}
	}
	return flightsThatBlocks;
}

int getMinValueFomVector(vector<int> vector) {
	int min = 1000;
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
		if (*it < min)
			min = *it;
	}
	return min;
}

int getMaxValueFomVector(vector<int> vector) {
	int max = 0;
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it) {
		if (*it > max)
			max = *it;
	}
	return max;
}

vector<int> removeElementsFromVector(vector<int> orignal, vector<int> elementsToDelete) {
	vector<int> erased = orignal;
	for (std::vector<int>::iterator elementToDelete = elementsToDelete.begin();
			elementToDelete != elementsToDelete.end(); ++elementToDelete) {
		for (vector<int>::iterator it = erased.begin(); it != erased.end(); ++it) {
			if (*it == *elementToDelete) {
//				cout << "borro el" << *it << endl;
				erased.erase(it);
				break;
			}
		}
	}
	return erased;
}
bool vectorContainsAllValues(vector<int> orignal, vector<int> elementsToCheck) {
	for (vector<int>::iterator elementToFind = elementsToCheck.begin(); elementToFind != elementsToCheck.end();
			++elementToFind) {
		if (std::find(orignal.begin(), orignal.end(), *elementToFind) == orignal.end())
			return false;
	}
	return true;
}

pair<int, int> getMinMaxTimeWR(vector<int> candidates, Problem *p) {
	vector<int> times;
	for (vector<int>::iterator eachFlightId = candidates.begin(); eachFlightId != candidates.end(); ++eachFlightId) {
		Flight*f = p->getFlightById(*eachFlightId);
		vector<int> path = f->getIntialSolution();
		for (vector<int>::iterator it = path.begin(); it != path.end(); ++it) {
			WaypointRoute *wr = f->getWRById(*it);
			times.push_back(wr->getInTime());
		}
	}
	int min = getMinValueFomVector(times);
	int max = getMaxValueFomVector(times);
	pair<int, int> minMax(min, max);
	return minMax;

}

bool checkVectorContainsElement(vector<int> v, int value) {
	if (std::find(v.begin(), v.end(), value) != v.end())
		return true;

	return false;
}

bool checkVectorStringContainsElement(vector<string> v, string value) {
	for (vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
		string currentValue = *it;
		if (currentValue.compare(value) == 0)
			return true;
	}
	return false;
}

int getNumCommonElementsVectorString(vector<string> a, vector<string> b) {
	int common = 0;
	for (vector<string>::iterator it = a.begin(); it != a.end(); ++it) {
		if (checkVectorStringContainsElement(b, *it)) {
			common++;
		}
	}
	return common;

}
