#pragma once
#include "stdio.h"
#include "List.h"
#include "Dijkstra.h"
#include "Game.h"
void printMenuOptions(struct List* head);
void handleMainMenu(struct List* head);
void handleNewGame(struct List* head);
void handleAddCity(struct List* head);
void handleExit(struct List* head);
void printList(struct List* head);
void handleCommandLineArguments(int argc, char* argv[], struct List* head);
