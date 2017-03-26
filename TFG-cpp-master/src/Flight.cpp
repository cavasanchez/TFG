/*
 * Flight.cpp
 *
 *  Created on: 2/2/2016
 *      Author: carlos
 */

#include "Flight.h"

#include <fstream>
#include <string>     // std::string, std::stoi

#include "Sector.h"
#include "Problem.h"
#include "TimeMoment.h"
#include "Waypoint.h"
#include "Sector.h"
#include "Utilities.h"

#include <ctime>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

Flight::Flight() {

}

Flight::~Flight() {
	for (int i = 0; i < 1000; i++) {
		delete _listWaypointsRoute[i];
	}

	delete _listWaypointsRoute;

	for (int i = 0; i < 1000; i++) {
		free(_routes[i]);
	}
	free(_routes);

}

Flight::Flight(int id, int timeStart, int idWaypointStart, int idWaypointEnd, int delayGround) {
	_id = id;
	_timeStart = timeStart;
	_idWaypointEnd = idWaypointEnd;
	_idWaypointStart = idWaypointStart;
	_status = FLIGHT_STATUS_NOT_LAUNCHED;
	_groundDelay = delayGround;
	_status = FLIGHT_STATUS_NOT_LAUNCHED;
}

WaypointRoute* Flight::getWRById(int id) {
	WaypointRoute *wr;
	for (int i = 0; i < this->getNumWaypointsRoute(); i++) {
		if (_listWaypointsRoute[i]->getId() == id) {
			wr = _listWaypointsRoute[i];
			break;
		}
	}
	return wr;
}

//Comprueba si en la lista de waypointsFather hay algún nodo con father e inTime similar
int Flight::isWaypointInList(int idWaypointRouteFather, int sizeList, int inTime, WaypointRoute **waypointsRoute) {
	int isInList = -1;
	for (int i = 0; i < sizeList; i++) {
		if (idWaypointRouteFather == waypointsRoute[i]->getWaypointFather()->getId()
				&& inTime == waypointsRoute[i]->getInTime()) {
			isInList = i;
			break;
		}
	}
	return isInList;
}

int Flight::getAllWaypointsFlight() {
	int num = 0;
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

		if (this->getId() == atoi(array[0].c_str())) {
			num++;
		}
	}
	return num;

}

int Flight::isNewWaypoint(std::string newPoint, std::string oldPoints[], int cont) {
	int isNew = 1;
	for (int i = 0; i < cont; i++) {
		if (oldPoints[i].compare(newPoint) == 0) {
			isNew = 0;
			break;
		}
	}
	return isNew;
}

//Número de waypoints que hay en TODAS las rutas del vuelo (sin repetir)
int Flight::numWaypointsFlight(int idFlight, int numWaypoints) {
	int numDifferentWaypoints = 0;
	int cont = 0;

	std::string oldNames[numWaypoints];
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

		if (atoi(array[0].c_str()) == idFlight) {

			if (isNewWaypoint(array[3], oldNames, cont)) {
				oldNames[cont] = array[3];
				_allWaypointNames.push_back(array[3]);
				numDifferentWaypoints++;
			}
			cont++;

		}
	}
	return numDifferentWaypoints;
}

vector<int> Flight::getIdSectorsIS() {
	vector<int> sectors;
	for (std::vector<int>::iterator it = this->_initialSolution.begin(); it != this->_initialSolution.end(); ++it) {
		WaypointRoute *currentWR = _listWaypointsRoute[*it];
		sectors.push_back(currentWR->getIdSector());
	}

	return removeDuplicatesVectorInt(sectors);
}

void Flight::printStatus() {
	cout << "El vuelo " << this->_id << " está ";
	switch (this->_status) {
		case FLIGHT_STATUS_ERROR:
			cout << "SIN SOLUCIÓN INICIAL. ERROR";
			break;
		case FLIGHT_STATUS_CANCELED:
			cout << "CANCELADO";
			break;
		case FLIGHT_STATUS_NOT_LAUNCHED:
			cout << "SIN SALIR";
			break;
		case FLIGHT_STATUS_IN_TIME:
			cout << "LLEGÓ EN TIEMPO";
			break;
		case FLIGHT_STATUS_DELAYED:
			cout << "OK PERO RETRASADO";
			break;
		case FLIGHT_STATUS_DEFLECTED:
			cout << "OK PERO DESVIADO";
			break;
		case FLIGHT_STATUS_DELAYED_AND_DEFLECTED:
			cout << "OK PERO RETRASADO Y DESVIADO";
			break;

	}
	cout << endl;

}

bool Flight::isCanceled() {
	return (_status == FLIGHT_STATUS_ERROR || _status == FLIGHT_STATUS_CANCELED || _status == FLIGHT_STATUS_NOT_LAUNCHED);
}

bool Flight::isOnTimeOrDelayed() {
	return (_status == FLIGHT_STATUS_DELAYED || _status == FLIGHT_STATUS_IN_TIME);

}

int Flight::getSomeWaypointUnused(vector<int> waypointId, vector<int> waypointsToAvoid) {

	for (int i = 0; i < this->getNumWaypointsRoute(); i++) {
		WaypointRoute *wr = this->getListWaypointsRoute()[i];
		bool contains = checkVectorContainsElement(waypointId, wr->getWaypointFather()->getId());
		if (contains && !checkVectorContainsElement(waypointsToAvoid, wr->getWaypointFather()->getId())) {

			return wr->getWaypointFather()->getId();
		}
	}
	return -1;
}

