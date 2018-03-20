#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream>
#include <iostream>
#include "lag.h"
#include "conster.h"

using namespace std;

// Standard konstruktor
Lag::Lag() {

}

// Konstruktor for å lese fra fil
Lag::Lag(ifstream& inn) {
	char tempChar[MAXSPILLERE * 3];

	inn.getline(tempChar, STRLEN);			// Henter navn av lag
	navn = new char[strlen(tempChar)];
	strcpy(navn, tempChar);					// Oppdaterer navn

	inn.getline(tempChar, STRLEN);			// Henter lagets adresse
	adresse = new char[strlen(tempChar)];
	strcpy(adresse, tempChar);				// Oppdaterer navn

	inn >> antSpillere;						// Henter antall spillere
	inn.ignore();

	// cout << "Navn: " << navn << "\nAdresse: " << adresse << "\nantSpillere: " << antSpillere << std::endl; // DEBUG

	for (int i = 0; i < antSpillere; i++)
	{
		spillerID[i] = new int;
		inn >> *(spillerID[i]); // endrer verdien til spillerID[i]
		// cout << *spillerID[i] << ", "; // DEBUG
	}
	// cout << std::endl; // DEBUG
	inn.ignore();
}

// Skriver lagets data til fil
void Lag::skrivTilFil(ofstream& ut) {
	ut << navn << endl;		// Navn
	ut << adresse << endl;		// Adresse
	ut << antSpillere << endl;	// Antall spillere

	for (int i = 0; i < antSpillere; i++)
	{
		ut << *spillerID[i]; // Skriver ut unik ID til alle spillere
		if (i != antSpillere - 1) ut << " ";	// Legger til et space hvis det ikke er den siste verdien
	}

	ut << endl << endl;					// Linjeskift
}