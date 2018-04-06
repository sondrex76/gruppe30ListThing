#include <iostream>

#include "ListTool2B.h"
#include "spillere.h"
#include "idrettene.h"
#include "main_functions.h"
#include "globale_funksjoner.h"
#include "spillere.h"

using namespace std;

// Globale variabler
Spillere spillere;		// Objekt som inneholder alle spillerne(spiller-objekter), og det siste unike nummeret som har blitt utdelt
Idrettene idrettene;	// Objekt som inneholder alle idretter

void skrivMeny();

int main() {
	char kommando;

	// lesFraFil er ikke ferdig enda og går i en uendelig loop for øyeblikket, skal fikse den senere, har ikke hatt frokost enda
	lesFraFil();	// Leser data fra fil
	skrivMeny();	// Skriver menyen

	do
	{
		cout << "Skriv kommando: ";
		kommando = les(false);

		switch (kommando)
		{
		case 'S': skrivSpiller(); break;
		case 'I': skrivIdrett(); break;
		case 'N': lagNy(); break;
		case 'F': fjern(); break;
		case 'L': skrivTerminListe(); break;
		case 'K': skrivKampene(); break;
		case 'T': skrivTabell(); break;
		case 'R': lesResultat(); break;
		case 'D': skrivLag(); break;
		case 'E': redigerSpiller(); break;
		case 'Q': break;
		default: skrivMeny();
		}
	} while (kommando != 'Q');

	// Skriver endringer til fil
	skrivTilFil();

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
		 <<"\tE - endre eller redigere spillerne pa et lag\n"
		 <<"\tQ - avslutt program\n\n"; 
}