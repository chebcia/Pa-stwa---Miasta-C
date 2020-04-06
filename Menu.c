#include "Menu.h"
//wyswietlamy liste opcji w menu glownym
//head - lista z danymi zaladowanymi z pliku
void printMenuOptions(struct List* head)
{
	createParametersJSON();
	printf("1.Zacznij gre\n");
	printf("2.dodaj miasto\n");
	printf("3.wyjdz\n");
	handleMainMenu(head);
}

void handleMainMenu(struct List* head)
{
	char option;
	scanf_s("%c", &option);
	switch (option)
	{
	case '1':
		system("@cls||clear");	//Czyszczenie konsoli
		handleNewGame(head);
		break;
	case '2':
		system("@cls||clear");
		handleAddCity(head);
		break;
	case '3':
		handleExit(head);	//wywolanie funkcji ktora wywoluje funkcje ktora czysci pamiec
		exit(0);
	default:
		break;
	}
}

void handleNewGame(struct List* head)
{
	cJSON* mappedCities = createJSON();
	printf("Wybierz miasto poczatkowe:\n");
	int i = 1;		//od 1 bo uzytkownicy lubia od 1
	int chosenCity;
	int distances[INITIAL_ARRAY_SIZE];
	while (mappedCities->child) {
		printf("%d.%s\n", i, mappedCities->child->string);
		i++;
		mappedCities->child = mappedCities->child->next;
	}
	scanf("%d", &chosenCity);	//adres
	chooseRandom(chooseDificulty(), chooseUnits(), dijkstra(head, chosenCity), chosenCity, head->size);
	printMenuOptions(head);
}

void handleAddCity(struct List* head)
{
	void(*addCityPtr)(struct List* head) = addCity;
	addCityPtr(head);
	printMenuOptions(head);
}

void handleExit(struct List* head)
{
	void(*clearMemoryPtr)(struct List*) = clearMemory;
	clearMemoryPtr(head);
}


void printList(struct List* head) {
	cJSON* json = createJSON();
	while (head->next) {
		printf("Distances from city: %s\n", findCityAtIndex(json, head->index));	//Wyswietlamy Dystans od miasta to TU_STRING ktory czytamy z jsona
		json = createJSON();
		struct List* insideList = head->listInsideAList;
		while (insideList->next) {
			printf("Distance to city: %s=%d\n", findCityAtIndex(json, insideList->index), insideList->distance);	// Wyswietlamy nazwe miasta i odleglosc do miasta ktorego nazwe wyswietlilismy wyzej
			json = createJSON();
			insideList = insideList->next;

		}
		printf("------------------------------\n");
		head = head->next;
	}

}

void handleCommandLineArguments(int argc, char * argv[], struct List* head)
{
	if (argc > 1 && strcmp(argv[1], "-l") == 0) {
		printList(head);
		handleExit(head);
		system("PAUSE");
	}
	else
		printMenuOptions(head);
}
