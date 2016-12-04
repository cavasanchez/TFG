/*
 * Problem.cpp
 *
 *  Created on: 30/1/2016
 *      Author: carlos
 */

#include "Problem.h"
#include "TimeMoment.h"
#include "Waypoint.h"
#include "Sector.h"
#include "WaypointRoute.h"
#include <ctime>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <sstream>
#include <string>
#include "Flight.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <cstdlib>      // std::rand, std::srand

#include <limits> // for numeric_limits

#include <queue>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

#include "Pathfinder.h"
#include "Utilities.h"

Problem::Problem() {

}
Problem::Problem(int numAirports, int numSectors, int numTrajectories, int numWaypoints, int numFlights) {
	_numAirports = numAirports;
	_numSectors = numSectors;
	_numTrajectories = numTrajectories;
	_numWaypoints = numWaypoints;
	_numFlights = numFlights;
	_iteration = 0;
}

/*
 * inicializa los datos del problema
 */
void Problem::inizializeProblem() {
	cout << "crea los sectores" << endl;
	createSectors();

	cout << "crea los waypoints" << endl;
	createWaypoints();

	cout << "crea los flights" << endl;
	createFlights();

	cout << "crea los times" << endl;
	createTimes();

	cout << "crea las rutas" << endl;
	createAllRoutes();

	cout << "crea los order" << endl;
	createOrderFlights();

}

/**
 * Find flights with no problems and remove it from problem
 */
void Problem::initialValidations() {
	cout << "busca los unconnected" << endl;
	this->getFlightsUnconnected();

	cout << "calcula el camino más corto para cada vuelo" << endl;
	this->getShortestRoutes();

//	cout << "busca los sobrecargados iniciales" << endl;
//	this->getInitialOverloadSectors();

//	for (int i = 0; i < 15; i++) {
//		cout << "****EN " << i << endl;
//		printArrayInt(_timeMomentlist[i]->getNumFlightsSector(), this->getNumSectors());
//	}
}

void Problem::getShortestRoutes() {
	for (int i = 0; i < this->getNumFlights(); i++) {
		Djistra(_listFlights[i], OPTION_SHORTEST_PATH);
	}
}

/**
 * Step 1: take off flights in random order. No alternative ways and no delays considered
 */
void Problem::initialFlightsTakeOff() {
	for (int i = 0; i < this->getNumFlights(); i++) {
		int currentPosition = this->_orderFlights[i];
		Djistra(_listFlights[currentPosition], OPTION_ONLY_INITIAL_SOLUTION);
	}
}
/**
 * Try to interchange a bad flight to
 */
void Problem::interchangeFlights() {

}

void Problem::createOrderFlights() {
	std::srand(unsigned(std::time(0)));
	std::vector<int> myvector;

	// set some values:
	for (int i = 0; i < this->getNumFlights(); ++i)
		myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

	// using built-in random generator:
	std::random_shuffle(myvector.begin(), myvector.end());
	this->_orderFlights = myvector;

	// print out content:
	std::cout << "my vector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;

}

void Problem::createTimes() {
	_timeMomentlist = new TimeMoment*[1000];
	cout << "creando times... " << endl;

	for (int id = 0; id < 1000; id++) {
		int **initialMatrix = (int **) malloc(this->getNumWaypoints() * sizeof(int*));

		for (int i = 0; i < this->getNumWaypoints(); i++) {
			initialMatrix[i] = (int *) malloc(this->getNumWaypoints() * sizeof(int));
		}

		int *initialSector = (int*) malloc(this->getNumSectors() * sizeof(int));

		for (int i = 0; i < this->getNumSectors(); i++) {
			initialSector[i] = 0;
		}

		inicializeMatrixTo0(initialMatrix, this->getNumWaypoints());
		TimeMoment *t = new TimeMoment(initialMatrix, initialSector);

		_timeMomentlist[id] = t;
	}
}

Waypoint* Problem::getWaypointById(int id) {
	Waypoint *w;
	for (int i = 0; i < this->getNumWaypoints(); i++) {
		if (_listWaypoints[i]->getId() == id) {
			w = _listWaypoints[i];
			break;
		}
	}
	return w;
}

Sector* Problem::getSectorById(int id) {

	Sector *s;

	for (int i = 0; i < this->getNumSectors(); i++) {
		if (_listSectors[i]->getId() == id) {
			s = _listSectors[i];
			break;
		}
	}
	return s;
}

