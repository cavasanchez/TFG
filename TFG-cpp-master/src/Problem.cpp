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
#include <stdio.h>
#include <string.h>
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
	_numTimes = 1000;
	_iteration = 0;
	_valueBestSolution = 0;
}

/*
 * inicializa los datos del problema
 */
void Problem::inizializeProblem(int numSimulation) {
	createSectors();

	createWaypoints();

	createFlights();

	createAllRoutes();

	createTimes();

	createFileResult(numSimulation);
}

void Problem::createFileResult(int numSimuation) {

	char *nameFile = "./Outputs/numSimuation.txt";

	//only when file is not created yet
	if (!std::ifstream(nameFile)) {
//		std::cout << "File already exists" << std::endl;

		std::ofstream outfile(nameFile);
		if (!outfile) {
			std::cout << "File could not be created" << std::endl;
			exit(1);
		}

		outfile << "simulation;iteration;value_solution" << endl;

		this->setRouteFileResults("./Outputs/numSimuation.txt");
	}
}

/**
 * Find flights with no problems and remove it from problem
 */
void Problem::initialSolutions() {
//	cout << "busca los unconnected" << endl;
	this->getFlightsUnconnected();

//	cout << "calcula el camino más corto para cada vuelo" << endl;
	this->getInitialShortestRoutes();
}

void Problem::getInitialShortestRoutes() {
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
		if (_listFlights[currentPosition]->getStatus() == FLIGHT_STATUS_NOT_LAUNCHED) {
			Djistra(_listFlights[currentPosition], OPTION_ONLY_INITIAL_SOLUTION);
		}
	}
}
/**
 * Try to interchange a bad
 */
void Problem::interchangeFlights() {

//list of pairs with status,ok flight candidates that block a cancel flight
	map<int, vector<int> > mapCanceledFlight_flightsBlockIt;

	for (int i = 0; i < this->getNumFlights(); i++) {
		if (_listFlights[i]->getStatus() == FLIGHT_STATUS_CANCELED) {
			//Step 1: create candidates for each flight in time
			vector<int> candidates = createFlightCandidatesInterchange(_listFlights[i]);

			mapCanceledFlight_flightsBlockIt[_listFlights[i]->getId()] = candidates;
//			cout << "el vuelo cancelado " << _listFlights[i]->getId() << " tiene " << candidates.size()
//					<< " candidatos (";
//			printVectorInt(candidates);
//			cout << ") con solución inicial ok" << endl;
		}
	}

	//Step 2: filter flights ok that blocks >1 cancel flights
	map<int, vector<int> > mapFiltered = filterFlightsBlokcMore1(mapCanceledFlight_flightsBlockIt);

	//Step 3: try to interchange an ok flight for 2 or more refused flights
	int numInterchnges = tryAllInterchanges(mapFiltered);

//	cout << "---------- DESPUES DE INTERCAMBIO ----------" << endl;
//	printAllFlightStatus();
}

void Problem::flightsTakeOffWithDelays() {
	srand(time(0));
	random_shuffle(_orderFlights.begin(), _orderFlights.end());

	//launch flights in random order
	for (int i = 0; i < this->getNumFlights(); i++) {
		int currentPosition = this->_orderFlights[i];
		if (_listFlights[currentPosition]->getStatus() == FLIGHT_STATUS_CANCELED) {
			Djistra(_listFlights[currentPosition], OPTION_ONLY_DELAYS);
		}
	}
}

void Problem::flightsTakeOffAlternativeRoutes() {
	srand(time(0));
	random_shuffle(_orderFlights.begin(), _orderFlights.end());

	//launch flights in random order
	for (int i = 0; i < this->getNumFlights(); i++) {
		int currentPosition = this->_orderFlights[i];
		if (_listFlights[currentPosition]->getStatus() == FLIGHT_STATUS_CANCELED) {
			Djistra(_listFlights[currentPosition], OPTION_ALTERNATIVE_ROUTES);
		}
	}

//	cout << "---------- DESPUES DE RUTAS ALTERNATIVAS ----------" << endl;
//	printAllFlightStatus();
}

