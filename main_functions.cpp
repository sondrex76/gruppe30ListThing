#include <iostream>
#include "main_functions.h"
#include "globale_funksjoner.h"
#include "idrettene.h";


using namespace std;
//
//	Hovedfunksjoner
//
Idrettene idrettene;						//ekstern (?)

// S A | <nr> | <navn> - skriv Alle spillere eller spiller med <nr> / <navn>
void skrivSpiller() {

}

// I A <navn> - skriv Alle idrettene eller idretten <nav
void skrivIdrett() {

}

// N S | I  D - Ny spiller, idrett eller divisjon
void lagNy() {
	char onske = les(false);

	if (onske == 'S')
	{
		//lager ny spiller. må vite idrett og lag
		cout << "Spiller";

	}
	else if (onske == 'I')
	{
		//lager ny idrett
		cout << "Idrett";
		idrettene.opprett();
	}
	else if (onske == 'D')
	{
		//lager ny divisjon
		cout << "div";
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