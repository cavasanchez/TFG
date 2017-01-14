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
#include "Utilities.h""

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
Flight::Flight(int id, int timeStart, int idWaypointStart, int idWaypointEnd, int delayGround) {
	_id = id;
	_timeStart = timeStart;
	_idWaypointEnd = idWaypointEnd;
	_idWaypointStart = idWaypointStart;
	_status = 0;
	_groundDelay = delayGround;
}

WaypointRoute* Flight::getWRById(int id) {
	WaypointRoute *wr = new WaypointRoute();
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
//		cout << "Miro si " << idWaypointRouteFather << " = " << waypointsRoute[i]->getWaypointFather()->getId() << " y "
//				<< inTime << " = " << waypointsRoute[i]->getInTime() << endl;

		if (idWaypointRouteFather == waypointsRoute[i]->getWaypointFather()->getId()
				&& inTime == waypointsRoute[i]->getInTime()) {
			isInList = i;
			break;
		}
	}
//	cout << "inlist es " << isInList << endl;
	return isInList;

}

int Flight::getAllWaypointsFlight() {
	int num = 0;
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

		if (this->getId() == atoi(array[0].c_str())) {
			num++;
		}
	}
	return num;

}

int Flight::isNewWaypoint(std::string newPoint, std::string oldPoints[], int cont) {
//cout<<"me entra "<<newPoint<<endl;

	int isNew = 1;
	for (int i = 0; i < cont; i++) {
		//	cout<<"MIRO SI "<<newPoint<< " es "<<oldPoints[i]<<endl;
		if (oldPoints[i].compare(newPoint) == 0) {
			isNew = 0;
			break;
		}
	}
//	cout<<"Es nuevo "<<isNew<<endl;
	return isNew;
}

//Número de waypoints que hay en TODAS las rutas del vuelo (sin repetir)
int Flight::numWaypointsFlight(int idFlight, int numWaypoints) {
	int numDifferentWaypoints = 0;
	int cont = 0;
//REVISA ESTO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	this->_listNameWaypoints = new std::string[numWaypoints];
	std::string oldNames[numWaypoints];
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

		if (atoi(array[0].c_str()) == idFlight) {

			if (isNewWaypoint(array[3], oldNames, cont)) {
				oldNames[cont] = array[3];
				this->_listNameWaypoints[cont] = array[3];
				numDifferentWaypoints++;
			}
			cont++;

		}
	}
//std::cout << "EL " << idFlight << "tiene "<<numDifferentWaypoints<< std::endl;
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

/*
 * STATUS VUELO:
 * 0= sin salir
 * 1= llegó en tiempo
 * 2= llega con delay
 * -1= cancelado
 * -10= sin solución inicial -> ERROR DATOS
 */

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
		case FLIGHT_STATUS_DELAYEYD:
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

