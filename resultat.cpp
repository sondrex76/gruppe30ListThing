#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream>
#include <iostream>
#include "resultat.h"
#include "conster.h"

using namespace std;

Resultat::Resultat(ifstream & inn, char d[9]) {
	// cout << d << endl; // DEBUG

	strcpy(dato, d); // kopierer d(ato) over til dato verdien

	lesResultat(inn); // Leser inn resten, koden er brukt av en annen funksjon og er derfor splittett inn i denne funksjonen
}

// Returnerer dato
char* Resultat::returnDato() {
	return dato;
}

void Resultat::display()
{
	cout << "Dato: " << dato << ". Resultat: " << hjemmemaal
		 << " - " << bortemaal << endl;
}

// leser inn resultatene til spesifik dato
void Resultat::lesResultat(std::ifstream& inn) {
	inn >> hjemmemaal;
	inn >> bortemaal;
	inn >> normalTid;
	inn.ignore();

	int tempInt;

	for (int i = 0; i < hjemmemaal; i++)
	{
		inn >> tempInt;

		hjemmeSkorer[i] = tempInt;
	}

	inn.ignore();

	for (int i = 0; i < bortemaal; i++)
	{
		inn >> tempInt;

		borteSkorer[i] = tempInt;

		// cout << "DEBUG: " << bortemaal << ": " << *borteSkorer[i] << endl; // DEBUG
	}

	inn.ignore();
}

void Resultat::skrivTilFil(ofstream& ut) {
	// Skriver dato, antall hjemme og bortemål og om kampen brukte overtid eller ikke
	ut << dato << " " << hjemmemaal << " " << bortemaal << " " << normalTid << endl;

	for (int i = 0; i < hjemmemaal; i++) {
		ut << hjemmeSkorer[i] << " ";
	}

	ut << endl;

	for (int i = 0; i < bortemaal; i++) {
		ut << borteSkorer[i] << " ";
	}

	ut << endl;
}

// Sjekker om resultatet er tomt
bool Resultat::erTom() {
	if (hjemmemaal == bortemaal == 0) return true;
	else return false;
}