#if !defined(__IDRETT_H)
#define  __IDRETT_H

#include <fstream>
#include "ListTool2B.h"
#include "enumer.h"

// Er sortert etter dets navn
class Idrett : public TextElement {
private:
	TabellType tabellType;							// Enum som lagrer typen tabell(2/1/0, 3/1/0, 3/2/1/0) brukt i idretten
	List* divAvdListe;								// Liste av alle divisjoner/avdelinger av idretten
public:
	Idrett(char*);									// Standard konstruktor
	Idrett(char*, std::ifstream&);					// Konstruktor som leser data fra fil
	~Idrett();										// Destruktor
	bool leggTilDiv(std::ifstream&, char*);	// Legger til ny div fra fil
	void slettDiv();
	bool likSom(char*);						//returnerer om navnene er like
	void skrivTerminListe();
	void skrivLag();
	void redigerSpiller();
	void skrivKamp();
	void display();									// Displayer I A spesifik info
	void displayResten();							// Displayer I <navn> spesifik info
	void skrivTabell();								// Skriver ut tabell av divisjon eller helt lag
	void fjernSpiller(int);							// Fjerner en spiller fra alle divisjoner i alle idretter og oppdaterer andre data
	char* hentNavn();								//returnerer navn
	bool lesResultat(bool, std::ifstream&);
	void skrivTilFil(std::ofstream&);
};

#endif