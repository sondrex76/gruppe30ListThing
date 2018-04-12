#if !defined(__LAG_H)
#define  __LAG_H

#include <fstream>

class Lag {
private:
	char* navn;			// Navnet på laget
	char* adresse;		// Adressen/stedet til laget
	int antSpillere;	// Antall spillere på laget
	int* spillerID[50];	// Det unike nummeret til hver spiller
public:
	Lag();
	Lag(std::ifstream&, bool);
	~Lag();				// Destruktor
	void skrivTilFil(std::ofstream&);
	char* sendNavn();
	void skrivLag();
	void fjernSpiller();
	void fjernSpiller(int);		// Fjerner spiller fra lag og returnerer true hvis en er fjernet
	void leggTilSpiller();
	void display();
};

#endif