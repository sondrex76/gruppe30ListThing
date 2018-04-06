#if !defined(__RESULTAT_H)
#define  __RESULTAT_H

#include <fstream>

class Resultat {
private:
	char dato[9];						// Datoen til resultatet(ååååmmdd)
	int hjemmemaal;						// Hjemmemål
	int bortemaal;						// Bortemål
	bool normalTid;						// Bool som beskriver om kampen endte på normal eller overtid
	int hjemmeSkorer[50];				// Liste over de som skoret på hjemmelaget
	int borteSkorer[50];				// Liste over de som skoret på bortelaget
public:
	Resultat(std::ifstream&, char[9]);	// Konstruktor, leser fra fil
	char* returnDato();					// Returnerer dato
	void lesResultat(std::ifstream&);	// Leser resultater
	void skrivTilFil(std::ofstream&);	// Skriv til fil
	void display();						//viser bare dato og mål nå
	bool erTom();						// Sjekkeer om resultatet er tomt
};

#endif