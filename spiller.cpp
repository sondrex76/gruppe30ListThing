#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream> // DEBUG
#include "globale_funksjoner.h"
#include "spiller.h"
#include "conster.h"


using namespace std;

// Standard konstruktor
Spiller::Spiller(int value) : NumElement(value){
										//spør om navn og adresse
	// Henter navn
	char nvn[STRLEN];
	les("Skriv inn spillernavn", nvn, STRLEN);
	navn = new char[strlen(nvn) + 1];
	strcpy(navn, nvn);

	// Henter adresse
	char adr[STRLEN];
	les("Skriv inn adresse", adr, STRLEN);
	adresse = new char[strlen(adr) + 1];
	strcpy(adresse, adr);

	cout << "Spiller nummer: " << number << endl;	// Skriver ut spillerens unike nummer
}

// Konstruktor brukt når man leser fra fil
Spiller::Spiller(int value, ifstream& inn) : NumElement(value) {
	char tempChar[STRLEN];
	inn.getline(tempChar, STRLEN);			// Henter navn

	navn = new char[strlen(tempChar) + 1];		// Setter navnets lengde
	strcpy(navn, tempChar);					// Definerer navn

	char temp[STRLEN];
	inn.getline(temp, STRLEN);

	adresse = new char[strlen(temp) + 1];	// Setter adressens lengde
	strcpy(adresse, temp);				// Definerer adresse

	// cout << "Navn: " << navn << "\nAdresse: " << adresse << endl; // DEBUG
}

Spiller::Spiller(int value, Spiller* temp) : NumElement(value) {
	// Lager ny char* med lengden av navnet til temp og kopierer verdien
	navn = new char[strlen(temp->navn) + 1];
	strcpy(navn, (temp->navn));

	// Lager ny char* med lengden av adressen til temp og kopierer verdien
	adresse = new char[strlen((temp->adresse)) + 1];
	strcpy(adresse, (temp->adresse));
	
	// cout << navn << endl << adresse << endl << "TEST\n\n"; // DEBUG
}

// Destruktor, deleter navn og adresse
Spiller::~Spiller() {
	delete navn;
	delete adresse;
	navn = nullptr;
	adresse = nullptr;
}

// DEBUG, burde bli brukt i faktisk kode senere

char* Spiller::hentNavn()
{
	return navn;
}


void Spiller::display()
{
	cout << "Navn: " << navn << endl
		 << "Adresse: " << adresse << endl;
}

void Spiller::skrivTilFil(ofstream& ut) {
	ut << navn << endl;	// Skriver ut navn
	ut << adresse << endl;	// Skriver ut adresse
	ut << endl;		// Går over til neste linje
}