int Problem::getIdWaypointByName(std::string name) {
	Waypoint *w;

	for (int i = 0; i < this->getNumWaypoints(); i++) {
		if (_listWaypoints[i]->getName().compare(name) == 0) {
			w = _listWaypoints[i];
			break;
		}
	}
	return w->getId();
}

Sector* Problem::getSectorByName(std::string name) {
	Sector *s;
	for (int i = 0; i < this->getNumSectors(); i++) {
		if (_listSectors[i]->getName().compare(name) == 0) {
			s = _listSectors[i];
			break;
		}
	}
	return s;
}

int Problem::getIdSectorByName(std::string name) {
	int id;
	for (int i = 0; i < this->getNumSectors(); i++) {
		if (_listSectors[i]->getName().compare(name) == 0) {
			id = _listSectors[i]->getId();
			break;
		}
	}
	return id;
}

void Problem::createAllRoutes() {
	cout << "Creando rutas..." << endl;
	for (int i = 0; i < this->getNumFlights(); i++) {
		createRoutes(_listFlights[i]);
	}
}

/*
 * Iniciliaza la lista de vuelos con numWaypoints, timeStart, idWaypointStart, idWaypointEnd
 */
void Problem::createFlights() {
	int cont = 0;
	ifstream fe("./Resources/medium1/flights.csv");
	std::string line;
	_listFlights = new Flight*[this->getNumFlights()];
	while (std::getline(fe, line)) {
		string array[15];
		int i = 0;
		stringstream ssin(line);
		while (ssin.good() && i < 15) {
			ssin >> array[i];
			++i;
		}

		Flight *newFlight = new Flight(atoi(array[0].c_str()), atoi(array[14].c_str()),
				this->getIdWaypointByName(array[12]), this->getIdWaypointByName(array[13]), atoi(array[11].c_str()));
		newFlight->setNumWaypoints(newFlight->numWaypointsFlight(newFlight->getId(), this->getNumWaypoints()));

		_listFlights[cont] = newFlight;
		cont++;
	}
}

/*
 *Inicializa la lista de sectores
 */
void Problem::createSectors() {
	int cont = 0;
	ifstream fe("./Resources/medium1/sectors.csv");
	std::string line;

	_listSectors = new Sector*[this->getNumSectors()];
	while (std::getline(fe, line)) {
		string array[1];
		int i = 0;
		stringstream ssin(line);
		while (ssin.good() && i < 1) {
			ssin >> array[i];
			++i;
		}

		Sector *newSector = new Sector(cont, array[0], 1);
		_listSectors[cont] = newSector;
		cont++;
	}
	fe.close();
}
int Problem::nameInList(string nameWay, Waypoint **waypoints, int cont) {

	int isInList = -1;
	for (int i = 0; i < cont; i++) {
		if (waypoints[i]->getName().compare(nameWay) == 0) {
			isInList = waypoints[i]->getId();
			break;
		}
	}
	return isInList;
}

/*
 * Inicializa la lista de Waypoints
 */
void Problem::createWaypoints() {
	int cont = 0;
	ifstream fe("./Resources/medium1/waypoints.csv");
	std::string line;

	_listWaypoints = new Waypoint*[this->getNumWaypoints()];
	while (std::getline(fe, line)) {
		string array[2];
		int i = 0;
		stringstream ssin(line);
		while (ssin.good() && i < 2) {
			ssin >> array[i];
			++i;
		}

		string auxName = array[0];
		string auxSector = array[1];

		int posOld = nameInList(auxName, _listWaypoints, cont);

		//New Waypoint
		if (posOld < 0) {
			Waypoint *newWaypoint = new Waypoint(cont, array[0], array[1]);
			if (array[0][0] == 'A') {
				newWaypoint->setIsAirport(1);
				cout << array[0] << " es aeropuerto" << endl;
			}
			_listWaypoints[cont] = newWaypoint;

		}
		//Waypoint already in list
		else {

			_listWaypoints[posOld]->setSector2(auxSector);
			cont--;
		}

		cont++;
	}

	this->setNumWaypoints(cont);
	fe.close();

}

//void Problem::calculateAllShortestPath() {
//	for (int i = 0; i < this->getNumFlights(); i++) {
//		if (_listFlights[i]->getStatus() == 0)
//			Djistra(_listFlights[i], OPTION_ONLY_OVERLOAD_SECTORS);
//	}
//}

