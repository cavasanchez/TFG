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

	for (int numSimulation = 0; numSimulation < 1; numSimulation++) {

		static ofstream log;

		log.open("log.txt");

	//	log << writeInLog("Executon start");

		int numAirports = linesFile(RESORCES_FOLDER + "arports.csv");
		int numFlights = linesFile(RESORCES_FOLDER + "flights.csv");
		int numSectors = linesFile(RESORCES_FOLDER + "sectors.csv");
		int numTrajectories = linesFile(RESORCES_FOLDER + "trajectories.csv");
		int numWaypoints = linesFile(RESORCES_FOLDER + "waypoints.csv");

		Problem *p = new Problem(numAirports, numSectors, numTrajectories, numWaypoints, numFlights);

		//USAR EL PRINT DATA DE AUX

		log << "Poblem characteristics:" << endl;
		log << "\t Num airports: " << p->getNumAirports() << endl;
		log << "\t Num flights: " << p->getNumFlights() << endl;
		log << "\t Num sectors: " << p->getNumSectors() << endl;
		log << "\t Num trajectories: " << p->getNumTrajectories() << endl;
		log << "\t Num waypoints: " << p->getNumWaypoints() << endl;

		//log << writeInLog("Problem initialization");
		p->inizializeProblem(numSimulation);
		//log << writeInLog("Initialization finished");

	//	log << writeInLog("Calculating shortest paths");
		p->initialSolutions();

		int iterations = 1;

		while (iterations < MAX_ITERATIONS) {

		//	cout << "******************ITERACCION " << iterations << " ************************" << endl;

			//log << writeInLog("Step 0. Add best flights queue to listFlights");
			p->addFlightsBestSolution();

			//log << writeInLog("Step 1. Take off flights in random order");
			p->initialFlightsTakeOff();

			//log << writeInLog("Step 2. trying to interchange flights");
			p->interchangeFlights();

			//log << writeInLog("Step 3. Take off flights with delays");
			p->flightsTakeOffWithDelays();

			//log << writeInLog("Step 4. Take off flights with alternatives routes");
			p->flightsTakeOffAlternativeRoutes();

			//log << writeInLog("Step 5. Find waypoints not used and try to find any route through them ");
			p->employUnusedWaypoints();

			//log << writeInLog("Step 6. Try to delay an ok flight to set a cancel flight");
			p->delayOkFlights();

			p->saveCurrentSolution(iterations);

			if (iterations % NUM_SOULUTIONS_TO_EXAMINE == 0) {
				p->setNewFlightsQueue(iterations);
			}

			if (iterations + 1 != MAX_ITERATIONS) {
				p->resetProblem();
			}

			iterations++;
		}

		p->writeResult(numSimulation);

		p->getBestSolution();

		p->writeFileForHTML();

		p->printStatusProblem();

		// log << writeInLog("Execution finished");

		log.close();

		delete p;

		cout << "END";
	}
}

