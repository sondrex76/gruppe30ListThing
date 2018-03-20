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
	char nvn[STRLEN];
	les("Skriv inn spillernavn", nvn, STRLEN);
	navn = new char[strlen(nvn)+1];
	strcpy(navn, nvn);

	char adr[STRLEN];
	les("Skriv inn adresse", adr, STRLEN);
	adresse = new char[strlen(adr) + 1];
	strcpy(adresse, adr);
	display();
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

	// cout << "Navn: " << navn << "\nAdresse: " << adresse << endl; // DEBUG
}

void Spiller::display()
{
	cout << "Spillernr: " << number << endl
		 << "Navn: " << navn << endl
		 << "Adresse: " << adresse << endl;
}