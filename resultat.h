#if !defined(__RESULTAT_H)
#define  __RESULTAT_H

class Resultat {
private:
	char dato[9];			// Datoen til resultatet(ååååmmdd)
	int bortemaal;			// Bortemål
	int Hjemmemaal;			// Hjemmemål
	bool normalTid;			// Bool som beskriver om kampen endte på normal eller overtid
	int borteSkorer[50];	// Liste over de som skoret på bortelaget
	int hjemmeSkorer[50];	// Liste over de som skoret på hjemmelaget
public:

};

#endif