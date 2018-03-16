#include <iostream>
#include "ListTool2B.h"
#include "spillere.h"
#include "idrettene.h"
#include "globale_funksjoner.h"

using namespace std;

void skrivMeny();

int main() {
	char kommando;
	
	do
	{
		skrivMeny();
	
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
		}
	} while (kommando != 'Q');


	int x; cin >> x;
	return 0;
}


void skrivMeny()
{
	cout << "TILGJENGELIGE KOMMANDOER:\n"
		 << "S : | A - alle | <nr> | <navn | \t - viser spillere\n"
		 << "I : | A - alle | <navn> | \t - viser idretter\n"
<< "N : | S - spiller | I - idrett | D - div/avd | \t - lager ny s/i/d\n"
<< "F : | S - spiller | I - idrett | D - div/avd | \t - fjerner s/i/d\n"
		 << "L - skriver terminliste for 1 div/avd til skjerm/fil\n"
		 << "K - kamper gitt en dato for en hel idrett eller 1 div/avd"
		 <<"til skjerm/fil\n"
<<"T - skriv tabeller for en hel idrett eller div/avd til skjerm/fil\n"
		 <<"R - lese inn resultatliste fra fil\n"
		 <<"D - skriver alle spillernes data pa et lag\n"
		 <<"E - endre eller redigere spillerne på et lag\n"
		 <<"Q - avslutt program\n\n"; 
}