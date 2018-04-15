#if !defined(__DIV_AVD_H)
#define  __DIV_AVD_H

#include <fstream>
#include "ListTool2B.h"
#include "lag.h"
#include "resultat.h"
#include "conster.h"
#include "enumer.h"

// Er en divisjon/avdeling av en sport
// Sortert etter navn av divisjon/avderling
class DivAvd : public TextElement {
private:
	int antLag;								// Antall lag i divisjon
	Lag* lag[30];							// Lagene i divisjonen
	Resultat* resultater[MAXLAG][MAXLAG];	// Matrise med pekere til resultater
public:
	DivAvd(char*, std::ifstream&, bool);
	~DivAvd();								// Destruktor
	char* hentNavn();						//returnerer 'navn'
	void skrivTerminListe();
	void skrivLag();
	void redigerSpiller();
	void sjekkDato(char*, int, int);
	void sjekkDatoFil(char*, int, int, std::ofstream&);
	void display();
	bool lesResultat(bool, std::ifstream&);
	void fjernSpiller(int);	// Fjerner spiller fra divisjon og lag og oppdaterer andre data
	void skrivTabell(TabellType, char*);
	void skrivTabellFil(TabellType, char*, std::ofstream&);
	void skrivTilFil(std::ofstream&);
};

#endif