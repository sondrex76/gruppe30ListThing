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
	char valg[STRLEN];
	bool alle = false;
	les("", valg, STRLEN);
	
	if (!strcmp(valg, "A") || !strcmp(valg, "a"))		//hvis alle
	{
		alle = true;
	}
	
		spillere.skrivSpiller(valg, alle);			//skriver spiller

}

// I A <navn> - skriv Alle idrettene eller idretten <nav
void skrivIdrett() {
	//sjekker om man vil ha alle eller navn
	char input[STRLEN];
	les("", input, STRLEN);

	bool alle = false;

	if (!strcmp(input, "a") || !strcmp(input, "A"))
	{
		alle = true;
	}
	idrettene.skrivUt(input, alle);

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
			}
			else if (!isQ(navn))
			{
				cout << "Finner ikke idretten. "
				<< "Skriv inn gyldig idrett eller avbryt med a skrive Q\n";
			}
		} while (nr == 0 && !isQ(navn));
	}
	else cout << "Ugyldig kommando.\n";

}

// F S | I | D - Fjern spiller, idrett eller divisjon
void fjern() {
	char valg = les(true);

	if (valg == 'S')
	{
		//fjerner spiller
		if (spillere.faaSiste())
		{
		int nr = les("Skriv inn spillerens nummer", 0, spillere.faaSiste() - 1);
			spillere.fjernSpiller(nr+1);
		}
		else cout << "Det finnes ingen spillere.\n";
	}
	else if (valg == 'I')
	{
		//fjerner idrett
		if (idrettene.ikkeTom())
		{
			char navn[STRLEN];
			les("Skriv inn navn pa idrett du vil fjerne", navn, STRLEN);
			idrettene.fjernIdrett(navn);
		}
		else cout << "Det finnes ingen idretter.\n";
	}
	else if (valg == 'D')
	{
		//fjerner divisjon. må vite idrett
		if (idrettene.ikkeTom())
		{
			char navn[STRLEN];
			les("Skriv inn navn pa divisjonens idrett", navn, STRLEN);
			idrettene.fjernDiv(navn);
		}
		else cout <<"Det finnes ingen idretter, ergo ingen divisjoner.\n";

	}
	else cout << "Ugyldig kommando";
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
	//skriv inn idrett, div og lag
	char navn[STRLEN];
	les("Skriv inn navn pa idrett", navn, STRLEN);
	if (idrettene.harIdrett(navn))
	{
		idrettene.laglag(navn);
	}
	else cout << "Finner ikke denne idretten.\n";
	//hvis idrett eksisterer

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