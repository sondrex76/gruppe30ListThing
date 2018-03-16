#if !defined(__LAG_H)
#define  __LAG_H

class Lag {
private:
	char* navn;			// Navnet på laget
	char* adresse;		// Adressen/stedet til laget
	int antSpillere;	// Antall spillere på laget
	int spillerID[50];	// Det unike nummeret til hver spiller
public:
	Lag();
};

#endif