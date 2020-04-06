#include "List.h"
//funkcja dodawania miast do istniejacej lity miast i do zapisywania do pliku
void addCity(struct List * head)
{
	if (!head) {	//jezeli nie ma glowy to ladujemy miasta z pliku
		head = loadData('\0', 0, 0);
	}
	else {
		addCityNmeToFile();
		FILE* fp;
		struct List* newDistancesList = createDistancesList();
		fp = fopen("Distances.txt", "a+");
		struct List * temp = newDistancesList;
		char contents[POTENTIAL_FILE_SIZE];
		char ch;
		int i = 0;
		while ((ch = fgetc(fp)) != EOF) {	//wpisujemy do tablicy contents cala zawartosc pliku distances.txt razem z srednikami \n itd..
			contents[i] = ch;
			i++;
		}
		contents[i - 1] = '\0';
		fclose(fp);
		clearAndWriteToDistancesTxt(temp, contents, i);
		fclose(fp);
		appendLastLineToDistances(newDistancesList);
	}
	getchar();
}

/*funkcja dopisujaca ostatni rzad dystansow do pliku Distances.txt
	head - glowa listy z ktorej bedziemy pobierac wartosci ktore wpiszemy w ostatni rzad pliku Distances.txt
*/
void appendLastLineToDistances(struct List* head) {
	FILE* fp;
	fp = fopen("Distances.txt", "a");
	fprintf(fp, "\n");
	struct List* temp = head;	//cium cium cium
	while (temp->next) {	//dopisalismy kolumne, teraz dopisujemy to samo jako ostatni wiersz
		//rewind(fp);
		fprintf(fp, "%d;", temp->distance);
		temp = temp->next;
	}
	fprintf(fp, "0;\n"); //printujemy 0 bo dystans z miasto do samego siebie to 0
	fclose(fp);
}

//funkcja dopisujaca nazwe miasta do pliku Miasta.txt
void addCityNmeToFile() {
	cJSON* json = createParametersJSON();
	//const int INITIAL_ARRAY_SIZEx = findValueForString(json, "INITIAL_ARRAY_SIZE");
	char cityName[INITIAL_ARRAY_SIZE];	//String do ktorego wpiszemy nazwe miasta a zestring to tablica charow to jest tablica charow
	//char* cityName;
	printf("Podaj nazwe miasta: ");
	scanf("%s", &cityName);
	FILE* fp;
	fp = fopen("Miasta.txt", "a");	// "a" - append czyli dolaczyc czyli dopisywanie do pliku
	fprintf(fp, strcat(cityName, ";")); //Laczenie stringow
	fclose(fp);
}
/*funkcja wpisujaca wartosci do pliku Distances.txt
	head - wartosci ktore bedziemy dopisywac do pliku
	contents - tablica charow przechowujaca poprzednia zawartosc pliku
	i - ilosc elementow w pliku

*/
void clearAndWriteToDistancesTxt(struct List* head, char* contents, int i) {
	FILE* fp;
	fp = fopen("Distances.txt", "w");//podczas otwieranie w "w" plik jest czyszczony
	for (int j = 0; j < i; j++) {
		if (contents[j] == '\n' || contents[j] == '\0') {
			fflush(fp);	//wymusza zapisanie danych
			if (contents[j] == '\n')	//na koniec linii w pliku wpisujemy dystans z listy ktora wczesniej stworzylismy
				fprintf(fp, "%d;%c", head->distance, contents[j]);	//%d - printujemy liczbe, %c - printujemy chara
			else
				fprintf(fp, "%d;", head->distance);	//printujemy dystans i srednik
			head = head->next;
		}
		else {
			fflush(fp);
			fprintf(fp, "%c", contents[j]);
		}
	}
	fclose(fp);
}

