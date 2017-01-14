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
#include <algorithm>    // std::for_each
#include <map>

#include <limits> // for numeric_limits

#include <queue>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

#include "Pathfinder.h"
#include "Utilities.h"

Problem::Problem() {

}

Problem::~Problem() {
	// TODO Auto-generated destructor stub
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
//	cout << "crea los sectores" << endl;
	createSectors();

	//cout << "crea los waypoints" << endl;
	createWaypoints();

	//cout << "crea los flights" << endl;
	createFlights();

	//cout << "crea los times" << endl;
	createTimes();

	//cout << "crea las rutas" << endl;
	createAllRoutes();

	//cout << "crea los order" << endl;
	createOrderFlights();

}

/**
 * Find flights with no problems and remove it from problem
 */
void Problem::initialValidations() {
	cout << "busca los unconnected" << endl;
	this->getFlightsUnconnected();

	cout << "calcula el camino más corto para cada vuelo" << endl;
	this->getInitialShortestRoutes();

//	cout << "busca los sobrecargados iniciales" << endl;
//	this->getInitialOverloadSectors();

//	for (int i = 0; i < 15; i++) {
//		cout << "****EN " << i << endl;
//		printArrayInt(_timeMomentlist[i]->getNumFlightsSector(), this->getNumSectors());
//	}
}

void Problem::getInitialShortestRoutes() {
	for (int i = 0; i < this->getNumFlights(); i++) {
		Djistra(_listFlights[i], OPTION_SHORTEST_PATH);
	}

//PRUEBAS
//	Djistra(_listFlights[0], OPTION_SHORTEST_PATH);
//	Djistra(_listFlights[1], OPTION_SHORTEST_PATH);
//	Djistra(_listFlights[20], OPTION_SHORTEST_PATH);
//	Djistra(_listFlights[21], OPTION_SHORTEST_PATH);

}

/**
 * Step 1: take off flights in random order. No alternative ways and no delays considered
 */
void Problem::initialFlightsTakeOff() {
	for (int i = 0; i < this->getNumFlights(); i++) {
		int currentPosition = this->_orderFlights[i];
		Djistra(_listFlights[i], OPTION_ONLY_INITIAL_SOLUTION);
	}

//PRUEBAS
//	Djistra(_listFlights[0], OPTION_ONLY_INITIAL_SOLUTION);
//	Djistra(_listFlights[1], OPTION_ONLY_INITIAL_SOLUTION);
//	Djistra(_listFlights[20], OPTION_ONLY_INITIAL_SOLUTION);
//	Djistra(_listFlights[21], OPTION_ONLY_INITIAL_SOLUTION);

}
/**
 * Try to interchange a bad
 */
void Problem::interchangeFlights() {
	cout << "ANTES DE INTERCAMBIO" << endl;
	printAllFlightStatus();

	//list of pairs with status,ok flight candidates that block a cancel flight
	map<int, vector<int> > mapCanceledFlight_flightsBlockIt;

	for (int i = 0; i < this->getNumFlights(); i++) {
		if (_listFlights[i]->getStatus() == FLIGHT_STATUS_CANCELED) {
			//Step 1: create candidates for each flight in time
			vector<int> candidates = createFlightCandidatesInterchange(_listFlights[i]);

			mapCanceledFlight_flightsBlockIt[_listFlights[i]->getId()] = candidates;
			cout << "el vuelo cancelado " << _listFlights[i]->getId() << " tiene " << candidates.size()
					<< " candidatos (";
			printVectorInt(candidates);
			cout << ") con solución inicial ok" << endl;
		}
	}

	//Step 2: filter flights ok that blocks >1 cancel flights
	map<int, vector<int> > mapFiltered = filterFlightsBlokcMore1(mapCanceledFlight_flightsBlockIt);

	//Step 3: try to interchange an ok flight for 2 or more refused flights
	int numInterchnges = tryAllInterchanges(mapFiltered);

	cout << "DESPUES DE INTERCAMBIO" << endl;
	printAllFlightStatus();
}

