#if !defined(__IDRETTENE_H)
#define  __IDRETTENE_H

#include "ListTool2B.h"
#include "enumer.h"
class Idrettene {
private:
	List* idrettListe;
	
public:
	Idrettene();
	void opprett();
	int faaNr(char*);				//returnerer nr i lista. evt 0
	void leggTilDiv(int);			//legger til ny divisjon
	void fjernIdrett(char*);		// Fjerner en idrett
	void fjernDiv();					// Fjerner en divisjon
	bool harIdrett(char*);			// Sjekekr om idretten finnes
	void skrivTerminListe(char*);	// Skriver teminliste
	void skrivKamp(char*);			// Skriver ut kamp
	void skrivLag(char*);			// Skriver lag
	void redigerSpiller(char*);	// Redigerer spiller
	bool ikkeTom();						//returnerer om lista er tom
	void skrivUt();						// Skriver ut data
	bool lesResultat(bool);				// Leser inn fra RESULTAT.DTA eller sjekker om den er gyldig
	void skrivTabell(char*);			// Skriver ut tabell av idrett eller div til fil eller skjerm
	void fjernSpiller(int);				// fjerner spiller fra alle divisjoner av alle idretter, og oppdaterer alle id-er over den
	void lesFraFil();					// Leser fra fil
	void skrivTilFil();					// Skriver til fil
};

#endif