//void Problem::getInitialOverloadSectors() {
//	for (int i = 0; i < this->getNumFlights(); i++) {
//		Djistra(_listFlights[i], OPTION_SHORTEST_PATH);
//	}
//
//	std::vector<int> sectorsToAvoid;
//	std::vector<int> totalChargeAllTimes(this->getNumSectors(), 0);
//	for (int i = 0; i < 50; i++) {
//
//		for (int j = 0; j < this->getNumSectors(); j++) {
//			// if in some moment is overload
//			if (_timeMomentlist[i]->getNumFlightsSector()[j] > 1) {
//				sectorsToAvoid.push_back(_timeMomentlist[i]->getNumFlightsSector()[j]);
//			}
//			totalChargeAllTimes[j] += _timeMomentlist[i]->getNumFlightsSector()[j];
//		}
//	}
//	_initialOverload = totalChargeAllTimes;
//	for (std::vector<int>::const_iterator i = totalChargeAllTimes.begin(); i != totalChargeAllTimes.end(); ++i)
//		std::cout << *i << ' ';
//}

void Problem::getFlightsUnconnected() {
	std::vector<string> allWaypointsRoute;

	//First get waypoints rout of each flight
	for (int i = 0; i < this->getNumFlights(); i++) {
		vector<string> flightWaypointRouteNames = this->getUniqueWaypointsRouteByFlight(_listFlights[i]);
		allWaypointsRoute.insert(allWaypointsRoute.end(), flightWaypointRouteNames.begin(),
				flightWaypointRouteNames.end());
	}
	//If all flight waypointsRoute appears only once, its an unconnected flight
	for (int i = 0; i < this->getNumFlights(); i++) {
		vector<string> flightWaypointsRoute = this->getUniqueWaypointsRouteByFlight(_listFlights[i]);
		if (this->flightIsUnconnected(allWaypointsRoute, flightWaypointsRoute)) {
			cout << "SACAMOS EL " << i << endl;
			_listFlights[i]->setStatus(2);
		}
	}
	cout << endl;
	//printVectorString(allWaypointsRoute);
}
//Return if all waypoints route of flight only appears once in allWaypointsRoute
bool Problem::flightIsUnconnected(vector<string> allWaypointsRoute, vector<string> flightWaypointsRoute) {

	int size = flightWaypointsRoute.size();
	bool allUnconnected = true;
	for (int i = 0; i < size; i++) {
		int appearances = std::count(allWaypointsRoute.begin(), allWaypointsRoute.end(), flightWaypointsRoute[i]);
//		std::cout << flightWaypointsRoute[i] << " appears " << appearances << " times.\n";
		if (appearances > 1) {
			allUnconnected = false;
			break;
		}
	}
	return allUnconnected;
}

void Problem::assignHeuristcs() {
	for (int i = 0; i < this->getNumFlights(); i++) {
		if (_listFlights[i]->getStatus() == 0) {
			_listFlights[i]->assignHeuristics();
		}
	}
}

vector<string> Problem::getUniqueWaypointsRouteByFlight(Flight *flight) {
	vector<string> flightWaypointRouteNames;
	for (int i = 0; i < flight->getNumWaypointsRoute(); i++) {
		WaypointRoute *currentWaypointRoute = flight->getListWaypointsRoute()[i];
		flightWaypointRouteNames.push_back(currentWaypointRoute->getName());
	}

//Remove duplicates from vector
	flightWaypointRouteNames = removeDuplicatesVectorString(flightWaypointRouteNames);
	return flightWaypointRouteNames;
}

//Actualizar el nº de vuelos por sector en tiempo t
void Problem::updateTimeSector(vector<int> PathIdWaypointsRoute, int numWaypointsFlight, Flight *flight) {
	int lastInstantFlight = 0;
	int idOldSectorToUpdate = 0;
	for (int i = 1; i < numWaypointsFlight; i++) {
		WaypointRoute *currentWR = flight->getListWaypointsRoute()[PathIdWaypointsRoute[i]];
		//if is waypoint end (1), stop
		if (currentWR->getId() == 1) {
			break;
		}

		else {

			int newInstantFlight = currentWR->getInTime();

			string nameSector = currentWR->getWaypointFather()->getSector1();

			int idSectorToUpdate = this->getIdSectorByName(nameSector);

//			cout << "En el instante " << newInstantFlight << " estoy en el "
//					<< flight->getListWaypointsRoute()[idPaths[i]]->getCompleteName() << " y sectores"
//					<< idSectorToUpdate << endl;

			//update times between waypoints
			this->updateTimesBetweenWaypoints(lastInstantFlight, newInstantFlight, idOldSectorToUpdate);

			lastInstantFlight = newInstantFlight;
			idOldSectorToUpdate = idSectorToUpdate;
//			cout << "*********En el instante " << newInstantFlight << " ++ en sector" << idSectorToUpdate << endl;

			//airpots has no capacity
			if (!currentWR->isAirport())
				_timeMomentlist[newInstantFlight]->getNumFlightsSector()[idSectorToUpdate]++;
		}

	}

}

