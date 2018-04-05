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
	int faaNr(char* nvn);				//returnerer nr i lista. evt 0
	void leggTilDiv(int nr);			//legger til ny divisjon
	void fjernIdrett(char* navn);		
	void fjernDiv(char* navn);
	bool harIdrett(char* navn);
	void skrivDato(char* navn);
	void skrivLag(char* navn);
	void redigerSpiller(char* navn);
	bool ikkeTom();						//returnerer om lista er tom
	void skrivUt(char* navn, bool alle);
	bool lesResultat(bool, std::ifstream&);
	void lesFraFil();
	void skrivTilFil();
};

#endif