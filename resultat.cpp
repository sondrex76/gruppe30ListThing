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

	// Leser første linje
	inn >> hjemmemaal;
	inn >> bortemaal;
	inn >> normalTid;
	inn.ignore();

	int tempInt;
	
	for (int i = 0; i < hjemmemaal; i++)
	{
		inn >> tempInt;

		hjemmeSkorer[i] = new int;
		*hjemmeSkorer[i] = tempInt;
	}

	inn.ignore();

	for (int i = 0; i < bortemaal; i++)
	{
		inn >> tempInt;

		borteSkorer[i] = new int;
		*borteSkorer[i] = tempInt;
	}

	inn.ignore();

	// cout << "Hjemme: " << Hjemmemaal << "\nBorte: " << bortemaal << "\nNormal: " << normalTid << endl; // DEBUG
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