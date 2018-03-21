#if !defined(__DIV_AVD_H)
#define  __DIV_AVD_H

#include <fstream>
#include "ListTool2B.h"
#include "lag.h"
#include "resultat.h"
#include "conster.h"

// Er en divisjon/avdeling av en sport
// Sortert etter navn av divisjon/avderling
class DivAvd : public TextElement {
private:
	int antLag;								// Antall lag i divisjon
	Lag* lag[30];							// Lagene i divisjonen
	Resultat* resultater[MAXLAG][MAXLAG];	// Matrise med pekere til resultater
public:
	DivAvd(char*, std::ifstream&, bool);
	char* hentNavn();						//returnerer 'navn'
	void lagLag();
	void leggTilSpiller();
	void display();
	void skrivTilFil(std::ofstream&);
};

#endif