// update timeMomentList in periods flight is traveling between waypoints
void Problem::updateTimesBetweenWaypoints(int lastInstantFlight, int newInstantFlight, int idOldSectorToUpdate) {

	for (int i = lastInstantFlight + 1; i < newInstantFlight; i++) {
		//	cout << "*********En el instante " << i << " ++ en sector" << idOldSectorToUpdate << endl;
		_timeMomentlist[i]->getNumFlightsSector()[idOldSectorToUpdate]++;

	}

}

int Problem::sectorIsFreeAtTime(int time, string sectorName) {
	int sectorIsFree = 0;
	if (_timeMomentlist[time]->getNumFlightsSector()[getIdSectorByName(sectorName)] == 0) {
		sectorIsFree = 1;
	}
	return sectorIsFree;
}

int Problem::conditionDjistraByOption(int option, int inTime, string sectorWaypointRoute, int isAirport) {
	int resultCondition = 0;
	switch (option) {
		case OPTION_ONLY_INITIAL_SOLUTION:
			resultCondition = (sectorIsFreeAtTime(inTime, sectorWaypointRoute) || isAirport);
			break;

		case OPTION_SHORTEST_PATH:
			resultCondition = 1;
			break;
	}
	return resultCondition;
}

void Problem::createRoutes(Flight *flight) {
	int newPosition = 2;
	int size = 1000;
	int numWaypoints = flight->getAllWaypointsFlight();
//	cout << "el flight con id " << flight->getId() << " tiene " << numWaypoints << endl;
	WaypointRoute **waypointsRoute = new WaypointRoute*[size];

	int cont = 0;
	string seqArray[numWaypoints];
	string pointsArray[numWaypoints + 1];
	string timesMin[numWaypoints];
	string timesMax[numWaypoints];

//2 por el start y el end
	int num = 2;
	int **matrix = (int **) malloc(size * sizeof(int*));

	for (int i = 0; i < size; i++) {
		matrix[i] = (int *) malloc(size * sizeof(int));

	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = -1;

		}
	}

	//Creamos nodos inicio y fin
	WaypointRoute *start = new WaypointRoute(0, flight->getTimeStart(), getWaypointById(flight->getIdWaypointStart()));

	WaypointRoute *end = new WaypointRoute(1, 0, getWaypointById(flight->getIdWaypointEnd()));

	waypointsRoute[0] = start;
	waypointsRoute[1] = end;

	ifstream fe("./Resources/medium1/trajectories.csv");
	std::string line;

	while (std::getline(fe, line)) {
		string array[7];
		int i = 0;
		stringstream ssin(line);
		while (ssin.good() && i < 7) {
			ssin >> array[i];
			++i;
		}
		if (atoi(array[0].c_str()) == flight->getId()) {
			seqArray[cont] = array[2];
			pointsArray[cont] = array[3];
			timesMin[cont] = array[4];
			timesMax[cont] = array[6];
			flight->setNumRoutes(atoi(array[1].c_str()));

			if (array[3] == getWaypointById(flight->getIdWaypointStart())->getName()) {
				//Es el nodo de salida
				for (int i = 0; i <= flight->getGroundDelay(); i++) {

					//Actualizo matriz de costes
					matrix[i + num][0] = i;

					//Actualizo lista de waypointsRoute
					WaypointRoute *w = new WaypointRoute(newPosition, i, getWaypointById(flight->getIdWaypointStart()));
					waypointsRoute[newPosition] = w;

					newPosition++;
				}
			}
			cont++;
		}
	}

	int numWaypointsList = newPosition;

	for (int numRoutes = 0; numRoutes < flight->getNumRoutes(); numRoutes++) {
		//cout << "RONAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
		for (int i = 1; i < numWaypoints; i++) {

			string actualSeq = seqArray[i];
			string oldSeq = seqArray[i - 1];
			string actualPoint;
			string oldPoint;

			if (atoi(actualSeq.c_str()) > atoi(oldSeq.c_str())) {
//				cout << "*******Hay que unir " << pointsArray[i - 1] << " ("
//						<< this->getIdWaypointByName(pointsArray[i - 1])
//						<< ") con " << pointsArray[i] << " ("
//						<< this->getIdWaypointByName(pointsArray[i])
//						<< ") y coste de " << timesMin[i] << " a "
//						<< timesMax[i] << "***" << endl;

				int numNodesToAnalize = numWaypointsList;

				for (int j = 2; j < numNodesToAnalize; j++) {

					if (waypointsRoute[j]->getWaypointFather()->getId()
							== this->getIdWaypointByName(pointsArray[i - 1])) {
//
//						cout << "NUEVO NODO DE SALIDA DETECTADO: el " << j
//								<< endl;
//						cout << "En la lista hay " << numWaypointsList
//								<< " nodos" << endl;

//Creo un nodo por cada posible tiempo
						int timeMax = atoi(timesMax[i].c_str());
						int timeMin = atoi(timesMin[i].c_str());

						for (int times = timeMin; times <= timeMax; times++) {

//							cout << "Miro si existe un WR con padre "
//									<< pointsArray[i] << " y time del padre "
//									<< times + waypointsRoute[j]->getInTime()
//									<< endl;

							int position = isWaypointRouteInList(waypointsRoute, getIdWaypointByName(pointsArray[i]),
									times + waypointsRoute[j]->getInTime(), numWaypointsList);
							if (position == -1) {
//								cout << "---->Creo un waypoint con id "
//										<< numWaypointsList << "y intime "
//										<< times
//												+ waypointsRoute[j]->getInTime()
//										<< " y padre "
//										<< getWaypointById(
//												getIdWaypointByName(
//														pointsArray[i]))->getId()
//										<< endl;

								WaypointRoute *w = new WaypointRoute(numWaypointsList,
										times + waypointsRoute[j]->getInTime(),
										getWaypointById(getIdWaypointByName(pointsArray[i])));
								waypointsRoute[numWaypointsList] = w;

//								cout << "pongo un " << atoi(timesMin[i].c_str())
//										<< " en " << waypointsRoute[j]->getId()
//										<< "," << numWaypointsList << endl;
								matrix[numWaypointsList][waypointsRoute[j]->getId()] = atoi(timesMin[i].c_str());
								numWaypointsList++;
							} else {
//								cout << "-->WAYPOINT YA EXISTENTE" << endl;
//								cout << "pongo un " << atoi(timesMin[i].c_str())
//										<< " en " << waypointsRoute[j]->getId()
//										<< "," << position << endl;
								matrix[position][waypointsRoute[j]->getId()] = atoi(timesMin[i].c_str());
							}

						}
					}

				}

				actualPoint = pointsArray[i + 1];
				oldPoint = pointsArray[i];
			}

			else {
				actualPoint = pointsArray[i + 2];
				oldPoint = pointsArray[i + 1];
			}
		}
	}

