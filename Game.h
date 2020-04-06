#pragma once
#include "CreateJson.h"
#define INITIAL_ARRAY_SIZE 100

int chooseDificulty();
double chooseUnits();
void chooseRandom(int dificulty,double units, int data[],int chosenIndex, int size);
int play(int data[], int dificulty,double unitMultiplayer, int cityIndex);
double unitMultiplayer(int choice);