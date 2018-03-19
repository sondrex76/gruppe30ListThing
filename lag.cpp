#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream>
#include <iostream>
#include "lag.h"
#include "conster.h"

// Standard konstruktor
Lag::Lag() {

}

// Konstruktor for å lese fra fil
Lag::Lag(std::ifstream& inn) {
	char tempChar[MAXSPILLERE * 3];

	inn.getline(tempChar, STRLEN);			// Henter navn av lag
	navn = new char[strlen(tempChar)];
	strcpy(navn, tempChar);					// Oppdaterer navn

	inn.getline(tempChar, STRLEN);			// Henter lagets adresse
	adresse = new char[strlen(tempChar)];
	strcpy(adresse, tempChar);				// Oppdaterer navn

	inn >> antSpillere;						// Henter antall spillere
	inn.ignore();

	std::cout << "Navn: " << navn << "\nAdresse: " << adresse << "\nantSpillere: " << antSpillere << std::endl;

	for (int i = 0; i < antSpillere; i++)
	{
		spillerID[i] = new int;
		inn >> *(spillerID[i]); // endrer verdien til spillerID[i]
		std::cout << *spillerID[i] << ", ";
	}
	std::cout << std::endl;
	inn.ignore();
}