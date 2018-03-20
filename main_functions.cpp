#include <iostream>

#include "main_functions.h"
#include "globale_funksjoner.h"
#include "idrettene.h"
#include "spillere.h"
#include "conster.h"

using namespace std;

extern Idrettene idrettene;
extern Spillere spillere;

// S A | <nr> | <navn> - skriv Alle spillere eller spiller med <nr> / <navn>
void skrivSpiller() {

}

// I A <navn> - skriv Alle idrettene eller idretten <nav
void skrivIdrett() {

}

// N S | I  D - Ny spiller, idrett eller divisjon
void lagNy() {
	char onske = les(true);

	if (onske == 'S')
	{
		//lager ny spiller. må vite idrett og lag
		spillere.lagSpiller();
	}
	else if (onske == 'I')
	{
		idrettene.opprett();						// Lager ny idrett
	}
	else if (onske == 'D')
	{
		//lager ny divisjon. spør om hvilken idrett.
		char navn[STRLEN];

		//sjekker at idretten finnes
		int nr;

		do {
			les("Skriv inn idretten du onsker ny div/avd i", navn, STRLEN);
			nr = idrettene.faaNr(navn);

			if (nr)
			{
					idrettene.leggTilDiv(nr);		// Legg til div/avd
					cout << "TEST\n";
			}
			else if (!isQ(navn))
			{
				cout << "Finner ikke idretten.\n";
				cout << "Skriv inn gyldig idrett eller avbryt med å skrive Q\n";
			}
		} while (nr == 0 && !isQ(navn));
	}
	else cout << "Ugyldig kommando.\n";

}

// F S | I | D - Fjern spiller, idrett eller divisjon
void fjern() {

}

// L Skriv terminliste for en gitt divisjon til skjerm eller fil
void skrivTerminListe() {

}

// (K)skriv resultatet av alle kampene en gitt dato for ne idrett eller en divisjon til skjerm eller fil
void skrivKampene() {

}

// (T)Skriv tabell(er) for en hel idrett eller en divisjon til fil eller skjerm
void skrivTabell() {

}

// (R)Les resultatliste fra fil
void lesResultat() {

}

// (D)Data om alle spillerne i et lag
void skrivLag() {

}

// (E)Endre spillere på et lag(legg til/fjern)
void redigerSpiller() {

}

// Leser data fra fil
void lesFraFil() {
	idrettene.lesFraFil();
	spillere.lesFraFil();
}

// Skriver data til fil
void skrivTilFil() {
	idrettene.skrivTilFil();
	spillere.skrivTilFil();
}