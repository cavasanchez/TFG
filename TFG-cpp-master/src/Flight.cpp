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
#include <ctime>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

Flight::Flight(int id, int timeStart, int idWaypointStart, int idWaypointEnd, int delayGround) {
	_id = id;
	_timeStart = timeStart;
	_idWaypointEnd = idWaypointEnd;
	_idWaypointStart = idWaypointStart;
	_status = 0;
	_groundDelay = delayGround;
}

//Comprueba si en la lista de waypointsFather hay algún nodo con father e inTime similar
int Flight::isWaypointInList(int idWaypointRouteFather, int sizeList, int inTime, WaypointRoute **waypointsRoute) {
	int isInList = -1;
	for (int i = 0; i < sizeList; i++) {
		cout << "Miro si " << idWaypointRouteFather << " = " << waypointsRoute[i]->getWaypointFather()->getId() << " y "
				<< inTime << " = " << waypointsRoute[i]->getInTime() << endl;

		if (idWaypointRouteFather == waypointsRoute[i]->getWaypointFather()->getId()
				&& inTime == waypointsRoute[i]->getInTime()) {
			isInList = i;
			break;
		}
	}
	cout << "inlist es " << isInList << endl;
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

void Flight::assignHeuristics() {
	Heuristic *heuristic = new Heuristic(this->getNumRoutes(), this->getNumWaypointsRoute());
	this->_heuristic = heuristic;
	double heuristicNumberRoutesANdWaypoints = _heuristic->getHeuristicNumberwaypoints();

}