void Problem::flightsTakeOffWithDelays() {
//launch flights in random order
	for (int i = 0; i < this->getNumFlights(); i++) {
		if (_listFlights[i]->getStatus() == -1) {
			Djistra(_listFlights[i], OPTION_ONLY_DELAYS);

		}
	}
	cout << "DESPUES DE RETRASOS" << endl;
	printAllFlightStatus();
}

void Problem::flightsTakeOffAlternativeRoutes() {
	for (int i = 0; i < this->getNumFlights(); i++) {
		if (_listFlights[i]->getStatus() == -1) {
			Djistra(_listFlights[i], OPTION_ALTERNATIVE_ROUTES);

		}
	}
	cout << "DESPUES DE RUTAS ALTERNATIVAS" << endl;
	printAllFlightStatus();
}

void Problem::createOrderFlights() {
	std::srand(unsigned(std::time(0)));
	std::vector<int> myvector;

	// set some values:
	for (int i = 0; i < this->getNumFlights(); ++i)
		myvector.push_back(i);

	// using built-in random generator:
	std::random_shuffle(myvector.begin(), myvector.end());
	this->_orderFlights = myvector;

	// print out content:
//	std::cout << "my vector contains:";
//	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
//		std::cout << ' ' << *it;

}

void Problem::createTimes() {
	int maxSize = 100;
	_timeMomentlist = new TimeMoment*[maxSize];
	cout << "creando times... " << endl;

	for (int id = 0; id < maxSize; id++) {
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

Flight* Problem::getFlightById(int id) {
	Flight *f;
	for (int i = 0; i < this->getNumFlights(); i++) {
		if (_listFlights[i]->getId() == id) {
			f = _listFlights[i];
			break;
		}
	}
	return f;
}

WaypointRoute* Problem::getWRById(Flight *f, int id) {
	WaypointRoute *wr;
	for (int i = 0; i < f->getNumWaypointsRoute(); i++) {
		if (f->getListWaypointsRoute()[i]->getId() == id) {
			wr = f->getListWaypointsRoute()[i];
			break;
		}
	}
	return wr;
}

void Problem::printAllFlightStatus() {
	for (int i = 0; i < this->getNumFlights(); i++) {
		Flight *f = _listFlights[i];
		f->printStatus();
	}
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
	int id = -1;
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

		Sector *newSector = new Sector(cont, (array[0]), 1);
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
			Sector *s = getSectorByName(auxSector);
			Waypoint *newWaypoint = new Waypoint(cont, array[0], s);
			if (array[0][0] == 'A') {
				newWaypoint->setIsAirport(1);
			}
			_listWaypoints[cont] = newWaypoint;

		}
		//Waypoint already in list
		else {
			//_listWaypoints[posOld]->setSector2(auxSector);
			cont--;
		}

		cont++;
	}

	this->setNumWaypoints(cont);
	fe.close();

}

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

vector<string> Problem::getUniqueWaypointsRouteByFlight(Flight *flight) {
	vector<string> flightWaypointRouteNames;
	for (int i = 0; i < flight->getNumWaypointsRoute(); i++) {
		WaypointRoute *currentWaypointRoute = flight->getWRById(i);
		flightWaypointRouteNames.push_back(currentWaypointRoute->getName());
	}

//Remove duplicates from vector
	flightWaypointRouteNames = removeDuplicatesVectorString(flightWaypointRouteNames);
	return flightWaypointRouteNames;
}

