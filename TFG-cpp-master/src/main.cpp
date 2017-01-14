//============================================================================
// Name        : TFG.cpp
// Author      : Carlos
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <ctime>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Problem.h"
#include "Utilities.h"

using namespace std;

int main() {

	static ofstream log;

	log.open("log.txt");

	log << writeInLog("Executon start");


	int numAirports = linesFile(RESORCES_FOLDER+"arports.csv");
	int numFlights = linesFile(RESORCES_FOLDER+"flights.csv");
	int numSectors = linesFile(RESORCES_FOLDER+"sectors.csv");
	int numTrajectories = linesFile(RESORCES_FOLDER+"trajectories.csv");
	int numWaypoints = linesFile(RESORCES_FOLDER+"waypoints.csv");

	Problem *p = new Problem(numAirports, numSectors, numTrajectories, numWaypoints, numFlights);

	//USAR EL PRINT DATA DE AUX

	log << "Poblem characteristics:" << endl;
	log << "\t Num airports: " << p->getNumAirports() << endl;
	log << "\t Num flights: " << p->getNumFlights() << endl;
	log << "\t Num sectors: " << p->getNumSectors() << endl;
	log << "\t Num trajectories: " << p->getNumTrajectories() << endl;
	log << "\t Num waypoints: " << p->getNumWaypoints() << endl;

	log << writeInLog("Problem initialization");
	p->inizializeProblem();
	log << writeInLog("Initialization finished");

	log << writeInLog("Calculating shortest paths");
	p->initialValidations();

	log << writeInLog("Step 1. Take off flights in random order");
	p->initialFlightsTakeOff();

	int lastNumFlightsNoCancel = 0;
	int iterations = 0;
	int currentFlightNoCanceled = 0;

//	while (iterations < MAX_ITERATIONS) {
		while (iterations < 1) {

		cout << "******************ITERACCION " << iterations << " ************************" << endl;
		log << writeInLog("Step 2. trying to interchange flights");
		p->interchangeFlights();
		log << writeInLog("Step 3. Take off flights with delays");
		p->flightsTakeOffWithDelays();

		log << writeInLog("Step 4. Take off flights with alternatives routes");
		p->flightsTakeOffAlternativeRoutes();

		int currentFlightNoCanceled = p->getNumFlightsNoCanceled();
		iterations++;
	}

	p->writeFileForHTML();

	p->printStatusProblem();
	log << writeInLog("Execution finished");

	log.close();

	cout << "FIN";

}

