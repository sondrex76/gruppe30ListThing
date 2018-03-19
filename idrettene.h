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
	void lesFraFil();
	void skrivTilFil();
};

#endif