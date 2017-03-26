/*
 * Flight.h
 *
 *  Created on: 30/1/2016
 *      Author: carlos
 */

#ifndef FLIGHT_H_
#define FLIGHT_H_

#include <string>
#include <vector>

#include "Waypoint.h"
#include "WaypointRoute.h"

class Flight {
public:

	Flight();

	Flight(int id, int timeStart, int idWaypointStart, int idWaypointEnd, int delayGround);

	virtual ~Flight();

	int numWaypointsFlight(int idFlight, int numWaypoints);
	WaypointRoute* getWRById(int id);
	int isNewWaypoint(std::string newPoint, std::string oldPoints[], int cont);
	int getAllWaypointsFlight();
	int isWaypointInList(int idWaypointRoute, int sizeList, int inTime, WaypointRoute **waypointsRoute);
	void printStatus();
	bool isCanceled();
	bool isOnTimeOrDelayed();
	int getSomeWaypointUnused(std::vector<int> waypointId, std::vector<int> waypointsToAvoid);

	int getId() const {
		return _id;
	}

	void setId(int id) {
		_id = id;
	}

	int getIdWaypointEnd() const {
		return _idWaypointEnd;
	}

	void setIdWaypointEnd(int idWaypointEnd) {
		_idWaypointEnd = idWaypointEnd;
	}

	int getIdWaypointStart() const {
		return _idWaypointStart;
	}

	void setIdWaypointStart(int idWaypointStart) {
		_idWaypointStart = idWaypointStart;
	}

	int getNumWaypoints() const {
		return _numWaypoints;
	}

	void setNumWaypoints(int numWaypoints) {
		_numWaypoints = numWaypoints;
	}

	int getTimeStart() const {
		return _timeStart;
	}

	void setTimeStart(int timeStart) {
		_timeStart = timeStart;
	}

	int getStatus() const {
		return _status;
	}

	void setStatus(int status) {
		_status = status;
	}



	int getGroundDelay() const {
		return _groundDelay;
	}

	void setGroundDelay(int groundDelay) {
		_groundDelay = groundDelay;
	}

	int getNumRoutes() const {
		return _numRoutes;
	}

	void setNumRoutes(int numRoutes) {
		_numRoutes = numRoutes;
	}

	int getNumWaypointsRoute() const {
		return _numWaypointsRoute;
	}

	void setNumWaypointsRoute(int numWaypointsRoute) {
		_numWaypointsRoute = numWaypointsRoute;
	}

	int** getRoutes() const {
		return _routes;
	}

	void setRoutes(int** routes) {
		_routes = routes;
	}

	WaypointRoute**& getListWaypointsRoute() {
		return _listWaypointsRoute;
	}

	void setListWaypointsRoute(WaypointRoute**& listWaypointsRoute) {
		_listWaypointsRoute = listWaypointsRoute;
	}

	const std::vector<int>& getCurrentSolution() const {
		return _currentSolution;
	}

	void setCurrentSolution(const std::vector<int>& currentSolution) {
		_currentSolution = currentSolution;
	}

	const std::vector<int>& getIntialSolution() const {
		return _initialSolution;
	}

	void setIntialSolution(const std::vector<int>& intialSolution) {
		_initialSolution = intialSolution;
	}

	int getTimeFinish() const {
		return _timeFinish;
	}

	void setTimeFinish(int timeFinish) {
		_timeFinish = timeFinish;
	}

	std::vector<int> getIdSectorsIS();

	const std::string& getWaypointNameToAvoid() const {
		return _waypointNameToAvoid;
	}

	void setWaypointNameToAvoid(const std::string& waypointNameToAvoid) {
		_waypointNameToAvoid = waypointNameToAvoid;
	}

	const std::vector<std::string>& getAllWaypointNames() const {
		return _allWaypointNames;
	}

	void setAllWaypointNames(const std::vector<std::string>& allWaypointNames) {
		_allWaypointNames = allWaypointNames;
	}

private:
	int _id;
	int _timeStart;
	int _groundDelay;
	int **_routes;
	int _numWaypoints;
	int _idWaypointStart;
	int _idWaypointEnd;
	int _status;
	int _numRoutes;
	int _timeFinish;
	std::vector<std::string> _allWaypointNames;
	WaypointRoute **_listWaypointsRoute;
	int _numWaypointsRoute;
	std::vector<int> _initialSolution;	// in waypointsRouteId
	std::vector<int> _currentSolution;	//
	std::vector<Flight> _flightInterchangeCandidates;
	std::string _waypointNameToAvoid;

};

#endif /* FLIGHT_H_ */
