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
	bool leggTilDiv(std::ifstream&, char* navn);	// Legger til ny div fra fil
	void slettDiv();
	bool harIkkeDiv(char* navn);					//returnerer om div ikke finnes
	bool likSom(char* navn);						//returnerer om navnene er like
	bool harDiv(char* navn);						//returnerer om har en viss div
	void redigerSpiller();
	void display();									// Displayer I A spesifik info
	void displayResten();							// Displayer I <navn> spesifik info
	void skrivTilFil(std::ofstream&);
	char* hentNavn();								//returnerer navn
};

#endif