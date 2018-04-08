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
	
	cout << "A = Alle | <nummer> = skriv ut nummer | <navn> = skriv ut <navn>\n";

	// Leser inn resultat
	les("", valg, STRLEN, false);
	cout << endl;

	// Sjekker om alle skal skrives ut
	if (isQ(valg, 'A'))		// Hvis alle
		alle = true;
	
	spillere.skrivSpiller(valg, alle);			// Skriver spiller
		
}

// I A <navn> - skriv Alle idrettene eller idretten <nav
void skrivIdrett() {
	//sjekker om man vil ha alle eller navn
	char input[STRLEN];
	les("", input, STRLEN, false);

	bool alle = false;

	if (isQ(input, 'A'))
	{
		alle = true;
	}

	idrettene.skrivUt(input, alle);
}

// N S | I  D - Ny spiller, idrett eller divisjon
void lagNy() {
	char onske = les(true);

	
	if (onske == 'S') // Lager ny spiller. må vite idrett og lag
	{
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
				cout << "Finner ikke idretten.\n";
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
			int nr = les("Skriv inn spillerens nummer", 1, spillere.faaSiste());
			spillere.fjernSpiller(nr);
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
		else cout << "Det finnes ingen idretter, ergo ingen divisjoner.\n";
	}
	else cout << "Ugyldig kommando";
}

// L Skriv terminliste for en gitt divisjon til skjerm eller fil
void skrivTerminListe() {

}

// (K)skriv resultatet av alle kampene en gitt dato for ne idrett eller en divisjon til skjerm eller fil
void skrivKampene() {
	char navn[STRLEN];            //spør om idrettnavn
	cin.ignore();
	les("Skriv inn navn pa idrett", navn, STRLEN);

	while (!idrettene.harIdrett(navn))
	{
		les("Finner ikke idretten. Prov pa nytt", navn, STRLEN);
	}

	idrettene.skrivKamp(navn);				//sender med idretten
}

// (T)Skriv tabell(er) for en hel idrett eller en divisjon til fil eller skjerm
void skrivTabell() {

}

// (R)Les resultatliste fra fil
void lesResultat() {
	if (idrettene.lesResultat(false)) // Sjekker om resultater fra RESULTAT.DTA er akseptable 
		idrettene.lesResultat(true); // Leser inn resultater fra RESULTAT.DTA 
}

// (D)Data om alle spillerne i et lag
void skrivLag() {
	//skriv inn idrett, div og lag
	char navn[STRLEN];
	cin.ignore();

	// Kjører minst en gang og fortsetter til resultatet er Q eller en eksisterende idrett
	cout << "Skriv Q for å avbryte\n";
	 // fortsetter så lenge navn != Q
	do
	{
		les("Skriv inn navn pa gyldig idrett", navn, STRLEN);

		if (!idrettene.harIdrett(navn) && !isQ(navn))
			cout << "Idretten eksisterer ikke!\n";
		else if (idrettene.harIdrett(navn)) break; // Avbryter loopen
	} while (!isQ(navn));
	// Loopen er avbrukk gjennom break,
	// det er unødvendig å sjekke om loopen skal fortsette på dette punktet

	if (!isQ(navn)) idrettene.skrivLag(navn);
	//hvis idrett eksisterer og idretten skrevet inn ikke er 'Q'
}

// (E)Endre spillere på et lag(legg til/fjern)
void redigerSpiller() {
	//skriv inn idrett, div og lag
	char navn[STRLEN] = "";
	cin.ignore();
	
	// Kjører minst en gang og fortsetter til resultatet er Q eller en eksisterende idrett
	cout << "Skriv q for å avbryte\n";
	while (!isQ(navn)) // fortsetter så lenge navn != Q
	{

		les("Skriv inn navn pa gyldig idrett", navn, STRLEN);

		if (!idrettene.harIdrett(navn) && !isQ(navn))
			cout << "Idretten eksisterer ikke!\n";
		else if (idrettene.harIdrett(navn)) break;
		
	} // Loopen er avbrukk gjennom break, det er unødvendig å sjekke om loopen skal fortsette på dette punktet

	if (!isQ(navn)) idrettene.redigerSpiller(navn);
	//hvis idrett eksisterer og idretten skrevet inn ikke er 'Q'

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