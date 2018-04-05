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

	lesResultat(inn, true); // Leser inn resten, koden er brukt av en annen funksjon og er derfor splittett inn i denne funksjonen
}

// Destruktor
Resultat::~Resultat() {
	// Fjerner alle hjemmeSkorer verdier
	for (int i = 0; i < hjemmemaal; i++)
		delete hjemmeSkorer[i];
	// Fjerner alle borteSkorer verdier
	for (int i = 0; i < bortemaal; i++)
		delete borteSkorer[i];
	
}

// Returnerer dato
char* Resultat::returnDato() {
	return dato;
}

// leser inn resultatene til spesifik dato
void Resultat::lesResultat(std::ifstream& inn, bool first) {
	inn >> hjemmemaal;
	inn >> bortemaal;
	inn >> normalTid;
	inn.ignore();

	int tempInt;

	for (int i = 0; i < hjemmemaal; i++)
	{
		inn >> tempInt;

		if (first) hjemmeSkorer[i] = new int; // Hvis den ikke har blitt generert før
		*hjemmeSkorer[i] = tempInt;

		cout << "DEBUG: " << *hjemmeSkorer[i] << endl; // DEBUG
	}

	inn.ignore();

	for (int i = 0; i < bortemaal; i++)
	{
		inn >> tempInt;

		if (first) borteSkorer[i] = new int; // Hvis den ikke har blitt generert før
		*borteSkorer[i] = tempInt;

		cout << "DEBUG: " << *borteSkorer[i] << endl; // DEBUG
	}

	inn.ignore();
}

void Resultat::skrivTilFil(ofstream& ut) {
	// Skriver dato, antall hjemme og bortemål og om kampen brukte overtid eller ikke
	ut << dato << " " << hjemmemaal << " " << bortemaal << " " << normalTid << endl;

	for (int i = 0; i < hjemmemaal; i++) {
		if (hjemmeSkorer[i] != nullptr)
			ut << *hjemmeSkorer[i] << " ";
		else break;
	}

	ut << endl;

	for (int i = 0; i < bortemaal; i++) {
		if (borteSkorer[i] != nullptr)
			ut << *borteSkorer[i] << " ";
		else break;
	}

	ut << endl;
}