// funkcja pytajaca uzytkownika o odleglosci do miast by pozniej stworzyc z nich liste
struct List* createDistancesList() {	//robimy jeden wymiar listy i wpisujemy odleglosci do poszczegolnych miast
	struct List* head = (struct List*)malloc(sizeof(struct List));	//alokujemy pamiec dla glowy listy
	head->size = 0; // nadajemy wartosci poczatkowe (taki konstruktor rozbity na wiele linijek)
	struct List* temp = head;
	temp->next = NULL;
	cJSON* mappedCities = createJSON();
	int distance;
	int index = 0;
	while (mappedCities->child->next) {
		printf("Podaj odleglosc do miasta %s: ", mappedCities->child->string); //wyswietlanie
		scanf("%d", &distance);	//wpisywanie
		temp->index = index;
		temp->distance = distance;

		temp->next = (struct List *)malloc(sizeof(struct List));
		head->size++;
		temp = temp->next;
		index++;
		mappedCities->child = mappedCities->child->next;
	}
	temp->next = NULL;
	return head;
}
/*Funkcja ³aduje dane z pliku Distances.txt do pamiêci programu
	ch - pusty char do ktorego wpisujemy wartosci z pliku
	i - iterator porzebny do wypelniania tablicy lenght, resetuje sie do zera podczas napotkania \0
	j - iterator potrzebny do wypelnienia tablicy distancesArray, resetuje sie do zera podczas napotkania \n

*/
struct List * loadData(char ch, int i, int j) {
	struct List* head = (struct List*)malloc(sizeof(struct List));	//to takie new z c++ czyli rezerwujemy miejsce w pamieci na glowe
	head->size = 0;
	struct List* temp = head;
	temp->next = NULL;
	FILE* fp = fopen("Distances.txt", "r");
	char length[INITIAL_ARRAY_SIZE];	//Dystans zczytany z pliku
	int distancesArray[INITIAL_ARRAY_SIZE];
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n') {
			j = 0;
			temp->listInsideAList = fillListInsideAList(distancesArray);
			head->size++;
			temp->next = (struct List*)malloc(sizeof(struct List));		//na glownej glowie
			temp = temp->next;
			temp->next = NULL;
			ch = fgetc(fp);
		}
		else if (ch != ';') {
			length[i] = ch;
			i++;
		}
		else {
			length[i] = '\0';
			int lengthInteger = atoi(length);	//atoi zmienia string na integer
			distancesArray[j] = lengthInteger;
			j++;
			i = 0;
		}
	}
	temp = head;
	addValuesToTheFirstRow(temp, head->listInsideAList);
	fclose(fp);
	return head;
}
/*funkcja dopisujaca wartosci do pierwszego rzedu listy list (wypelniamy jakby tab[i][0]) PS> to jest te skracanie funkcji w linijkach
	temp - lista do ktorej dopisujemy
	anotherTemp - przechowywator glowy
*/
void addValuesToTheFirstRow(struct List* temp, struct List* anotherTemp) {
	while (temp)//dopisujemy nowe miasto do listy ktora juz byla w pamieci programu
	{
		temp->index = anotherTemp->index;
		temp->distance = anotherTemp->distance;
		anotherTemp = anotherTemp->next;
		temp = temp->next;
	}
}

/*funkcja wypelniajaca liste w liscie (czyli robimy tab[0][i])     PS> to tez
	distancesArray - tablica z ktorej pobieramy wartosci ktorymi wypelnimy liste w liscie
*/
struct List* fillListInsideAList(int* distancesArray) {
	struct List* head = (struct List*)malloc(sizeof(struct List));
	struct List* insideListTemp = head;
	cJSON* jsonObject = createParametersJSON();
	int defaultIntValue = findValueForString(jsonObject, "DEFAULT_INT_VALUE");
	insideListTemp->next = NULL;	//ustawiamy nastepny element listy na NULL
	for (int k = 0; distancesArray[k] != defaultIntValue; k++) {
		insideListTemp->index = k;
		insideListTemp->distance = distancesArray[k];
		insideListTemp->size++;
		insideListTemp->next = (struct List*)malloc(sizeof(struct List)); //alokujemy pamiec dla nastepnego elemntu ktory wczesniej ustalilismy na NULL
		insideListTemp = insideListTemp->next;
		insideListTemp->next = NULL;
	}
	return head;
}
/*to jest po prostu head[i][j] tylko ze przelozone na nasza liste
	head-lista w ktorej szukamy wartosci
	i-pierwszy indeks (rzedy)
	j-drugi indeks  (kolumny)
*/
int findDistanceAtIndex(struct List * head, int i, int j)	
{
	struct List* temp = head;
	while (temp->index != i && temp->next)
		temp = temp->next;
	struct List* tempInsideList = temp->listInsideAList;
	while (tempInsideList->index != j && tempInsideList->next)
		tempInsideList = tempInsideList->next;
	return tempInsideList->distance;

	

}
//funkcja czyszczaca
//head -> glowa listy do wyczyszczenia
void clearMemory(struct List * head)
{
	struct List* temp = head;
	while (head->next) {
		temp = head->next;
		struct List* insideHead = head->listInsideAList;
		while (insideHead) {
			struct List* insideTemp = insideHead->next;
			free(insideHead);
			insideHead = insideTemp;
			//insideTemp = insideHead->next;
		}
		free(insideHead);
		free(head);
		head = temp;
	}
	free(head);
}
