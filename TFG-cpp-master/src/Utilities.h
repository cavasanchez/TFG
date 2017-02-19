/*
 * Aux.h
 *
 *  Created on: 30/1/2016
 *      Author: carlos
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <iostream>
#include "Problem.h"
#include "Waypoint.h"
#include <fstream>
#include <list>

int linesFile(string route);
void printProblemData(std::ofstream log, Problem *p);
void printArrayInt(int *array, int size);

void printMatrixInt(int **matrix, int size);
void printMatrixString(std::string **matrix, int size);
pair<int, int> getMinMaxTimeWR(vector<int> candidates, Problem *p);

void inicializeMatrixTo0(int **matrix, int num);

string writeInLog(std::string text);

void printVectorString(vector<string> vectorStrings);
void printVectorInt(vector<int> vectorInts);
vector<int> createVectorFromList(list<int> path);
vector<int> getFlightsThatBlocks(int value, map<int, vector<int> > original);
bool checkVectorContainsElement(vector<int> v, int value);
bool checkVectorStringContainsElement(vector<string> v, string value);
vector<string> removeDuplicatesVectorString(vector<string> vectorStrings);
vector<int> removeDuplicatesVectorInt(vector<int> vectorInt);
int getMinValueFomVector(vector<int> vector);

vector<string> joinVectorString(vector<string> vectorA, vector<string> vectorB, vector<string> &finalVector);
vector<int> arrayIntToVector(int *array);
int** initializeMatrixRoutes();
vector<int> removeElementsFromVector(vector<int> orignal, vector<int> elementsToDelete);
bool vectorContainsAllValues(vector<int> orignal, vector<int> elementsToCheck);
int getNumCommonElementsVectorString(vector<string> a, vector<string> b);
vector<int> removeDuplicatesVectorIntWithoutSort(vector<int> vectorInt);

#endif /* UTILITIES_H_ */
