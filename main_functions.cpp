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
	idrettene.skrivUt();
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
			cout << "Skriv inn 0 for a avbryte\n";
			int nr = les("Skriv inn spillerens nummer", 0, spillere.faaSiste());
			if (nr != 0) spillere.fjernSpiller(nr);
		}
		else cout << "Det finnes ingen spillere.\n";
	}
	else if (valg == 'I')
	{
		//fjerner idrett
		if (idrettene.ikkeTom())
		{
			char navn[STRLEN];
			skrivQ();
			do {
				les("Skriv inn navn pa idretten du vil fjerne", navn, STRLEN);
			} while (!idrettene.harIdrett(navn) && !isQ(navn));
			
			if (!isQ(navn)) idrettene.fjernIdrett(navn);
		}
		else cout << "Det finnes ingen idretter.\n";
	}
	else if (valg == 'D')
	{
		//fjerner divisjon. må vite idrett
		if (idrettene.ikkeTom())
		{
			skrivQ();
			idrettene.fjernDiv();
		}
		else cout << "Det finnes ingen idretter, ergo ingen divisjoner.\n";
	}
	else cout << "Ugyldig kommando\n";
}

// (L)Skriv terminliste for en gitt divisjon til skjerm eller fil
void skrivTerminListe() {
	//skriv inn idrett, div og lag
	char navn[STRLEN];
	cin.ignore();

	// Kjører minst en gang og fortsetter til resultatet er Q eller en eksisterende idrett
	skrivQ();
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

	if (!isQ(navn)) idrettene.skrivTerminListe(navn);
	//hvis idrett eksisterer og idretten skrevet inn ikke er 'Q'
}

// (K)skriv resultatet av alle kampene en gitt dato for ne idrett eller en divisjon til skjerm eller fil
void skrivKampene() {
	
	char navn[STRLEN];            //spør om idrettnavn
	cin.ignore();
	skrivQ();
	les("Skriv inn navn pa idrett", navn, STRLEN);

	while (!idrettene.harIdrett(navn) && !isQ(navn))
	{
		les("Finner ikke idretten. Prov pa nytt", navn, STRLEN);
	}

	if (!isQ(navn)) idrettene.skrivKamp(navn);				//sender med idretten
}

// (T)Skriv tabell(er) for en hel idrett eller en divisjon til fil eller skjerm
void skrivTabell() {
	char navn[STRLEN];
	bool temp;

	skrivQ();

	cin.ignore();
	do {
		// Leser inn en tekst
		les("Skriv inn idrett", navn, STRLEN);

		temp = idrettene.harIdrett(navn);
		if (!isQ(navn) && !temp) cout << "Idretten " << navn << " eksisterer ikke!\n";
	} while (!isQ(navn) && !temp);

	if (!isQ(navn)) idrettene.skrivTabell(navn);
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
	bool temp;	// Midlertidig bool som lar .harIdrett bli kjørt bare en gang hver loop av do loopen
	cin.ignore();

	// Kjører minst en gang og fortsetter til resultatet er Q eller en eksisterende idrett
	skrivQ();
	 // fortsetter så lenge navn != Q
	do
	{
		les("Skriv inn navn pa gyldig idrett", navn, STRLEN);

		temp = idrettene.harIdrett(navn);

		if (!temp && !isQ(navn))
			cout << "Idretten eksisterer ikke!\n";
	} while (!isQ(navn) && !temp);

	if (!isQ(navn)) idrettene.skrivLag(navn);
	//hvis idrett eksisterer og idretten skrevet inn ikke er 'Q'
}

// (E)Endre spillere på et lag(legg til/fjern)
void redigerSpiller() {
	//skriv inn idrett, div og lag
	char navn[STRLEN] = "";
	bool temp;	// Midlertidig bool som lar .harIdrett bli kjørt bare en gang hver loop av do loopen
	cin.ignore();
	
	// Kjører minst en gang og fortsetter til resultatet er Q eller en eksisterende idrett
	skrivQ();
	do  // fortsetter så lenge navn != Q
	{
		les("Skriv inn navn pa gyldig idrett", navn, STRLEN);

		temp = idrettene.harIdrett(navn);

		if (!temp && !isQ(navn))
			cout << "Idretten eksisterer ikke!\n";
		
	} while (!isQ(navn) && !temp); // Loopen er avbrukk gjennom break, det er unødvendig å sjekke om loopen skal fortsette på dette punktet

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