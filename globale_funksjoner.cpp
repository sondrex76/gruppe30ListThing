# include <iostream>
#include "globale_funksjoner.h"

using namespace std;
//
//	les() funksjoner
//

// Returnerer en int mellom min og max
int les(char* info, int min, int max)
{
	int verdi; // Lagrer verdien man skriver inn

	do {
		cout << '\t' << info << "(" << min << "-" << max << ")"; // Printer ut info i tilleg til "(min-max)"
		cin >> verdi; // Henter verdien
		cin.ignore();
	} while (verdi > max || verdi < min); // checks if value is valid

	return verdi;
}

// Leser en enkelt char
char les(bool ignorerAndre)
{
	char ch;
	cin >> ch;

	// Ignorerer resten av karakterene hvis ignorerAndre == true
	if (ignorerAndre) cin.ignore();
	
	return toupper(ch);
}

// Returnerer en ikke tom string skrevet av brukeren
void les(char* info, char* txt, int MAXLEN)
{
	do {
		cout << '\t' << info << ": ";
		cin.getline(txt, MAXLEN);	// Henter en linje fra brukeren og kopierer den over til txt
	} while (strlen(txt) == 0);	// Forsikrer at brukeren ikke bare skrev inn enter
}

//
//	Hovedfunksjoner
//

// S A | <nr> | <navn> - skriv Alle spillere eller spiller med <nr> / <navn>
void skrivSpiller() {

}

// I A <navn> - skriv Alle idrettene eller idretten <nav
void skrivIdrett() {

}

// N S | I  D - Ny spiller, idrett eller divisjon
void lagNy() {

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