void Problem::createOrderFlights(vector<int> listFlights) {

	srand(time(0));
	random_shuffle(listFlights.begin(), listFlights.end());
	listFlights = removeDuplicatesVectorIntWithoutSort(listFlights);
	this->_orderFlights = listFlights;
}

//get max in time in all flights
int Problem::getMaxInTime() {
	int result = 0;
	for (int i = 0; i < _numFlights; i++) {
		Flight *f = _listFlights[i];
		int numberWR = f->getNumWaypointsRoute();
		for (int j = 0; j < numberWR; j++) {
			WaypointRoute *wr = f->getListWaypointsRoute()[j];
			if (wr->getInTime() > result) {
				result = wr->getInTime();
			}
		}
	}
	return result;
}

void Problem::createTimes() {
//	int maxSize = this->getMaxInTime();
//	cout<<maxSize<<endl;
//	exit(1);
	int maxSize = _numTimes;

	_timeMomentlist = new TimeMoment*[maxSize];
//	cout << "creando times... " << endl;

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
	string s = RESORCES_FOLDER + "flights.csv";
	const char* route = s.c_str();

	ifstream fe(route);
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
	string s = RESORCES_FOLDER + "sectors.csv";
	const char* route = s.c_str();
	ifstream fe(route);
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

		Sector *newSector = new Sector(cont, (array[0]), CAPACITY_SECTOR);
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
	string s = RESORCES_FOLDER + "waypoints.csv";
	const char* route = s.c_str();
	ifstream fe(route);
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
			//	cout << "SACAMOS EL " << i << endl;
			_listFlights[i]->setStatus(2);
		}
	}
//	cout << endl;
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

int Problem::sectorIsFreeAtTime(int time, string sectorName, int incrementLimit) {
	int sectorIsFree = 0;
	if (_timeMomentlist[time]->getNumFlightsSector()[getIdSectorByName(sectorName)] == (0 - incrementLimit)) {
		sectorIsFree = 1;
	}
	return sectorIsFree;
}

int Problem::conditionDjistraByOption(int option, int inTime, WaypointRoute *currentWaypointRoute, vector<int> v,
		int idWaypointDestiny) {
	int resultCondition = 0;
	std::string nameWaypointRoute = currentWaypointRoute->getCompleteName();
	std::string sectorWaypointRoute = currentWaypointRoute->getWaypointFather()->getSector1()->getName();
	int isAirport = currentWaypointRoute->getWaypointFather()->getIsAirport();

	switch (option) {
		case OPTION_ONLY_INITIAL_SOLUTION:
		case OPTION_ALTERNATIVE_ROUTES:
			resultCondition = (sectorIsFreeAtTime(inTime, sectorWaypointRoute, 0) || isAirport);
			break;

		case OPTION_WITH_UNUSED_WAYPOINT:
			resultCondition = (sectorIsFreeAtTime(inTime, sectorWaypointRoute, 1) || isAirport);
			break;

		case OPTION_SHORTEST_PATH:
			resultCondition = 1;
			break;
		case OPTION_ONLY_DELAYS:

			int currentWaypointId = currentWaypointRoute->getWaypointFather()->getId();
			bool isWaypointsIncluded = checkVectorContainsElement(v, currentWaypointId);
			bool destinyIsIncluded = checkVectorContainsElement(v, idWaypointDestiny);
			bool noCapacityProblems = sectorIsFreeAtTime(inTime, sectorWaypointRoute, 0);
			bool isAnAirport = isAirport;
			resultCondition = (isWaypointsIncluded && destinyIsIncluded && noCapacityProblems) || isAnAirport;

//			cout << "Añado el " << currentWaypointRoute->getId() << "? " << resultCondition << "!";
//			if (!isWaypointsIncluded)
//				cout << " origen no incluído" << endl;
//			if (!destinyIsIncluded)
//				cout << "destino no incluído" << endl;
//
//			if (!noCapacityProblems)
//				cout << "sector lleno" << endl;
//
//			if (isAnAirport)
//							cout << "es aeropuerto" << endl;
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

	string s = RESORCES_FOLDER + "trajectories.csv";
	const char* route = s.c_str();
	ifstream fe(route);
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
//				cout << "El vuelo " << *eachCandidate << " está bloqueando " << flightsThatBlock.size()
//						<< " vuelos cancelados que son ";
//				printVectorInt(flightsThatBlock);
//				cout << endl;
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

//	cout << "intento cambiar el " << flightId << " por alguno de" << endl;
//	printVectorInt(candidates);
//	cout << endl;

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
	srand(time(0));
	random_shuffle(candidatesCopy.begin(), candidatesCopy.end());

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
//		cout << "SOLUCION VALIDA!!!. Cambio el " << flightId << " por ";
//		printVectorInt(solutions);
//		cout << endl;
	}
	return result;
}