//Actualizar el nº de vuelos por sector en tiempo t.
// Si option=1, suma. Si option =-1, resta
void Problem::updateTimeSector(vector<int> PathIdWaypointsRoute, Flight *flight, int option) {

	//cout << "el vuelo " << flight->getId() << " empieza en " << flight->getTimeStart() << endl;
	for (int i = 1; i < PathIdWaypointsRoute.size(); i++) {
		WaypointRoute *currentWR = flight->getWRById(PathIdWaypointsRoute[i]);
		WaypointRoute *previousWR = flight->getWRById(PathIdWaypointsRoute[i - 1]);

		for (int j = previousWR->getInTime(); j < currentWR->getInTime(); j++) {
			string nameSector = previousWR->getWaypointFather()->getSector1()->getName();
			int idSector = getIdSectorByName(nameSector);
//			cout << "añado 1 al sector" << nameSector << " del wr " << previousWR->getId() << " en instante "
//					<< j << endl;
			if (option > 0) {
				_timeMomentlist[j]->getNumFlightsSector()[idSector]++;
			} else {
				_timeMomentlist[j]->getNumFlightsSector()[idSector]--;
			}
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

int Problem::conditionDjistraByOption(int option, int inTime, WaypointRoute *currentWaypointRoute, vector<int> v) {
	int resultCondition = 0;
	std::string nameWaypointRoute = currentWaypointRoute->getCompleteName();
	std::string sectorWaypointRoute = currentWaypointRoute->getWaypointFather()->getSector1()->getName();
	int isAirport = currentWaypointRoute->getWaypointFather()->getIsAirport();

	switch (option) {
		case OPTION_ONLY_INITIAL_SOLUTION:
			caseOPTION_ALTERNATIVE_ROUTES: resultCondition = (sectorIsFreeAtTime(inTime, sectorWaypointRoute)
					|| isAirport);
			break;

		case OPTION_SHORTEST_PATH:
			resultCondition = 1;
			break;
		case OPTION_ONLY_DELAYS:
			int currentWaypointId = currentWaypointRoute->getWaypointFather()->getId();
			bool inWaypointsIncluded = checkVectorContainsElement(v, currentWaypointId);
			resultCondition = (sectorIsFreeAtTime(inTime, sectorWaypointRoute) || isAirport) && inWaypointsIncluded;
			break;
	}
	return resultCondition;
}

void Problem::createRoutes(Flight *flight) {
	int newPosition = 2;
	int numWaypoints = flight->getAllWaypointsFlight();
	WaypointRoute **waypointsRoute = new WaypointRoute*[1000];

	int cont = 0;
	string seqArray[numWaypoints];
	string pointsArray[numWaypoints + 1];
	string timesMin[numWaypoints];
	string timesMax[numWaypoints];

	//2 por el start y el end
	int num = 2;
	int **matrix = initializeMatrixRoutes();

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
					WaypointRoute *w = new WaypointRoute(newPosition, i + flight->getTimeStart(),
							getWaypointById(flight->getIdWaypointStart()));
					waypointsRoute[newPosition] = w;

					newPosition++;
				}
			}
			cont++;
		}
	}

	int numWaypointsList = newPosition;

	for (int numRoutes = 0; numRoutes < flight->getNumRoutes(); numRoutes++) {
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

						//Creo un nodo por cada posible tiempo
						int timeMax = atoi(timesMax[i].c_str());
						int timeMin = atoi(timesMin[i].c_str());

						for (int times = timeMin; times <= timeMax; times++) {
							int currentPostion = times + waypointsRoute[j]->getInTime();
							int position = isWaypointRouteInList(waypointsRoute, getIdWaypointByName(pointsArray[i]),
									currentPostion, numWaypointsList);
							if (position == -1) {
								WaypointRoute *w = new WaypointRoute(numWaypointsList,
										times + waypointsRoute[j]->getInTime(),
										getWaypointById(getIdWaypointByName(pointsArray[i])));
								waypointsRoute[numWaypointsList] = w;

								matrix[numWaypointsList][waypointsRoute[j]->getId()] = timeMin;
								numWaypointsList++;
							}
							//Waypoint already exists
							else {
								matrix[position][waypointsRoute[j]->getId()] = timeMin;
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

	this->setProblemRouteAttributes(flight, matrix, numWaypointsList, waypointsRoute);
}

void Problem::setProblemRouteAttributes(Flight *flight, int **matrix, int numWaypointsList,
		WaypointRoute **waypointsRoute) {

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
	flight->setNumWaypointsRoute(numWaypointsList);
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
	return position;
}

bool Problem::solutionHasValidSectors(vector<int> vectorWaypointsRoute, Flight *flight) {
	bool result = true;

	for (int i = 1; i < vectorWaypointsRoute.size(); i++) {
		WaypointRoute *currentWR = flight->getWRById(vectorWaypointsRoute[i]);
		WaypointRoute *previousWR = flight->getWRById(vectorWaypointsRoute[i - 1]);

		for (int j = previousWR->getInTime(); j < currentWR->getInTime(); j++) {
			int idSector = previousWR->getIdSector();
//			cout << "miro si está libre el sector" << nameSector << " del wr " << previousWR->getId() << " en instante "
//					<< j << endl;
			int flightsInSector = _timeMomentlist[j]->getNumFlightsSector()[idSector];
			if (flightsInSector > 0)
				return false;

		}
	}
	return result;
}

//Given a cancel flight, return list of ok flights to interchange
vector<int> Problem::createFlightCandidatesInterchange(Flight *flightCancel) {
	std::vector<int> candidates;
	//foreach canceled flight, check if share at least one WR on same time
	for (int i = 0; i < this->getNumFlights(); i++) {
		Flight *currentFlight = _listFlights[i];
		if (currentFlight->getStatus() == 1) {
			bool isCandidate = checkFlightsShareSectorInTime(flightCancel, currentFlight);
			if (isCandidate) {
//				cout << "El " << currentFlight->getId() << " es candidato del cancelado " << flightCancel->getId()
//						<< endl;
				candidates.push_back(currentFlight->getId());
			}
		}
	}
	return candidates;
}

bool Problem::checkFlightsShareSectorInTime(Flight *originalCanceled, Flight *candidate) {
	//cout << "******comparo el cancelado " << originalCanceled->getId() << " con el ok " << candidate->getId() << endl;

	vector<int> originalSolution = originalCanceled->getIntialSolution();
	//foreach WR in original
	for (std::vector<int>::iterator eachWRId = originalSolution.begin(); eachWRId != originalSolution.end();
			++eachWRId) {
//		cout << *eachWRId << " del " << candidate->getId() << endl;
		WaypointRoute *currentWR = originalCanceled->getWRById(*eachWRId);

		if (!currentWR->isAirport()) {
			int inTimeOriginal = currentWR->getInTime();
			int idSectorOriginal = currentWR->getIdSector();
			std::pair<int, int> orinalPair(inTimeOriginal, idSectorOriginal);
			bool pairFound = existsPairWRInFlight(orinalPair, candidate);
			// is any pair is not found, return false
			if (!pairFound) {
				return false;
			}
		}
	}
	return true;
}

bool Problem::existsPairWRInFlight(pair<int, int> orinalPair, Flight *candidate) {
	bool pairFound = false;

	vector<int> candidateSolution = candidate->getIntialSolution();

//	cout << "----BUSCO el sector " << orinalPair.first << " en timepo " << orinalPair.second << endl;
//check if any WR of candidate has same sector and in time
	for (std::vector<int>::iterator it = candidateSolution.begin(); it != candidateSolution.end(); ++it) {
		WaypointRoute *candidateWR = candidate->getWRById(*it);
		if (!candidateWR->isAirport()) {
			int inTimeCadidate = candidateWR->getInTime();
			int idSectorCandidate = candidateWR->getIdSector();
			std::pair<int, int> candidatePair(inTimeCadidate, idSectorCandidate);
			//	cout << "--------->Miro el sector " << idSectorCandidate << " en timepo " << inTimeCadidate << endl;

			if (candidatePair == orinalPair) {
				//	cout << "el " << *it << " del " << candidate->getId() << " SIIIIIIIIIIIIII coincide! con el " << endl;
				pairFound += true;
				break;
			} else {
				//	cout << "el " << *it << " del " << candidate->getId() << " NOOO coincide!" << endl;
			}
		}
	}
	return pairFound;
}

//return ok flight that blocks more than 1 cancel flights
map<int, vector<int> > Problem::filterFlightsBlokcMore1(map<int, vector<int> > candidates) {
	map<int, vector<int> > resultFiltered;
	vector<int> candidatesAnalyzed;
	//foreach result in map
	for (map<int, vector<int> >::iterator eachResult = candidates.begin(); eachResult != candidates.end();
			++eachResult) {
		vector<int> currentCandidates = eachResult->second;
		//for each candidate
		for (vector<int>::iterator eachCandidate = currentCandidates.begin(); eachCandidate != currentCandidates.end();
				++eachCandidate) {

			// if candidate hasnt been analyzed yet
			if (find(candidatesAnalyzed.begin(), candidatesAnalyzed.end(), *eachCandidate)
					== candidatesAnalyzed.end()) {
				vector<int> flightsThatBlock = getFlightsThatBlocks(*eachCandidate, candidates);
				cout << "El vuelo " << *eachCandidate << " está bloqueando " << flightsThatBlock.size()
						<< " vuelos cancelados que son ";
				printVectorInt(flightsThatBlock);
				cout << endl;
				//If flight COULD enable 2 or more flights
				if (flightsThatBlock.size() > 0)
					resultFiltered[*eachCandidate] = flightsThatBlock;
			}
			candidatesAnalyzed.push_back(*eachCandidate);
		}
	}
	return resultFiltered;
}

int Problem::tryAllInterchanges(map<int, vector<int> > FlightOKAndCandidates) {
	int numInterchanges = 0;

	//try interchange for each flight
	for (map<int, vector<int> >::iterator eachResult = FlightOKAndCandidates.begin();
			eachResult != FlightOKAndCandidates.end(); ++eachResult) {
		int flightId = eachResult->first;
		vector<int> candidates = eachResult->second;
		bool succesFullInterchange = tryInterchange(flightId, candidates);
		if (succesFullInterchange)
			numInterchanges++;

	}
	return numInterchanges;
}

bool Problem::tryInterchange(int flightId, vector<int> candidates) {
	bool successfullInterchange = false;

	cout << "intento cambiar el " << flightId << " por alguno de" << endl;
	printVectorInt(candidates);
	cout << endl;

	//Get minimun number of sectors
	int minSize = getMinValueFomVector(candidates);

	int numSectorIS = getFlightById(flightId)->getIdSectorsIS().size();

	//if we can take at least 2 flights to interchange
	if (minSize * 2 <= numSectorIS) {
		//get all solution that has more flights
		vector<int> allSolutions = getSolutionInterchangeFlights(flightId, candidates, numSectorIS / 2);
		if (allSolutions.size() > 1) {
			successfullInterchange = changeFlightForCandidates(flightId, allSolutions);
		}
	} else {
		successfullInterchange = false;
	}
	return successfullInterchange;
}

vector<int> Problem::getSolutionInterchangeFlights(int flightId, vector<int> candidates, int maxSize) {
	vector<int> candidatesSelected;
	vector<int> sectorsToGet = getFlightById(flightId)->getIdSectorsIS();
	vector<int> candidatesCopy = candidates;
	//shuffle vector candidates
	std::random_shuffle(candidatesCopy.begin(), candidatesCopy.end());

	//get all combination of solutions
	for (vector<int>::iterator it = candidatesCopy.begin(); it != candidatesCopy.end(); ++it) {
		//if there are no more sectors free, stop
		if (sectorsToGet.empty()) {
			break;
		}
//		cout << "el " << *it << " tiene SI ";
		vector<int> idSectorCandidate = getFlightById(*it)->getIdSectorsIS();
//		printVectorInt(idSectorCandidate);
//		cout << endl;
		if (idSectorCandidate.size() <= maxSize) {
			//if there are availabe all sectors of ok flight
			if (vectorContainsAllValues(sectorsToGet, idSectorCandidate)) {
//				printVectorInt(idSectorCandidate);
//				cout << "está en ";
//				printVectorInt(sectorsToGet);
//				cout << endl;
				//remove from available sector which candidate use it
				sectorsToGet = removeElementsFromVector(sectorsToGet, idSectorCandidate);
				//	cout << "después de borrar queda";

//				printVectorInt(sectorsToGet);
//				cout << endl;

				candidatesSelected.push_back(*it);
				//	cout << "AÑADO EL" << *it << endl;
			} else {
				//	cout << "NO ESTA LIBRE :(" << endl;
			}
		}
	}
	return candidatesSelected;
}

bool Problem::changeFlightForCandidates(int flightId, vector<int> solutions) {
	Flight *original = getFlightById(flightId);
	//cancel flight
	cancelFlight(original, original->getIntialSolution());

	//launch each candidate

	for (vector<int>::iterator it = solutions.begin(); it != solutions.end(); ++it) {
		Flight *f = getFlightById(*it);
		setFlightOk(f, f->getIntialSolution());
	}

	//check there are no conflicts
	bool result = sectorCapacitiesAreOk(solutions);

	//if is not a valid solution, go back to previous state
	if (!result) {
		setFlightOk(original, original->getIntialSolution());
		for (vector<int>::iterator it = solutions.begin(); it != solutions.end(); ++it) {
			Flight *f = getFlightById(*it);
			cancelFlight(f, f->getIntialSolution());
		}
	} else {
		cout << "SOLUCION VALIDA!!!. Cambio el " << flightId << " por ";
		printVectorInt(solutions);
		cout << endl;
	}
	return result;
}

void Problem::cancelFlight(Flight* f, vector<int> path) {
	updateTimeSector(path, f, -1);
	f->setStatus(-1);
}

void Problem::setFlightOk(Flight* f, vector<int> path) {
	updateTimeSector(path, f, 1);
	f->setCurrentSolution(path);
	f->setStatus(1);
}

void Problem::setFlightDelayed(Flight* f, vector<int> path) {
	updateTimeSector(path, f, 1);
	f->setCurrentSolution(path);
	f->setStatus(2);
}

void Problem::setFlightAlternativeRoute(Flight* f, vector<int> path, int newDuration) {
	updateTimeSector(path, f, 1);
	f->setCurrentSolution(path);

	//alternative route and delayed
	if (newDuration > f->getTimeFinish()) {
		f->setStatus(4);
	}
	//alternative route but same or better time
	else {
		f->setStatus(3);
	}
}

//
bool Problem::sectorCapacitiesAreOk(vector<int> solutions) {
//get max and min inTIme of solutions
	pair<int, int> minMaxTimes = getMinMaxTimeWR(solutions, this);
	for (int i = minMaxTimes.first; i <= minMaxTimes.second; i++) {
		for (int sector = 0; sector < getNumSectors(); sector++) {
			if (_timeMomentlist[i]->getNumFlightsSector()[sector] > 1) {
				return false;
			}
		}
	}
	return true;
}

vector<int> Problem::getIdWaypointsInIS(Flight *flight) {
	vector<int> waypointIds;
	vector<int> initialSolution = flight->getIntialSolution();

	for (vector<int>::iterator it = initialSolution.begin(); it != initialSolution.end(); ++it) {
		waypointIds.push_back(getWRById(flight, *it)->getWaypointFather()->getId());
	}
	return waypointIds;
}

int Problem::getNumFlightsNoCanceled() {
	int flightsNoCancel = 0;
	for (int i = 0; i < this->getNumFlights(); i++) {
		if (!_listFlights[i]->isCanceled())
			flightsNoCancel++;
	}
	return flightsNoCancel;
}

void Problem::writeFileForHTML() {
	createFileSectors();
	createFileFlights();
}

void Problem::createFileSectors() {
	std::ofstream outfile("waypoints.txt");
	for (int i = 0; i < getNumWaypoints(); i++) {
		Waypoint *w = _listWaypoints[i];
		outfile << w->getId() << " " << w->getName() << std::endl;
	}
	outfile.close();

}

void Problem::createFileFlights() {
	std::ofstream outfile("flights.txt");
	for (int i = 0; i < getNumFlights(); i++) {
		Flight *f = _listFlights[i];
		if (!f->isCanceled()) {
			cout << "entro" << endl;
			vector<int> solution = f->getCurrentSolution();
			cout << "salgo" << endl;
			printVectorInt(solution);
			cout << endl;
			if (!solution.empty()) {

				for (int j = 0; j < solution.size() - 1; j++) {
					Waypoint *w1 = getWRById(f, solution[j])->getWaypointFather();
					Waypoint *w2 = getWRById(f, solution[j + 1])->getWaypointFather();
					int id1 = w1->getId();
					int id2 = w2->getId();
					string name1 = w1->getName();
					string name2 = w2->getName();

					outfile << f->getId() << " " << id1 << " " << name1 << " " << id2 << " " << name2 << std::endl;
				}
			}
		}
	}
	outfile.close();
}

