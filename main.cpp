#include <iostream>
#include "ListTool2B.h"
#include "spillere.h"
#include "idrettene.h"
#include "globale_funksjoner.h"

using namespace std;

void skrivMeny();

int main() {
	char kommando;

	skrivMeny();

	do
	{
		cout << "Skriv inn kommando: ";
		cin >> kommando;
		kommando = toupper(kommando);

		switch (kommando)
		{
		case 'S': skrivSpiller(); break;
		case 'I':; break;
		case 'N':; break;
		case 'F':; break;
		case 'L':; break;
		case 'K':; break;
		case 'T':; break;
		case 'R':; break;
		case 'D':; break;
		case 'E':; break;
		default: skrivMeny();
		}
	} while (kommando != 'Q');


	int x; cin >> x;
	return 0;
}


void skrivMeny()
{
	cout << "TILGJENGELIGE KOMMANDOER:\n"
		 << "\tS : | A - alle | <nr> | <navn | \t - viser spillere\n"
		 << "\tI : | A - alle | <navn> | \t - viser idretter\n"
		<< "\tN : | S - spiller | I - idrett | D - div/avd | \t - lager ny s/i/d\n"
		<< "\tF : | S - spiller | I - idrett | D - div/avd | \t - fjerner s/i/d\n"
		 << "\tL - skriver terminliste for 1 div/avd til skjerm/fil\n"
		 << "\tK - kamper gitt en dato for en hel idrett eller 1 div/avd til skjerm/fil\n"
		<<"\tT - skriv tabeller for en hel idrett eller div/avd til skjerm/fil\n"
		 <<"\tR - lese inn resultatliste fra fil\n"
		 <<"\tD - skriver alle spillernes data pa et lag\n"
		 <<"\tE - endre eller redigere spillerne på et lag\n"
		 <<"\tQ - avslutt program\n\n"; 
}