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
	inn >> Hjemmemaal;
	inn >> bortemaal;
	inn >> normalTid;
	inn.ignore();

	int tempInt;
	
	for (int i = 0; i < Hjemmemaal; i++)
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