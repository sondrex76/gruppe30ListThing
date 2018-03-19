#include <fstream>
#include <iostream> // DEBUG
#include "spiller.h"
#include "conster.h"

using namespace std;

// Standard konstruktor
Spiller::Spiller(int value) : NumElement(value){

}

// Konstruktor brukt når man leser fra fil
Spiller::Spiller(int value, ifstream& inn) : NumElement(value) {
	char tempChar[STRLEN];
	inn.getline(tempChar, STRLEN);			// Henter navn

	navn = new char[strlen(tempChar)];		// Setter navnets lengde
	navn = tempChar;						// Definerer navn
	

	char temp[STRLEN];
	inn.getline(temp, STRLEN);

	adresse = new char[strlen(temp)];	// Setter adressens lengde
	adresse = temp;						// Definerer adresse

	cout << "Navn: " << navn << "\nAdresse: " << adresse << endl; // DEBUG
}