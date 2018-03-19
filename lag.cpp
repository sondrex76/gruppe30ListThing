#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include "lag.h"
#include <fstream>
#include "conster.h"

// Standard konstruktor
Lag::Lag() {

}

// Konstruktor for � lese fra fil
Lag::Lag(std::ifstream& inn) {
	char tempChar[MAXSPILLERE * 3];

	inn.getline(tempChar, STRLEN);			// Henter navn av lag
	navn = new char[strlen(tempChar)];
	strcpy(navn, tempChar);					// Oppdaterer navn

	inn.getline(tempChar, STRLEN);			// Henter navn av lag
	adresse = new char[strlen(tempChar)];
	strcpy(adresse, tempChar);				// Oppdaterer navn

	inn >> antSpillere;						// Henter antall spillere
	inn.ignore();

	for (int i = 0; i < antSpillere; i++)
	{
		spillerID[i] = new int;
		inn >> *spillerID[i]; // endrer verdien til spillerID[i]
	}

	inn.ignore();
}