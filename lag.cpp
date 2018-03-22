#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream>
#include <iostream>
#include "lag.h"
#include "conster.h"
#include "spillere.h"

using namespace std;

// Spillere slik at når man leser avdeling fra fil kan man legge til spillere
extern Spillere spillere;

// Standard konstruktor
Lag::Lag() {
	cout << "Lager lag!!\n";
}

// Konstruktor for å lese fra fil
Lag::Lag(ifstream& inn, bool start) {	// Start ser om det er på starten av programmet eller om det leses inn en ny divisjon
	char tempChar[MAXSPILLERE * 3];

	inn.getline(tempChar, STRLEN);			// Henter navn av lag
	navn = new char[strlen(tempChar)];
	strcpy(navn, tempChar);					// Oppdaterer navn

	inn.getline(tempChar, STRLEN);			// Henter lagets adresse
	adresse = new char[strlen(tempChar)];
	strcpy(adresse, tempChar);				// Oppdaterer navn

	inn >> antSpillere;						// Henter antall spillere
	inn.ignore();

	// Kjører på starten, leser aldri inn navn og adresse av spillere
	if (start)
	{
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
	else {	// Leser ny divisjon
		for (int i = 0; i < antSpillere; i++)
		{
			spillerID[i] = new int;
			inn >> *(spillerID[i]); // endrer verdien til spillerID[i]

			inn.ignore();

			// Kode som sjekker om spillerID[i] allerede eksisterer
			// om spillerID[i] allerede eksisterer, gjør ingenting.
			// om spillerID[i] ikke allerede eksisterer, legg til spilleren med både navn og adresse
			if (!spillere.eksisterer(*(spillerID[i])))
			{
				spillere.lesSpillerFraFil(*(spillerID[i]), inn);
			}
		}
	}
}

// Skriver ut navn, adresse og antall spillere
void Lag::display() {
	cout << "Navn: " << navn << endl;
	cout << "Adresse: " << adresse << endl;
	cout << "Antall spillere: " << antSpillere << endl;
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