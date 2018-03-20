#if !defined(__SPILLERE_H)
#define  __SPILLERE_H

#include "ListTool2B.h"

// Klasse som holder alle spilelre og siste nummer, samt spiller relaterte funksjoner
class Spillere {
private:
	List* spillerListe;		// Liste av spiller objekter
	int sisteNummer;	// Siste nummer brukt, megden spillere(fra 1-sisteNummer)
public:
	Spillere();			// Konstruktor
	void lagSpiller();
	void lesFraFil();
	void skrivTilFil();
};



#endif