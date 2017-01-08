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

	int numAirports = linesFile("./Resources/medium1/airports.csv");
	int numFlights = linesFile("./Resources/medium1/flights.csv");
	int numSectors = linesFile("./Resources/medium1/sectors.csv");
	int numTrajectories = linesFile("./Resources/medium1/trajectories.csv");
	int numWaypoints = linesFile("./Resources/medium1/waypoints.csv");

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

	log << writeInLog("Step 1. Take of flights in random order");
	p->initialFlightsTakeOff();

	log << writeInLog("Step 2. trying to interchange flights");
	p->interchangeFlights();
	log << writeInLog("Execution finished");
	log.close();

	cout << "FIN";

}

