#if !defined(__RESULTAT_H)
#define  __RESULTAT_H

#include <fstream>

class Resultat {
private:
	char dato[9];						// Datoen til resultatet(����mmdd)
	int hjemmemaal;						// Hjemmem�l
	int bortemaal;						// Bortem�l
	bool normalTid;						// Bool som beskriver om kampen endte p� normal eller overtid
	int hjemmeSkorer[50];				// Liste over de som skoret p� hjemmelaget
	int borteSkorer[50];				// Liste over de som skoret p� bortelaget
public:
	Resultat(std::ifstream&, char[9]);	// Konstruktor, leser fra fil
	char* returnDato();					// Returnerer dato
	void lesResultat(std::ifstream&, bool);
	void skrivTilFil(std::ofstream&);	// Skriv til fil
};

#endif