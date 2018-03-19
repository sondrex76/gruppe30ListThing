#include <iostream>
#include <fstream>
#include "idrettene.h"
#include "conster.h"
#include "idrett.h"
#include "globale_funksjoner.h"

using namespace std;

// Konstruktor
Idrettene::Idrettene() {
	idrettListe = new List(Sorted);
}

void Idrettene::opprett()
{
	
	char navn[STRLEN]; 
	les("Skriv inn idrettens navn", navn, STRLEN);
	//Idrett temp;
	//idrett->add(1);

}

void Idrettene::lesFraFil() {
	ifstream inn("IDRETTENE.DTA");

	Idrett* tempIdrett = nullptr;
	char tempNavn[STRLEN];
	int numSport = 0;

	inn >> numSport;
	inn.ignore();

	// Hver loop henter en idrett
	while (!inn.eof()) // leser fra fil så lenge den ikke slutter
	{
		inn.getline(tempNavn, STRLEN);

		tempIdrett = new Idrett(tempNavn, inn);
		idrettListe->add(tempIdrett);				// Legger til idretten
	}
}

void Idrettene::skrivTilFil() {

}