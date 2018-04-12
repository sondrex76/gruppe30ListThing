#if !defined(__RESULTAT_H)
#define  __RESULTAT_H

#include <fstream>
#include "enumer.h"

class Resultat {
private:
	char dato[9];							// Datoen til resultatet(ååååmmdd)
	int hjemmemaal;							// Hjemmemål
	int bortemaal;							// Bortemål
	bool normalTid;							// Bool som beskriver om kampen endte på normal eller overtid
	int hjemmeSkorer[50];					// Liste over de som skoret på hjemmelaget
	int borteSkorer[50];					// Liste over de som skoret på bortelaget
public:
	Resultat(std::ifstream&, char[9]);		// Konstruktor, leser fra fil
	char* returnDato();						// Returnerer dato
	void lesResultat(std::ifstream&);		// Leser resultater
	void skrivTilFil(std::ofstream&);		// Skriv til fil
	void skrivTabell(std::ofstream&);		// Skriver en leselig tabell
	void displayTabell();					// Display, tabellform
	void display();							// Viser bare dato og mål nå
	void fjernSpiller(int);					// Fjerner spiller fra resultater og oppdaterer data
	int poengResultat(TabellType, bool);	// Gir resultat fra kampen(hjemme hvis boolen er sann)
	bool erTom();							// Sjekkeer om resultatet er tomt
};

#endif