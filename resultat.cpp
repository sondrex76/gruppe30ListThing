#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream>
#include <iostream>
#include "resultat.h"
#include "conster.h"
#include "globale_funksjoner.h"

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
	cout << "\tDato: " << dato << "\tResultat: " << hjemmemaal
		 << " - " << bortemaal << endl;
}

void Resultat::displayTabell()
{
	char d[6];
	strcpy(d, datoFormat(dato));

	cout << "\t" << d << "\t\t" << hjemmemaal << "\t" << bortemaal << "\t";
	if (normalTid)
	{
		cout << "  Nei";
	}
	else
	{
		cout << "   ja";
	}
}


void Resultat::skrivTabell(ofstream& ut)
{
	ut << "\t" << dato << "\t" << hjemmemaal << "\t\t" << bortemaal << "\t\t";
	if (!normalTid)
	{
		ut << "  X";
	}
}
// leser inn resultatene til spesifik dato
void Resultat::lesResultat(std::ifstream& inn) {
	inn >> hjemmemaal;
	inn >> bortemaal;
	inn >> normalTid;

	// cout << "hjemme: " << hjemmemaal << "\nborte: " << bortemaal << "\nTid: " << normalTid << endl; // DEBUG

	if (hjemmemaal) inn.ignore();

	int tempInt;

	for (int i = 0; i < hjemmemaal; i++)
	{
		inn >> tempInt;

		hjemmeSkorer[i] = tempInt;
	}

	if (bortemaal) inn.ignore();

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

	if (hjemmemaal >= 0) ut << endl;

	for (int i = 0; i < bortemaal; i++) {
		ut << borteSkorer[i] << " ";
	}

	if (bortemaal >= 0) ut << endl;
}

// Gir resultat til lag1 i kamp mellom lag1 og lag2 
int Resultat::poengResultat(TabellType type, bool hjemme) {
	int lag1, lag2;

	if (hjemme)
	{
		lag1 = hjemmemaal;
		lag2 = bortemaal;
	}
	else
	{
		lag1 = bortemaal;
		lag2 = hjemmemaal;
	}
	// ToEnNull		= 2 poeng for seier, 1 for uavgjort og 0 for tap
	// TreEnNull	= 3 poeng for seier, 1 for uavgjort og 0 for tap
	// TreToEnNull	= 3 poeng for seier, 2 poeng for seier på overtid / straffer, 1 for uavgjort ved fulltid og 0 for tap

	if (type == ToEnNull)
	{
		if (lag1 > lag2) // vinn
			return 2;
		else if (lag1 == lag2)
			return 1;
		else
			return 0;
	}
	else if (type == TreEnNull)
	{
		if (lag1 > lag2) // vinn
			return 3;
		else if (lag1 == lag2)
			return 1;
		else
			return 0;
	}
	else // TreToEnNull
	{
		if (lag1 > lag2) // vinn
			if (normalTid) 
				return 3;
			else 
				return 2;
		else if (lag1 == lag2 && normalTid)
			return 1;
		else
			return 0;
	}
}

// Sjekker om resultatet er tomt
bool Resultat::erTom() {
	return (hjemmemaal == -1 && bortemaal == -1);
}