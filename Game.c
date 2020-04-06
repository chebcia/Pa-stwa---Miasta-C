#include "Game.h"
#include <time.h> 

//funkcja do wyboru poziomu trudnosci, wyswietla opcje trudnosci
int chooseDificulty()
{
	system("@cls||clear");
	int choice;
	printf("wybierz poziom trudnosci:\n");
	printf("1.Trudny (dokladnosc do 1m)\n");
	printf("2.Sredni (dokladnosc do 10m)\n");
	printf("3.Latwy (dokladnosc do 50m)\n");
	scanf("%d", &choice);

	return choice;
}
//funkcja do wyboru jednostek ktore beda uzywane do gry, wyswietla opcje
double chooseUnits()
{
	system("@cls||clear");
	int choice;
	printf("wybierz jednostki w ktorych bedziesz wprowadzac wyniki:\n");
	printf("1.Kilometry\n");
	printf("2.Jardy\n");
	printf("3.Mile\n");
	scanf("%d", &choice);
	double(*multiplayer)(int) = &unitMultiplayer;
	return (*multiplayer)(choice);
}
/*funkcja zwracajaca mnoznik jednostki wybranej przez uzytkownika
	choice - indeks wybranej jednostki

*/
double unitMultiplayer(int choice) {
	switch (choice)
	{
	case 1:
		return 1.0;
	case 2:
		return 1093.61;
	case 3:
		return 0.63;
	default:
		return 1.0;
	}
	return 1.0;
}
/*funkcja wybierajaca losowe i niepowtarzalne miasto i jednoczesnie odpalajaca zgadywanie
	dificulty - poziom trudnosci wybrany przez uzytkownika
	units - mnoznik dla jednostki wybranej przez uzytkownika
	data - odleglosci z miasta poczatkowego do reszty miast wyliczone algorytmem dijkstry
	chosenIndex - miasto poczatkowe wybrane przez uzytkownika
	size - ilosc miast
*/
void chooseRandom(int dificulty, double units, int data[], int chosenIndex, int size)
{
	int points = 0; //punkty ktore gracz zarobi
	int indices[INITIAL_ARRAY_SIZE];	//indeksy miast, jest nam to potrzebne po to zeby je usuwac i zeby sie nie powtarzaly
	int howMany = 5; //ile razy uzytkownik powinien byc spytany o odpowiedz
	if (size < 5) {	//zabezpieczenie jezeli mamy mniej miast niz 5
		howMany = size;
	}
	for (int i = 0; i < size - 1; i++) {
		if (i >= chosenIndex - 1)
			indices[i] = i + 1;
		else
			indices[i] = i;
	}
	size -= 1;
	for (int i = 0; i < howMany; i++) {
		srand(time(NULL));
		int randomIndex = (rand() % (size));	//losowanie indeksu miast
		points += play(data, dificulty, units, indices[randomIndex]);	//dodajemy punkty
		system("@cls||clear");
		printf("Twoj wynik to: %d\n", points);
		for (int j = randomIndex; j < size; j++) {	//zebyy sie miasta nie powtarzaly
			indices[j] = indices[j + 1];
		}
		size = size - 1;
	}
	getchar();	//potrzebne zeby uzyc menu
}
/*funkcja pytajaca uzytkownika o odleglosci
	unitMultiplier - mnoznik dla jednostki wybranej przez uzytkownika
	difficulty - poziom trudnosci wybrany przez uzytkownika
	data - odleglosci z miasta poczatkowego do reszty miast wyliczone algorytmem dijkstry
	cityIndex - miasto poczatkowe wybrane przez algorytm losowania
*/
int play(int data[], int dificulty, double unitMultiplier, int cityIndex) {
	cJSON* json = createJSON();
	int distance;
	printf("podaj odleglosc do miasta: %s\n", findCityAtIndex(json, cityIndex));
	scanf("%d", &distance);

	int difference = abs(distance - data[cityIndex] * unitMultiplier);
	switch (dificulty)
	{
	case 1:
		if (difference <= 1)
			return 1;
		else
			return 0;
	case 2:
		if (difference <= 10)
			return 1;
		else
			return 0;
	case 3:
		if (difference <= 50)
			return 1;
		else
			return 0;
	default:
		return 0;
	}
}
