#include <fstream>
#include <iostream> // DEBUG
#include "spillere.h"
#include "spiller.h"
#include "ListTool2B.h"

using namespace std;

// Konstruktor for Spillere
Spillere::Spillere() {
	spillerListe = new List(Sorted); // setter spiller listen som sorted
}

void Spillere::lagSpiller()
{
	Spiller* temp = new Spiller(sisteNummer++);
	spillerListe->add(temp);
}


// Leser alle spillere fra fil(Navn og adresse)
void Spillere::lesFraFil() {
	ifstream inn("SPILLERE.DTA");
	
	inn >> sisteNummer; // setter sisteNummer
	inn.ignore();		// Ignorerer to linjer
	inn.ignore();

	Spiller* tempSpiller = nullptr;

	// leser inn en spiller for hvert nummer mellom(og inkludert) en og sisteNummer
	for (int i = 1; i <= sisteNummer; i++)
	{
		tempSpiller = new Spiller(i, inn);

		inn.ignore();	// Ignorerer en linje i filen

		spillerListe->add(tempSpiller); // Legger til ny spiller til spillere
	}

	inn.close();
}

void Spillere::skrivTilFil() {

}