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

int linesFile(char* route) {
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
	for (std::vector<int>::const_iterator i = vectorInts.begin(); i != vectorInts.end(); ++i)
		std::cout << *i << ' ';
}

vector<string> removeDuplicatesVectorString(vector<int> vectorStrings) {
	sort(vectorStrings.begin(), vectorStrings.end());
	vectorStrings.erase(unique(vectorStrings.begin(), vectorStrings.end()), vectorStrings.end());
	return vectorStrings;
}

vector<string> removeDuplicatesVectorInt(vector<int> vectorStrings) {
	sort(vectorStrings.begin(), vectorStrings.end());
	vectorStrings.erase(unique(vectorStrings.begin(), vectorStrings.end()), vectorStrings.end());
	return vectorStrings;
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
		vector<int> currentCandidates = it->second;
		//for each candidate
		for (vector<int>::iterator eachCandidate = currentCandidates.begin(); eachCandidate != currentCandidates.end();
				++eachCandidate) {
			if (value == *eachCandidate) {
				flightsThatBlocks.push_back(*eachCandidate);
			}
		}
	}

	return flightsThatBlocks;
}

