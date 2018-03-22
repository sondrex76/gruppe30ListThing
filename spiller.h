#if !defined(__SPILLER_H)
#define  __SPILLER_H

#include <fstream>
#include "ListTool2B.h"

// Er sort etter unikt nummer for spilleren
class Spiller : public NumElement {
private:
	char* navn;		// Peker til navn
	char* adresse;	// Peker til adresse
public:
	Spiller(int);
	Spiller(int value, std::ifstream&);
	Spiller(int, char*, char*);		// Konstruktor når man bytter ID
	~Spiller();						// Destruktor
	void display();					// Skriver spillerens navn og adresse
	char* hentNavn();				//returnerer 'navn'
	void skrivTilFil(std::ofstream&);
};

#endif