#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits> // for numeric_limits
#include <list>
#include <queue>
#include <string>
#include <utility> // for pair
#include <vector>
#include <typeinfo>

#include "Flight.h"
#include "Problem.h"
#include "TimeMoment.h"
#include "Waypoint.h"
#include "WaypointRoute.h"
#include "Utilities.h"

typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();
const double MAX_DISTANCE = 1000;

struct neighbor {
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight) :
			target(arg_target), weight(arg_weight) {
	}
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;
typedef std::pair<weight_t, vertex_t> weight_vertex_pair_t;

void computePaths(vertex_t source, const adjacency_list_t &adjacency_list, std::vector<weight_t> &min_distance,
		std::vector<vertex_t> &previous) {
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	// we use greater instead of less to turn max-heap into min-heap
	std::priority_queue<weight_vertex_pair_t, std::vector<weight_vertex_pair_t>, std::greater<weight_vertex_pair_t> > vertex_queue;
	vertex_queue.push(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty()) {
		weight_t dist = vertex_queue.top().first;
		vertex_t u = vertex_queue.top().second;
		vertex_queue.pop();

		// Because we leave old copies of the vertex in the priority queue
		// (with outdated higher distances), we need to ignore it when we come
		// across it again, by checking its distance against the minimum distance
		if (dist > min_distance[u])
			continue;

		// Visit each edge exiting u
		const std::vector<neighbor> &neighbors = adjacency_list[u];
		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin(); neighbor_iter != neighbors.end();
				neighbor_iter++) {
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.push(std::make_pair(min_distance[v], v));
			}
		}
	}
}

std::list<vertex_t> getShortestPathTo(vertex_t vertex, const std::vector<vertex_t> &previous) {
	std::list<vertex_t> path;
	for (; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}

adjacency_list_t createGraph(Flight *flight, int idWaypoints[], int option, Problem *p) {

	adjacency_list_t adjacency_list(flight->getNumWaypointsRoute());

	switch (option) {
		case OPTION_SHORTEST_PATH:

			for (int idWaypoint = 0; idWaypoint < flight->getNumWaypointsRoute(); idWaypoint++) {
				int currentDelay = 0;

				for (int fila = 0; fila < flight->getNumWaypointsRoute(); fila++) {
					if (flight->getRoutes()[fila][idWaypoints[idWaypoint]] != 1000) {

						WaypointRoute *currentWaypointRoute = flight->getListWaypointsRoute()[fila];
						std::string nameWaypointRoute = currentWaypointRoute->getCompleteName();
						std::string sectorWaypointRoute =
								currentWaypointRoute->getWaypointFather()->getSector1()->getName();

						// Time instant we analize
						int inTime = currentWaypointRoute->getInTime() + flight->getTimeStart();
						int isAirport = currentWaypointRoute->getWaypointFather()->getIsAirport();

						if (p->conditionDjistraByOption(option, inTime, sectorWaypointRoute, isAirport)) {
							int totalDelay = flight->getRoutes()[fila][idWaypoints[idWaypoint]] + currentDelay;
							neighbor newNeighbor = neighbor(fila, totalDelay);

							adjacency_list[idWaypoints[idWaypoint]].push_back(newNeighbor);
						}

						if (!isAirport)
							currentDelay++;
					}
				}
			}

			break;

		case OPTION_ONLY_INITIAL_SOLUTION:
			vector<int> initialSoluton = flight->getIntialSolution();
			if (p->solutionHasValidSectors(initialSoluton, flight)) {

				cout << "ID: " << flight->getId() << endl;
				for (int i = 0; i < initialSoluton.size(); i++) {

					int currentWRId = initialSoluton[i];
					int nextWRid = initialSoluton[i + 1];
					WaypointRoute *wr = flight->getListWaypointsRoute()[currentWRId];
					cout << currentWRId << " --> " << wr->getInTime() << endl;

					//start airport
					if (currentWRId == 0) {
						neighbor n = neighbor(initialSoluton[i + 1], 0);
						adjacency_list[currentWRId].push_back(n);
					}

					//endairport
					else if (nextWRid == 1) {
						neighbor n = neighbor(nextWRid, 0);
						adjacency_list[currentWRId].push_back(n);
						break;
					}

					//no airports and no primas
					else {
						int currentCost = flight->getListWaypointsRoute()[currentWRId]->getInTime();
						int costNext = flight->getListWaypointsRoute()[nextWRid]->getInTime();

						neighbor n = neighbor(initialSoluton[i + 1], costNext - currentCost);
						adjacency_list[currentWRId].push_back(n);
					}

				}
			}

	}
	return adjacency_list;

}

//Return the shortest path from start to end given a flight
void Problem::Djistra(Flight *flight, int option) {
	vector<int> pathWaypointsRoute;
	vector<weight_t> min_distance;
	vector<vertex_t> previous;

	//Array with Waypoint names
	std::string arrayNameswaypoints[flight->getNumWaypointsRoute()];
	//Array with waypoints id
	int idWaypoints[flight->getNumWaypointsRoute()];

	for (int i = 0; i < flight->getNumWaypointsRoute(); i++) {
		std::string nameWaypointRoute = flight->getListWaypointsRoute()[i]->getCompleteName();
		arrayNameswaypoints[i] = i;
		idWaypoints[i] = i;
	}

	//crete graph given opton
	adjacency_list_t adjacency_list = createGraph(flight, idWaypoints, option, this);

	//Find shortest path
	computePaths(0, adjacency_list, min_distance, previous);

	int distance = min_distance[1];
	std::cout << "Distance del " << flight->getId() << ": " << distance << std::endl;

	// If we have found a route
	if (distance < MAX_DISTANCE && distance > 0) {

		list<vertex_t> path = getShortestPathTo(1, previous);
		cout << "Path: ";
		copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
		cout << endl;

		vector<int> pathWaypointsRoute = createVectorFromList(path);

		//Post solution
		switch (option) {
			case OPTION_SHORTEST_PATH:
				flight->setIntialSolution(pathWaypointsRoute);
				break;

			case OPTION_ONLY_INITIAL_SOLUTION:
				cout << "----ENCONTRADO!" << endl;
				setFlightOk(flight,pathWaypointsRoute);
				flight->setTimeFinish(flight->getTimeStart() + distance);
				break;
		}

	} else {
		switch (option) {
			case OPTION_SHORTEST_PATH:
				flight->setStatus(-10);
				cout << "SIN SOLUCION INICIAL. CAMINO NO ENCONTRADO" << endl;

			case OPTION_ONLY_INITIAL_SOLUTION:
				flight->setStatus(-1);
				cout << "CAMINO NO ENCONTRADO" << endl;
		}

	}

}

