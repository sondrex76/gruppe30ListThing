#include <fstream>
#include <iostream>
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
					
	char navn[STRLEN];								//navnetemp

	les("Skriv inn idrettens navn", navn, STRLEN);

	if (!idrettListe->inList(navn))					//hvis nytt navn
	{
								//lag peker til idrettobjekt og legg til
		cout << "Lager ny idrett.\n";
		Idrett* temp = new Idrett(navn);
		idrettListe->add(temp);

		idrettListe->displayList();			//for å sjekke at det virker
	}
	else
	{
		cout << "Denne idretten finnes allerede.\n";
	}
	
}

						//returner nummeret til idretten i lista. evt 0
int Idrettene::faaNr(char* nvn)
{
	int nr = 0;
	if (idrettListe->inList(nvn))
	{
		for (int i = 1; i <= idrettListe->noOfElements(); i++)
		{

			Idrett* temp = (Idrett*)idrettListe->removeNo(i);

			if (temp->likSom(nvn))
			{
				nr = i;
			}
			idrettListe->add(temp);
		}
	}
	return nr;
}

void Idrettene::leggTilDiv(int nr)
{
	Idrett* temp = (Idrett*)idrettListe->removeNo(nr);	//lager temp

	char navn[STRLEN];
	les("Skriv inn navnet på div/avd", navn, STRLEN);
	
		temp->leggTilDiv(navn);
	
	idrettListe->add(temp);
}

void Idrettene::lesFraFil() {
	ifstream inn("IDRETTENE.DTA");

	Idrett* tempIdrett = nullptr;
	char tempNavn[STRLEN];
	int numSport = 0;

	inn >> numSport;
	inn.ignore();

	//cout << numSport << endl; // DEBUG

	// Hver loop henter en idrett
	for (int i = 0; i < numSport; i++) // leser fra fil så lenge den ikke slutter
	{
		//cout << i << endl; // DEBUG
		//cout << tempNavn << endl; // DEBUG

		inn.getline(tempNavn, STRLEN);

		tempIdrett = new Idrett(tempNavn, inn);
		idrettListe->add(tempIdrett);				// Legger til idretten
	}
}

void Idrettene::skrivTilFil() {

}