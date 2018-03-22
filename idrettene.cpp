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
	bool erIListen;							// Midlertidig verdi for � lagre om idretten allerede eksisterer

	do {
		les("Skriv inn idrettens navn", navn, STRLEN); // Henter idrettens navn

		erIListen = idrettListe->inList(navn);

		if (erIListen)
		cout << "Idretten eksisterer allerede!\nSkriv inn Q for a avslutte loopen\n";
	} while (erIListen && !isQ(navn));
	
	// Lag peker til idrettobjekt og legg til
	if (!isQ(navn)) // kj�rer koden hvis navn ikke er lik 'Q'(eller 'q')
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

	// Finn filnavn eller skriv inn Q

	cout << "Skriv inn Q for � avbryte\n";

	do {
		les("Skriv inn navn p� fil(inkludert ending)", navn, STRLEN);
		
		// Sjekker om filen eksisterer
	} while (!ifstream(navn) && !isQ(navn));


	// Hvis koden ikke skal avbrytes
	if (!isQ(navn))
	{
		ifstream nyDiv(navn); // lager ny ifstream for filen

		// Loop kj�rer til q er skrevet, eller ett nytt avdelingsnavn er skrevet
		do {
			les("Skriv inn navnet p� div/avd", navn, STRLEN);
		} while (!temp->leggTilDiv(nyDiv, navn) && !isQ(navn));

		nyDiv.close(); // Lukker filen
	}


	idrettListe->add(temp); // kj�rer koden hvis brukeren ikke skrev inn Q
}

void Idrettene::fjernIdrett(char* navn)
{
	
	if (idrettListe->inList(navn))
	{
		for (int i = 1; i <= idrettListe->noOfElements(); i++)
		{
			//temp som sjekker om de matcher
			Idrett* temp = (Idrett*)idrettListe->removeNo(i);

			if (!strcmp(temp->hentNavn(), navn))				//er de like?
			{
				//dobbeltsjekker at man vil slette
				cout << "Er du sikker pa at du vil slette? Y/N";
				if (les(false) != 'Y')
				{
					cout << "Sletter ikke.\n";
					idrettListe->add(temp);
				}
				else cout << "Sletter...\n";
			}
			else
			{
				idrettListe->add(temp);			//legges tilbake i lista
			}
		}
	}
	else cout << "Denne idretten finnes ikke.\n";
}

void Idrettene::fjernDiv(char* navn)
{
	if (idrettListe->inList(navn))
	{
		bool fant = false;
		for (int i = 1; i <= idrettListe->noOfElements(); i++)
		{
			//temp som sjekker om de matcher
			Idrett* temp = (Idrett*)idrettListe->removeNo(i);

			if (!strcmp(temp->hentNavn(), navn))		
			{
				fant = true;
				temp->slettDiv();
			}

			idrettListe->add(temp);
			
		}
		if (!fant) cout << "Fant ikke divisjonen.\n";
	}
	else cout << "Finner ikke idrett.\n";
}

bool Idrettene::harIdrett(char* navn)
{
	return idrettListe->inList(navn);
}

void Idrettene::laglag(char* navn)
{
	for (int i = 1; i <= idrettListe->noOfElements(); i++)
	{
		Idrett* temp = (Idrett*)idrettListe->removeNo(i); //temp

		if (!strcmp(temp->hentNavn(), navn))		//hvis match
		{
			char nvn[STRLEN];
			les("Skriv inn divisjonsnavn", nvn, STRLEN);
			temp->laglag(nvn);
		}

		idrettListe->add(temp);			//legger tilbake i lista
	}
}

//sjekker om lista ikke er tom
bool Idrettene::ikkeTom()
{
	return idrettListe->noOfElements();
}

void Idrettene::skrivUt(char* navn, bool alle)
{

	if (alle)	// Skriver ut alle idretter, nummer av divisjoner og tabelltype
	{
		if (idrettListe->noOfElements())			//sjekker at ikke tom
		{
			idrettListe->displayList();


			cout << endl;
		}
		else cout << "Det finnes ingen idretter.\n";
	}
	else		// Skriver ut idretten <navn>s nummer av divisjoner, tabelltype og divisjonsnavn i tilleg til antall lag i hver divisjon, navnene og adressene til disse lagene og antall spillere i hvert lag
	{
		removeSpaces(navn);					// Fjerner eventuelle spacer fra starten
		
				// Displayer elementet om det eksisterer og skriver ut en beskje om det ikke eksisterer
		if (idrettListe->displayElement(navn))
		{
			// Henter idrett <navn>
			Idrett* temp = (Idrett*)idrettListe->remove(navn); 

			// Skriver ut I <navn> spesifik info
			temp->displayResten();

			// Legger adressen tilbake i listen
			idrettListe->add(temp);
		}
		else	// Skriver ut reseten av den n�dvendige infoen
			cout << "idretten " << navn << " ble ikke funnet!\n";
	}
}

// Leser fra fil
void Idrettene::lesFraFil() {
	ifstream inn("IDRETTENE.DTA");

	Idrett* tempIdrett = nullptr;
	char tempNavn[STRLEN];
	int numSport = 0;

	inn >> numSport;
	inn.ignore();

	// cout << numSport << endl; // DEBUG

	// Hver loop henter en idrett
	for (int i = 0; i < numSport; i++) // leser fra fil s� lenge den ikke slutter
	{
		//cout << i << endl; // DEBUG
		// cout << tempNavn << endl; // DEBUG
		// Henter sports navn
		inn.getline(tempNavn, STRLEN); // Henter sportsnavnet

		tempIdrett = new Idrett(tempNavn, inn);
		idrettListe->add(tempIdrett);				// Legger til idretten
	}

	inn.close();
}

// Skriver til fil i slutten av programmet
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