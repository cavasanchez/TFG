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

int linesFile(char* route);
void printProblemData(std::ofstream log, Problem *p);
void printArrayInt(int *array, int size);

void printMatrixInt(int **matrix, int size);
void printMatrixString(std::string **matrix, int size);

void inicializeMatrixTo0(int **matrix, int num);

std::string writeInLog(std::string text);

void printVectorString(vector<string> vectorStrings);
void printVectorInt(vector<int> vectorInts);

vector<string> removeDuplicatesVectorString(vector<string> vectorStrings);
vector<string> joinVectorString(vector<string> vectorA, vector<string> vectorB, vector<string> &finalVector);
vector<int> arrayIntToVector(int *array);

#endif /* UTILITIES_H_ */
