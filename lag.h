#if !defined(__LAG_H)
#define  __LAG_H

#include <fstream>

class Lag {
private:
	char* navn;			// Navnet p� laget
	char* adresse;		// Adressen/stedet til laget
	int antSpillere;	// Antall spillere p� laget
	int* spillerID[50];	// Det unike nummeret til hver spiller
public:
	Lag();
	Lag(std::ifstream&);
	void skrivTilFil(std::ofstream&);

	void display();
};

#endif