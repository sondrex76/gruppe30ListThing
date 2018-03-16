#if !defined(__SPILLER_H)
#define  __SPILLER_H

#include "ListTool2B.h"

// Er sort etter unikt nummer for spilleren
class Spiller : NumElement {
private:
	char* navn;		// Peker til navn
	char* adresse;	// Peker til adresse
public:
	Spiller();
	void skrivSpiller(); // Skriver spillerens navn og adresse
};

#endif