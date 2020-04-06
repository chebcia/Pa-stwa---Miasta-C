#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "CreateJson.h"

#define INITIAL_ARRAY_SIZE 100
#define POTENTIAL_FILE_SIZE 1000000

struct List {
	int size;
	int index;
	int distance;
	struct Lista* next;
	struct Lista* listInsideAList;
};

void addCity(struct List* head);
struct List* createDistancesList();
void clearAndWriteToDistancesTxt(struct List* head, char* contents, int i);
void appendLastLineToDistances(struct List* head);
void addCityNmeToFile();
struct List* fillListInsideAList(int* distancesArray);
struct List * loadData(char ch, int i, int j);
int findDistanceAtIndex(struct List* head, int i, int j);
void clearMemory(struct List* head);
void addValuesToTheFirstRow(struct List* temp, struct List* anotherTemp);