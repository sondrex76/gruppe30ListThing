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
	navn = new char[strlen(nvn)+1];
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

	navn = new char[strlen(tempChar)];		// Setter navnets lengde
	strcpy(navn, tempChar);					// Definerer navn

	char temp[STRLEN];
	inn.getline(temp, STRLEN);

	adresse = new char[strlen(temp)];	// Setter adressens lengde
	strcpy(adresse, temp);				// Definerer adresse

	// cout << "Navn: " << navn << "\nAdresse: " << adresse << endl; // DEBUG
}

// DEBUG, burde bli brukt i faktisk kode senere
void Spiller::display()
{
	cout << "Spillernr: " << number << endl
		 << "Navn: " << navn << endl
		 << "Adresse: " << adresse << endl;
}

void Spiller::skrivTilFil(ofstream& ut) {
	ut << navn << endl;	// Skriver ut navn
	ut << adresse << endl;	// Skriver ut adresse
	ut << endl;		// Går over til neste linje
}