#if !defined(__SPILLERE_H)
#define  __SPILLERE_H

#include <fstream>
#include "ListTool2B.h"

// Klasse som holder alle spilelre og siste nummer, samt spiller relaterte funksjoner
class Spillere {
private:
	List* spillerListe;		// Liste av spiller objekter
	int sisteNummer;	// Siste nummer brukt, megden spillere(fra 1-sisteNummer)
public:
	Spillere();			// Konstruktor
	int faaSiste();							//returnerer 'sisteNummer'
	bool eksisterer(int);		// Funksjon som sjekker om spiller med id int eksisterer
	void skrivSpiller(char*, bool);		//skriver ut
	void fjernSpiller(int);
	void lagSpiller();
	void lesSpillerFraFil(int, std::ifstream&);
	void lesFraFil();			// Leser spiller data fra fil
	void skrivTilFil();			// Skriver spiller data til fil
};



#endif