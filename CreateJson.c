#include "CreateJson.h"
//funkcja wpisuajca wartosci z pliku Miasta.txt do obiektu JSON
cJSON* createJSON() {
	char ch;
	cJSON* objectToReturn = cJSON_CreateObject();	//inicjalizacja jsona
	FILE* fp;
	fp = fopen("Miasta.txt", "r");
	int i = 0;
	int citiesCounter = 0;
	char word[100];
	while ((ch = fgetc(fp)) != EOF) {
		if (ch != ';') {
			word[i] = ch;		//czytamy znak po znaku W a r s z w a az do srednika i przypisujemy W a r s z w a do tablicy znakow
			i++;
		}
		else {
			word[i] = '\0';	//\- zeby zakonczyc string
			cJSON_AddNumberToObject(objectToReturn, word, citiesCounter);	//Dodajemy do naszego JSONA wartosc Warszawa i klucz citiesCounter
			citiesCounter++;
			i = 0;
		}

	}
	fclose(fp);
	return objectToReturn;	//zwracamy glowe jsona czyli glowe drzewa
}

//funkcja wpisuajca wartosci z pliku Parameters.txt do obiektu JSON
cJSON* createParametersJSON() {
	char ch;
	cJSON* objectToReturn = cJSON_CreateObject();	//inicjalizacja jsona
	FILE* fp;
	fp = fopen("Parameters.txt", "r");
	int i = 0;
	char word[100];
	char value[100];
	while ((ch = fgetc(fp)) != EOF) {
		if (ch != '\n') {
			word[i] = ch;		//czytamy znak po znaku W a r s z w a az do srednika i przypisujemy W a r s z w a do tablicy znakow
			i++;
		}
		else {
			word[i] = '\0';	//\- zeby zakonczyc string

			char* key = strtok(word, ";");
			int value = atoi(strtok(NULL, ""));
			//cJSON_AddNumberToObject(objectToReturn, word, citiesCounter);	//Dodajemy do naszego JSONA wartosc Warszawa i klucz citiesCounter
			cJSON_AddNumberToObject(objectToReturn, key, value);
			i = 0;
		}

	}
	fclose(fp);
	return objectToReturn;	//zwracamy glowe jsona czyli glowe drzewa
}
/*funkcja wyszukujaca wartosc int dla klucza string
	json - obiekt json w ktorym szukamy wartosci int dla podanego klucza
	string - klucz dla ktorego chcemy poznac wartosc int
*/
int findValueForString(cJSON* json, char* string) {
	while (json->child) {
		if (strcmp(json->child->string,string)==0) {
			return json->child->valueint;
		}
		json->child = json->child->next;
	}
}

/*Funkcja do przechodzenia po drzewie i wyszukiwania wartosci string dla klucza ktory jest typu int
	json - obiekt json w ktorym szukamy wartosci string dla podanego klucza
	index - klucz typu int dla ktorego szukamy wartosci typu string
*/
char * findCityAtIndex(cJSON * json, int index)
{
	while (json->child) {
		if (json->child->valueint == index) {
			return json->child->string;
		}
		json->child = json->child->next;
	}
}