void Problem::cancelFlight(Flight* f, vector<int> path) {
	updateTimeSector(path, f, -1);
	f->setStatus(FLIGHT_STATUS_CANCELED);
}

void Problem::setFlightOk(Flight* f, vector<int> path) {
	updateTimeSector(path, f, 1);
	f->setCurrentSolution(path);
	f->setStatus(FLIGHT_STATUS_IN_TIME);
}

void Problem::setFlightDelayed(Flight* f, vector<int> path) {
	updateTimeSector(path, f, 1);
	f->setCurrentSolution(path);
	f->setStatus(FLIGHT_STATUS_DELAYED);
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
//get max and min inTime of solutions
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

vector<int> Problem::getIdWRInIS(Flight *flight) {
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
	std::ofstream outfile("/home/carlos/DESARROLLO/waypoints.txt");
	for (int i = 0; i < getNumWaypoints(); i++) {
		Waypoint *w = _listWaypoints[i];
		outfile << w->getId() << " " << w->getName() << " " << w->getIsAirport() << " " << w->getSector1()->getId()
				<< endl;
	}
	outfile.close();
}

void Problem::createFileFlights() {
	std::ofstream outfile("/home/carlos/DESARROLLO/flights.txt");
	for (int i = 0; i < getNumFlights(); i++) {
		Flight *f = _listFlights[i];
		if (!f->isCanceled()) {
			vector<int> solution = f->getCurrentSolution();
			if (!solution.empty()) {

				for (int j = 0; j < solution.size() - 1; j++) {
					WaypointRoute *wr1 = getWRById(f, solution[j]);
					WaypointRoute *wr2 = getWRById(f, solution[j + 1]);

					Waypoint *w1 = wr1->getWaypointFather();
					Waypoint *w2 = wr2->getWaypointFather();
					int id1 = w1->getId();
					int id2 = w2->getId();
					string name1 = w1->getName();
					string name2 = w2->getName();

					if (id1 != id2)
						outfile << f->getId() << " " << id1 << " " << name1 << " " << id2 << " " << name2 << " "
								<< wr2->getInTime() << endl;
				}
			}
		}
	}
	outfile.close();
}

void Problem::printStatusProblem() {
	int numOK = 0;
	int numDelayed = 0;
	int numDeflected = 0;
	int numDeflectedAndDelayed = 0;
	int numCanceled = 0;
	int numError = 0;
	int numNotLaunched = 0;
	for (int i = 0; i < getNumFlights(); i++) {
		Flight *f = _listFlights[i];
		switch (f->getStatus()) {
			case FLIGHT_STATUS_ERROR:
				numError++;
				break;
			case FLIGHT_STATUS_CANCELED:
				numCanceled++;
				break;
			case FLIGHT_STATUS_NOT_LAUNCHED:
				numNotLaunched++;
				break;
			case FLIGHT_STATUS_IN_TIME:
				numOK++;
				break;
			case FLIGHT_STATUS_DELAYED:
				numDelayed++;
				break;
			case FLIGHT_STATUS_DEFLECTED:
				numDeflected++;
				break;
			case FLIGHT_STATUS_DELAYED_AND_DEFLECTED:
				numDeflectedAndDelayed++;
				break;
		}
	}
	cout << "/////// Resultado final: ///////" << endl;
	cout << "Vuelos sin despegar: " << numNotLaunched << endl;
	cout << "Vuelos con error: " << numError << endl;
	cout << "Vuelos cancelados: " << numCanceled << endl;
	cout << "Vuelos en tiempo previsto: " << numOK << endl;
	cout << "Vuelos retrasados: " << numDelayed << endl;
	cout << "Vuelos desviados pero en tiempo: " << numDeflected << endl;
	cout << "Vuelos desviados y retrasados: " << numDeflectedAndDelayed << endl;

}

void Problem::employUnusedWaypoints() {
	//first get unused waypoints in any time
	vector<int> unusedWaypoints = this->getUnusedWaypoints();
	vector<int> waypointsAlreadyMarked;

	//check if any landed flight has some of unused waypoints
	for (int i = 0; i < this->getNumFlights(); i++) {
		Flight *currentFlight = _listFlights[i];
		//if no canceled and contain some unused waypoints

		if (!currentFlight->isCanceled()) {
			int idWaypointUnused = currentFlight->getSomeWaypointUnused(unusedWaypoints, waypointsAlreadyMarked);

			if (idWaypointUnused > 0) {
				Waypoint *w = getWaypointById(idWaypointUnused);
//				cout << "El flight " << currentFlight->getId() << " pasa por uno sin usar que es " << w->getName()
//						<< endl;
				currentFlight->setWaypointNameToAvoid(w->getName());

//				vector<int> solutionWithWaypointUnused = getSolutionWithWaypoint(currentFlight, w);
				waypointsAlreadyMarked.push_back(idWaypointUnused);
				Djistra(currentFlight, OPTION_WITH_UNUSED_WAYPOINT);
			}
		}
	}
}

vector<int> Problem::getUnusedWaypoints() {
	vector<int> waypointsInSolution = getWaypointsInSolutions();
	vector<int> waypointsFree;
	for (int i = 0; i < this->getNumWaypoints(); i++) {
		int idWaypoint = _listWaypoints[i]->getId();
		bool isFree = !checkVectorContainsElement(waypointsInSolution, idWaypoint);
		if (isFree) {
			waypointsFree.push_back(idWaypoint);
		}
	}
	waypointsFree = removeDuplicatesVectorIntWithoutSort(waypointsFree);
	return waypointsFree;
}

vector<int> Problem::getWaypointsInSolutions() {
	vector<int> waypointsInSolution;

	for (int i = 0; i < this->getNumFlights(); i++) {
		Flight *currentFlight = _listFlights[i];
		if (!currentFlight->isCanceled()) {
			vector<int> flightSolution = currentFlight->getCurrentSolution();
			for (vector<int>::iterator it = flightSolution.begin(); it != flightSolution.end(); ++it) {
				int waypointId = currentFlight->getWRById(*it)->getWaypointFather()->getId();
				waypointsInSolution.push_back(waypointId);
			}
		}
	}
	removeDuplicatesVectorIntWithoutSort(waypointsInSolution);
	return waypointsInSolution;
}

int Problem::getRouteByFlightAndWaypoint(int flightId, string waypointName) {
	int routeId = -1;

	string s = RESORCES_FOLDER + "trajectories.csv";
	const char* route = s.c_str();
	ifstream fe(route);
	std::string line;
	while (std::getline(fe, line)) {
		string array[7];
		int i = 0;
		stringstream ssin(line);
		while (ssin.good() && i < 7) {
			ssin >> array[i];
			++i;
		}

		if (atoi(array[0].c_str()) == flightId && array[3].compare(waypointName) == 0) {
			return atoi(array[1].c_str());
		}
	}

	return routeId;
}

vector<string> Problem::getNameWaypointsByFlightAndouteId(int flightId, int routeId) {
	vector<string> nameWaypoints;

	string s = RESORCES_FOLDER + "trajectories.csv";
	const char* route = s.c_str();
	ifstream fe(route);
	std::string line;
	while (std::getline(fe, line)) {
		string array[7];
		int i = 0;
		stringstream ssin(line);
		while (ssin.good() && i < 7) {
			ssin >> array[i];
			++i;
		}

		if (atoi(array[0].c_str()) == flightId && atoi(array[1].c_str()) == routeId) {
			nameWaypoints.push_back(array[3]);
		}
	}

	return nameWaypoints;
}

vector<int> Problem::getWRByWaypointNames(Flight *f, vector<string> waypointNames) {
	vector<int> result;
	for (int i = 0; i < f->getNumWaypointsRoute(); i++) {
		WaypointRoute *currentWR = f->getListWaypointsRoute()[i];
//		cout<<currentWR->getCompleteName()<<endl;
		if (currentWR->isAirport()
				|| checkVectorStringContainsElement(waypointNames, currentWR->getWaypointFather()->getName())) {
			result.push_back(currentWR->getId());
		}
	}
	removeDuplicatesVectorIntWithoutSort(result);
	return result;
}

void Problem::delayOkFlights() {
	srand(time(0));
	random_shuffle(_orderFlights.begin(), _orderFlights.end());

	//launch flights in random order
	for (int i = 0; i < this->getNumFlights(); i++) {
		int currentPosition = this->_orderFlights[i];
		if (_listFlights[currentPosition]->isOnTimeOrDelayed()) {
			vector<int> candidates = getFlightCandidatesDelay(_listFlights[i]);
			cancelFlightOkAndTryCandidates(_listFlights[i], candidates);
		}
	}

//	cout << "---------- DESPUES DE RETRASAR VUELOS OK ----------" << endl;
//	printAllFlightStatus();

}

vector<int> Problem::getFlightCandidatesDelay(Flight *flightOk) {
	std::vector<int> candidates;
	//foreach canceled flight, check if share at least 3 waypoints
	for (int i = 0; i < this->getNumFlights(); i++) {
		Flight *currentFlight = _listFlights[i];
		if (currentFlight->getStatus() == FLIGHT_STATUS_CANCELED && currentFlight->getId() != flightOk->getId()) {
			bool isCandidate = checkFlightsShare2Waypoints(flightOk, currentFlight);
			if (isCandidate) {
//				cout << "El " << currentFlight->getId() << " es un candidato cancelado del OK " << flightOk->getId()
//						<< endl;
				candidates.push_back(currentFlight->getId());
			}
		}
	}
	return candidates;
}

bool Problem::checkFlightsShare2Waypoints(Flight *flightOk, Flight *flightCancel) {
	vector<string> waypointsFlightOk = flightOk->getAllWaypointNames();
	vector<string> waypointsFlightCancel = flightCancel->getAllWaypointNames();

	waypointsFlightOk = removeDuplicatesVectorString(waypointsFlightOk);
	waypointsFlightCancel = removeDuplicatesVectorString(waypointsFlightCancel);

//	printVectorString(waypointsFlightOk);
//	cout << endl;
//	printVectorString(waypointsFlightCancel);
//	cout << endl;

	int common = getNumCommonElementsVectorString(waypointsFlightOk, waypointsFlightCancel);
//	cout << common << "*************" << endl;
	return (common >= 2);
}

void Problem::cancelFlightOkAndTryCandidates(Flight *flightOk, vector<int> candidates) {
	vector<int> originalSolution = flightOk->getCurrentSolution();
	int lastStatus = flightOk->getStatus();
//	cout << endl;
//	cout << "el " << flightOk->getId() << " tiene de candidatos a ";
//	printVectorInt(candidates);
//	cout << endl;
	//free sectors of flight ok
	cancelFlight(flightOk, flightOk->getCurrentSolution());

	//get one random candidate and try to set
	srand(time(0));
	random_shuffle(candidates.begin(), candidates.end());
	for (vector<int>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
		Flight *candidateFlight = getFlightById(*it);

		//first try to set the candidate
		Djistra(candidateFlight, OPTION_ALTERNATIVE_ROUTES);
		bool isCandidateOk = !candidateFlight->isCanceled();

		if (isCandidateOk) {
//			cout << "CANDIDATO VALIDO" << endl;
			//try to re set the original flight
			Djistra(flightOk, OPTION_ALTERNATIVE_ROUTES);
			bool isOriginalOk = !flightOk->isCanceled();

			if (isOriginalOk) {
//				cout << "--------------------->SIIIIIIIIIIII" << endl;
//				cout << "EL " << candidateFlight->getId() << " y el " << flightOk->getId() << endl;
				break;
			} else {
				//Is not a valid candidate
				cancelFlight(candidateFlight, candidateFlight->getCurrentSolution());
			}
		}
	}

//	cout << "AAAAAA " << flightOk->isCanceled() << endl;

	//if at the end there is no solution, set ok again the original flight
	if (flightOk->isCanceled()) {
//		cout << "entro" << endl;
//		cout << "antes " << flightOk->getStatus() << endl;
		flightOk->setStatus(lastStatus);
//		cout << "después " << flightOk->getStatus() << endl;

		flightOk->setCurrentSolution(originalSolution);
	}
//	printAllFlightStatus();

//	exit(1);
}

// createRandom order to launch
void Problem::addFlightsBestSolution() {

	//add default flights to array

	vector<int> orderFlights;
	for (int i = 0; i < this->getNumFlights(); ++i) {
		orderFlights.push_back(i);
	}

	if (!_queueExtraFlights.empty()) {
		for (int i = 0; i < this->_queueExtraFlights.size(); ++i) {
			orderFlights.push_back(_queueExtraFlights[i] - 1);
		}
//		printVectorInt(orderFlights);
//		cout << endl;
//
//		std::random_shuffle(orderFlights.begin(), orderFlights.end());
//		printVectorInt(orderFlights);
//		cout << endl;
//		orderFlights=removeDuplicatesVectorIntWithoutSort(orderFlights);
//		printVectorInt(orderFlights);
//		cout << endl;

	}

	createOrderFlights(orderFlights);

	//add flights in queue

}
void Problem::saveCurrentSolution(int numberIteration) {

	//create solution
	map<int, pair<int, vector<int> > > flights = createSolution();
	int valueSolution = getValueSolution();

	Solution *s = new Solution(numberIteration, flights, valueSolution);
	_solutions.push_back(*s);

}

map<int, pair<int, vector<int> > > Problem::createSolution() {
	map<int, pair<int, vector<int> > > result;
	for (int i = 0; i < this->getNumFlights(); i++) {
		Flight *currentFlight = _listFlights[i];
		pair<int, vector<int> > currentPair;
		currentPair.first = currentFlight->getStatus();
		currentPair.second = currentFlight->getCurrentSolution();
		result[currentFlight->getId()] = currentPair;

	}
	return result;
}

int Problem::getValueSolution() {
	int result = 0;
	for (int i = 0; i < this->getNumFlights(); i++) {
		int statusFlight = _listFlights[i]->getStatus();
		if (statusFlight == FLIGHT_STATUS_IN_TIME) {
			result += 3;
		} else if (statusFlight == FLIGHT_STATUS_DELAYED || statusFlight == FLIGHT_STATUS_DEFLECTED) {
			result += 2;
		} else if (statusFlight == FLIGHT_STATUS_DELAYED_AND_DEFLECTED) {
			result += 1;
		}
	}
	return result;
}

//Get best flights in previous iterations and add it to queue
void Problem::setNewFlightsQueue(int numIteration) {
	Solution *bestSolutionInLast = getBestSolutionLastN(numIteration);

	//if we found a better solution, save it
	if (bestSolutionInLast->getValue() > this->getValueBestSolution()) {
		this->setValueBestSolution(bestSolutionInLast->getValue());
		//add new flights to queue
		vector<int> flghtsToAdd = getFlightsAddToQueue(bestSolutionInLast);
		this->setQueueExtraFlights(flghtsToAdd);
	}
	//if dont find a better solution, delete queue candidates
	else {
		_queueExtraFlights.clear();
	}

}

Solution* Problem::getBestSolutionLastN(int numIteration) {
	Solution *bestSolution;
	int bestValue = 0;
	int start = numIteration - NUM_SOULUTIONS_TO_EXAMINE;
	for (int i = start; i < numIteration; i++) {
		Solution *currentSolution = &_solutions[i];
//		cout << "LA iteracción " << currentSolution->getIteration() << " tiene valor " << currentSolution->getValue()
//				<< endl;
		if (currentSolution->getValue() > bestValue) {
			bestValue = currentSolution->getValue();
			bestSolution = currentSolution;
		}
	}
	//cout << "MEJOR SOLUCIÖN: " << bestSolution->getIteration();
	return bestSolution;
}

vector<int> Problem::getFlightsAddToQueue(Solution *bestSolutionInLast) {
	vector<int> result;
	map<int, pair<int, vector<int> > > flights = bestSolutionInLast->getFlightSolutions();
	for (std::map<int, pair<int, vector<int> > >::iterator it = flights.begin(); it != flights.end(); ++it) {
		Flight *currentFlight = getFlightById(it->first);
		if (currentFlight->isOnTimeOrDelayed()) {
			result.push_back(it->first);
		}
	}

	//get random elements of solution
	srand(time(0));
	random_shuffle(result.begin(), result.end());

	//if solution is too big, get X random elements
	if (result.size() > MAX_NUMBER_QUEUE) {
		vector<int> shortResult;
		for (int i = 0; i < MAX_NUMBER_QUEUE; i++) {
			shortResult.push_back(result[i]);
		}
		return shortResult;
	}

	return result;
}

//Reset flights and capacity sectors
void Problem::resetProblem() {

	//reset flights
	for (int i = 0; i < this->getNumFlights(); i++) {
		Flight *currentFlight = _listFlights[i];
		vector<int> empty;
		currentFlight->setCurrentSolution(empty);
		currentFlight->setStatus(FLIGHT_STATUS_NOT_LAUNCHED);
	}

	//reset capacities
	for (int i = 0; i < this->getNumTimes(); i++) {
		TimeMoment *tm = _timeMomentlist[i];
		for (int j = 0; j < getNumSectors(); j++) {
			int *initialSector = (int*) malloc(this->getNumSectors() * sizeof(int));
			for (int i = 0; i < this->getNumSectors(); i++) {
				initialSector[i] = 0;
			}
			tm->setNumFlightsSector(initialSector);
		}
	}
}

void Problem::getBestSolution() {
	Solution *bestSolution;
	int bestValue = 0;
	for (int i = 0; i < MAX_ITERATIONS - 1; i++) {
		Solution *currentSolution = &_solutions[i];
//		cout << "La iteracción " << currentSolution->getIteration() << " tiene valor " << currentSolution->getValue()
//				<< endl;
		if (currentSolution->getValue() > bestValue) {
			bestValue = currentSolution->getValue();
			bestSolution = currentSolution;
		}
	}
//	cout << "MEJOR SOLUCIÖN DE TODAS ES: " << bestSolution->getIteration() << " con valor " << bestSolution->getValue()
//			<< endl;
}

void Problem::writeResult(int simulation) {

	int numSolutions = this->_solutions.size();
	std::fstream fs;
	fs.open("./Outputs/numSimuation.txt", std::fstream::in | std::fstream::out | std::fstream::app);

	for (int i = 0; i < numSolutions; i++) {
		Solution *currentSolution = &_solutions[i];
		int valueCurrentSolution = currentSolution->getValue();
		fs << simulation << ";" << i << ";" << valueCurrentSolution << endl;

	}

	fs.close();

}
