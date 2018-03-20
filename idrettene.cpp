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

// Opretter ny idrett
void Idrettene::opprett()
{
					
	char navn[STRLEN];						// Navnetemp
	bool erIListen;							// Midlertidig verdi for å lagre om idretten allerede eksisterer

	do {
		les("Skriv inn idrettens navn", navn, STRLEN); // Henter idrettens navn

		erIListen = idrettListe->inList(navn);

		if (erIListen)
		cout << "Idretten eksisterer allerede!\nSkriv inn Q for a avslutte loopen\n";
	} while (erIListen && !isQ(navn));
	
	// Lag peker til idrettobjekt og legg til
	if (!isQ(navn)) // kjører koden hvis navn ikke er lik 'Q'(eller 'q')
	{
		cout << "Lager ny idrett.\n";
		Idrett* temp = new Idrett(navn);
		idrettListe->add(temp);
	}
	// idrettListe->displayList();			// DEBUG
	
}

						//returner nummeret til idretten i lista. evt 0
int Idrettene::faaNr(char* nvn)
{
	int nr = 0;
	if (idrettListe->inList(nvn))				//hvis i lista
	{
		for (int i = 1; i <= idrettListe->noOfElements(); i++)
		{
			//temp som sjekker om de matcher
			Idrett* temp = (Idrett*)idrettListe->removeNo(i);

			if (temp->likSom(nvn))				//er de like?
			{
				nr = i;
			}
			idrettListe->add(temp);			//legges tilbake i lista
		}
	}
	return nr;		//returnerer 0 om ikke funnet. eller nummer i lista
}

void Idrettene::leggTilDiv(int nr)
{
	Idrett* temp = (Idrett*)idrettListe->removeNo(nr);	//lager temp

	char navn[STRLEN];

	do {
		les("Skriv inn navnet pa div/avd", navn, STRLEN);

		// Loop kjører til brukeren har gidd gyldig resultat eller avbrutt med å skrive "Q"
	} while (!temp->leggTilDiv(navn) && !isQ(navn));

	if (!isQ(navn)) idrettListe->add(temp); // kjører koden hvis brukeren ikke skrev inn Q
}


void Idrettene::skrivUt(char* navn, bool alle)
{
	
	if (alle)		//viser hele lista
	{
		if (idrettListe->noOfElements())			//sjekker at ikke tom
		{
			idrettListe->displayList();
			cout << endl;
		}
		else cout << "Det finnes ingen idretter.\n";
	}
	else
	{
		
		if(idrettListe->inList(navn))		//ser om navnet finnes
		{ 
			
			//om det finnes blir det displayet
			for (int i = 1; i <= idrettListe->noOfElements(); i++)
			{
				Idrett* temp = (Idrett*)idrettListe->removeNo(i); //temp
				
				if (!strcmp(temp->hentNavn(), navn))		//hvis match
				{
					
					temp->display();
				}

				idrettListe->add(temp);			//legger tilbake i lista
			}
		
		}
		else
		{
			cout << "Fant ikke idretten.\n";
		}
	}
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
		// Henter sports navn
		inn.getline(tempNavn, STRLEN);

		tempIdrett = new Idrett(tempNavn, inn);
		idrettListe->add(tempIdrett);				// Legger til idretten
	}

	inn.close();
}

void Idrettene::skrivTilFil() {
	ofstream ut("IDRETTENE.DTA");
	
	// Antall sporter
	int sporter;
	sporter = idrettListe->noOfElements();
	ut << sporter << endl; // skriver sporter til fil

	Idrett* tempIdrett = nullptr;

	for (int i = 1; i <= sporter; i++)
	{
		// Henter sport nummer i
		tempIdrett = (Idrett*)idrettListe->removeNo(i);

		ut << tempIdrett->hentNavn() << endl;
		tempIdrett->skrivTilFil(ut);

		// Legger sport nr i tilbake i listen
		idrettListe->add(tempIdrett);
	}


	ut.close();
}