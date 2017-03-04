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
#include "Solution.h"
#include <vector>
#include <ctime>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <map>

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
	Flight* getFlightById(int id);
	WaypointRoute* getWRById(Flight *f, int id);
	void inizializeProblem(int);
	int nameInList(string nameWay, Waypoint **waypoints, int cont);
	void createWaypoints();
	void createSectors();
	void createFlights();
	void createAllRoutes();
	void createTimes();
	void createRoutes(Flight *flight);
	void createWaypointRoutesObject(Flight *flight);
	void setProblemRouteAttributes(Flight *flight, int **matrix, int numWaypointsList, WaypointRoute **waypointsRoute);
	int getMaxInTime();
	void calculateAllShortestPath();
	void createOrderFlights(vector<int>);
	void updateTimes();
	void getInitialOverloadSectors();
	void getInitialShortestRoutes();
	void initialSolutions();
	void interchangeFlights();
	void flightsTakeOffWithDelays();
	void flightsTakeOffAlternativeRoutes();
	void cancelFlight(Flight* f, vector<int> path);
	void setFlightOk(Flight* f, vector<int> path);
	void setFlightDelayed(Flight* f, vector<int> path);
	void setFlightAlternativeRoute(Flight* f, vector<int> path, int newDuration);
	int getNumFlightsNoCanceled();
	void writeFileForHTML();
	void createFileSectors();
	void createFileFlights();

	bool solutionHasValidSectors(vector<int> vectorWaypointsRoute, Flight *flight);
	bool sectorCapacitiesAreOk(vector<int> solutions);
	void printAllFlightStatus();
	vector<int> getIdWRInIS(Flight *flight);
	void getFlightsUnconnected();
	bool flightIsUnconnected(vector<string> allWaypointsRoute, vector<string> flightWaypointsRoute);
	std::vector<std::string> getUniqueWaypointsRouteByFlight(Flight *flight);
	int sectorIsFreeAtTime(int time, string sectorName, int incrementLimit);
	int conditionDjistraByOption(int option, int inTime, WaypointRoute *wr, vector<int> v, int wrDestiny);
	void updateTimesBetweenWaypoints(int lastInstantFlight, int newInstantFlight, int idSectorToUpdate);
	void tryInterchageFlights();
	vector<int> createFlightCandidatesInterchange(Flight *flight);
	bool checkFlightsShareSectorInTime(Flight *original, Flight *candidate);
	bool existsPairWRInFlight(pair<int, int> orinalPair, Flight *candidate);
	map<int, vector<int> > filterFlightsBlokcMore1(map<int, vector<int> > original);
	int tryAllInterchanges(map<int, vector<int> > mapFiltered);
	bool tryInterchange(int flightId, vector<int> candidates);
	vector<int> getSolutionInterchangeFlights(int flightId, vector<int> candidates, int minSize);
	bool changeFlightForCandidates(int flightId, vector<int> allSolutions);
	void employUnusedWaypoints();
	void delayOkFlights();
	void Djistra(Flight *flight, int option);
	vector<int> getUnusedWaypoints();
	vector<int> getWaypointsInSolutions();
	vector<int> getSolutionWithWaypoint(Flight *f, Waypoint *w);
	int getRouteByFlightAndWaypoint(int flightId, string waypointName);
	vector<string> getNameWaypointsByFlightAndouteId(int flightId, int routeId);
	vector<int> getWRByWaypointNames(Flight *f, vector<string> waypointNames);
	vector<int> getFlightCandidatesDelay(Flight*f);
	bool checkFlightsShare2Waypoints(Flight *flightOk, Flight *flightCancel);
	void cancelFlightOkAndTryCandidates(Flight *flightOk, vector<int> candidates);
	int sectorHasSpace(int inTime);
	void updateTimeSector(vector<int> PathIdWaypointsRoute, Flight *flight, int option);
	int isWaypointRouteInList(WaypointRoute **list, int idFather, int inTime, int sizeList);
	void initialFlightsTakeOff();
	void printStatusProblem();
	void getBestSolution();

	void addFlightsBestSolution();
	void saveCurrentSolution(int numberIteration);
	void setNewFlightsQueue(int);
	Solution* getBestSolutionLastN(int);
	vector<int> getFlightsAddToQueue(Solution *bestSolutionInLast);

	void writeResult(int);
	void createFileResult(int);

	void resetProblem();

	map<int, pair<int, vector<int> > > createSolution();
	int getValueSolution();

	int getNumTimes() const {
		return _numTimes;
	}

	void setNumTimes(int numTimes) {
		_numTimes = numTimes;
	}

	const vector<int>& getQueueExtraFlights() const {
		return _queueExtraFlights;
	}

	void setQueueExtraFlights(const vector<int>& queueExtraFlights) {
		_queueExtraFlights = queueExtraFlights;
	}

	int getValueBestSolution() const {
		return _valueBestSolution;
	}

	void setValueBestSolution(int valueBestSolution) {
		_valueBestSolution = valueBestSolution;
	}

	const string& getRouteFileResults() const {
		return routeFileResults;
	}

	void setRouteFileResults(const string& routeFileResults) {
		this->routeFileResults = routeFileResults;
	}

private:
	int _numAirports;
	int _numSectors;
	int _numTrajectories;
	int _numWaypoints;
	int _numFlights;
	int _numTimes;
	Waypoint **_listWaypoints;
	Sector **_listSectors;
	TimeMoment **_timeMomentlist;
	Flight **_listFlights;
	std::vector<int> _orderFlights;
	std::vector<int> _initialOverload;
	int _iteration;
	ofstream _log;
	vector<int> _queueExtraFlights;
	vector<Solution> _solutions;
	int _valueBestSolution;
	string routeFileResults;
};

#endif /* PROBLEM_H_ */
