#if !defined(__RESULTAT_H)
#define  __RESULTAT_H

class Resultat {
private:
	char dato[9];			// Datoen til resultatet(����mmdd)
	int bortemaal;			// Bortem�l
	int Hjemmemaal;			// Hjemmem�l
	bool normalTid;			// Bool som beskriver om kampen endte p� normal eller overtid
	int borteSkorer[50];	// Liste over de som skoret p� bortelaget
	int hjemmeSkorer[50];	// Liste over de som skoret p� hjemmelaget
public:

};

#endif