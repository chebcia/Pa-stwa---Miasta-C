#include "cJSON.h"
#include "Menu.h"
/*
	argc - ilosc argumentow z linii komend
	argv - argumenty z linii komend
*/
int main(int argc, char* argv[]) {
	struct List* head = loadData('\0', 0, 0);	//£adujemy dane z pliku do programu
	handleCommandLineArguments(argc, argv, head);
	return 0;
}