//Unir los destino prima al aeropuerto
	for (int v = 0; v < numWaypointsList; v++) {
		if (waypointsRoute[v]->getWaypointFather()->getId() == flight->getIdWaypointEnd() && v != 1) {

			matrix[1][v] = 0;
		}
	}
	for (int i = 0; i < numWaypointsList; i++) {
		for (int j = 0; j < numWaypointsList; j++) {
			if (matrix[i][j] == -1) {
				matrix[i][j] = 1000;

			}

		}

	}
//	cout << " vuelo " << flight->getId() << endl;
//	cout << "EL TAMAÑO ES :" << numWaypointsList << endl;
	flight->setNumWaypointsRoute(numWaypointsList);
//	cout << "el retardo del vuelo es de " << flight->getGroundDelay() << endl;
//	cout << "rutas " << flight->getNumRoutes() << endl;
//	printMatrixInt(matrix, flight->getNumWaypointsRoute());
	flight->setRoutes(matrix);
	flight->setListWaypointsRoute(waypointsRoute);

}

int Problem::isWaypointRouteInList(WaypointRoute **list, int idFather, int inTime, int sizeList) {
	int position = -1;
	for (int i = 0; i < sizeList; i++) {
		if (list[i]->isSameWaypointRoute(inTime, idFather)) {
			position = i;
			break;
		}

	}
//cout << "SACO " << position << endl;
	return position;
}

