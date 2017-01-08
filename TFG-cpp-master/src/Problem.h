/*
 * Problem.h
 *
 *  Created on: 30/1/2016
 *      Author: carlos
 */

#ifndef PROBLEM_H_
#define PROBLEM_H_
#include "Waypoint.h"
#include "Sector.h"
#include "TimeMoment.h"
#include "Flight.h"
#include "WaypointRoute.h"
#include "Heuristic.h"
#include "Constants.h"
#include <vector>
#include <ctime>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class Problem {
public:
	Problem();
	virtual ~Problem();

	Problem(int numAirports, int numSectors, int numTrajectories, int numWaypoints, int numFlights);

	int getNumAirports() const {
		return _numAirports;
	}

	void setNumAirports(int numAirports) {
		_numAirports = numAirports;
	}

	int getNumFlights() const {
		return _numFlights;
	}

	void setNumFlights(int numFlights) {
		_numFlights = numFlights;
	}

	int getNumSectors() const {
		return _numSectors;
	}

	void setNumSectors(int numSectors) {
		_numSectors = numSectors;
	}

	int getNumTrajectories() const {
		return _numTrajectories;
	}

	void setNumTrajectories(int numTrajectories) {
		_numTrajectories = numTrajectories;
	}

	int getNumWaypoints() const {
		return _numWaypoints;
	}

	void setNumWaypoints(int numWaypoints) {
		_numWaypoints = numWaypoints;
	}

	Sector* getSectorById(int id);
	Sector* getSectorByName(std::string name);
	int getIdWaypointByName(std::string name);
	Waypoint* getWaypointById(int id);
	int getIdSectorByName(std::string name);

	void inizializeProblem();
	int nameInList(string nameWay, Waypoint **waypoints, int cont);
	void createWaypoints();
	void createSectors();
	void createFlights();
	void createAllRoutes();
	void createRoutes(Flight *flight);
	void createWaypointRoutesObject(Flight *flight);
	void setProblemRouteAttributes(Flight *flight, int **matrix, int numWaypointsList, WaypointRoute **waypointsRoute);

	void createTimes();
	void calculateAllShortestPath();
	void createOrderFlights();
	void updateTimes();
	void getInitialOverloadSectors();
	void getInitialShortestRoutes();
	void initialValidations();
	void interchangeFlights();

	bool solutionHasValidSectors(vector<int> vectorWaypointsRoute, Flight *flight);

	void getFlightsUnconnected();
	void assignHeuristcs();
	bool flightIsUnconnected(vector<string> allWaypointsRoute, vector<string> flightWaypointsRoute);
	std::vector<std::string> getUniqueWaypointsRouteByFlight(Flight *flight);
	int sectorIsFreeAtTime(int time, string sectorName);
	int conditionDjistraByOption(int option, int inTime, string sectorWaypointRoute, int isAirport);
	void updateTimesBetweenWaypoints(int lastInstantFlight, int newInstantFlight, int idSectorToUpdate);
	void tryInterchageFlights();
	void createFlightCandidatesInterchange(Flight *flight);
	bool checkFlightsShareSectorInTime(Flight *original, Flight *candidate);

	void Djistra(Flight *flight, int option);

	int sectorHasSpace(int inTime);
	void updateTimeSector(vector<int> PathIdWaypointsRoute, Flight *flight);
	int isWaypointRouteInList(WaypointRoute **list, int idFather, int inTime, int sizeList);
	void initialFlightsTakeOff();

private:
	int _numAirports;
	int _numSectors;
	int _numTrajectories;
	int _numWaypoints;
	int _numFlights;
	Waypoint **_listWaypoints;
	Sector **_listSectors;
	TimeMoment **_timeMomentlist;
	Flight **_listFlights;

	std::vector<int> _orderFlights;
	std::vector<int> _initialOverload;
	int _iteration;
	ofstream _log;

};

#endif /* PROBLEM_H_ */
