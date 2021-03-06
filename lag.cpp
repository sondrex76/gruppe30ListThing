#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream>
#include <iostream>
#include "lag.h"
#include "conster.h"
#include "spillere.h"
#include "globale_funksjoner.h"

using namespace std;

// Spillere slik at n�r man leser avdeling fra fil kan man legge til spillere
extern Spillere spillere;

// Standard konstruktor
Lag::Lag() {
	cout << "Lager lag!!\n";
	for (int i = 0; i < MAXSPILLERE; i++)
	{
		spillerID[i] = 0;
	}
}

// Konstruktor for � lese fra fil
Lag::Lag(ifstream& inn, bool start) {	// Start ser om det er p� starten av programmet eller om det leses inn en ny divisjon
	char tempChar[MAXSPILLERE * 3];

	inn.getline(tempChar, STRLEN);			// Henter navn av lag
	navn = new char[strlen(tempChar) + 1];
	strcpy(navn, tempChar);					// Oppdaterer navn

	inn.getline(tempChar, STRLEN);			// Henter lagets adresse
	adresse = new char[strlen(tempChar) + 1];
	strcpy(adresse, tempChar);				// Oppdaterer navn

	inn >> antSpillere;						// Henter antall spillere
	inn.ignore();

	// Kj�rer p� starten, leser aldri inn navn og adresse av spillere
	if (start)
	{

		for (int i = 0; i < antSpillere; i++)
		{
			spillerID[i] = new int;
			inn >> *(spillerID[i]); // endrer verdien til spillerID[i]
		}
		inn.ignore();
	}
	else {	// Leser ny divisjon
		for (int i = 0; i < antSpillere; i++)
		{
			spillerID[i] = new int;
			inn >> *(spillerID[i]); // endrer verdien til spillerID[i]

			inn.ignore();

			// Kode som sjekker om spillerID[i] allerede eksisterer
			// om spillerID[i] allerede eksisterer, gj�r ingenting.
			// om spillerID[i] ikke allerede eksisterer, legg til spilleren med b�de navn og adresse
			if (!spillere.eksisterer(*(spillerID[i])))
			{
				spillere.lesSpillerFraFil(*(spillerID[i]), inn);
			}
		}
	}
}

// Destruktor
Lag::~Lag() {
	delete navn;	// Sletter navn
	delete adresse;	// Sletter adresse
	
	// Sletter spiller idene av lag medlemmene
	for (int i = 0; i < antSpillere; i++)
	{
		delete spillerID[i];
	}
}

// Skriver ut navn, adresse og antall spillere
void Lag::display() {
	cout << "Navn: " << navn << endl;
	cout << "Adresse: " << adresse << endl;
	cout << "Antall spillere: " << antSpillere << endl;
}

// Skriver lagets data til fil
void Lag::skrivTilFil(ofstream& ut) {
	ut << navn << endl;		// Navn
	ut << adresse << endl;		// Adresse
	ut << antSpillere << endl;	// Antall spillere

	for (int i = 0; i < antSpillere; i++)
	{
		ut << *spillerID[i]; // Skriver ut unik ID til alle spillere
		if (i != antSpillere - 1) ut << " ";	// Legger til et space hvis det ikke er den siste verdien
	}

	ut << endl << endl;					// Linjeskift
}

char* Lag::sendNavn()
{
	return navn;
}

void Lag::skrivLag()
{
	char temp[STRLEN]; // verdi som lagrer char versjon av int

	for (int i = 0; i < antSpillere; i++)
	{
		_itoa(*spillerID[i], temp, 10);
		spillere.skrivSpiller(temp, false); // Skriver ut spiller med verdi temp
	}
}

			//fjerner spiller.. ;)
void Lag::fjernSpiller()
{
	char input;				//valg, fortsett/stopp
	int nr;
	bool fant = false;			//brukes for � se om spiller finnes alt
	//en do/while som kj�rer s� lenge brukeren vil fjerne flere.

						//leser inn spillerID
	cout << "Skriv inn 0 for a avbryte loopen\n";

	do {
		nr = les("Skriv inn nummer pa spiller", 0, MAXSPILLERE);


		for (int i = 0; i < antSpillere; i++)			//for alle spillere
		{
			if (*spillerID[i] == nr)			//sjekk nr, hvis lik
			{
				fant = true;							//fant den!
				delete spillerID[i]; //spiller nr0 finnes ikke,s� bruker det
				antSpillere--;			//spiller fjernes, ergo 1 mindre

				for (int n = i; n < antSpillere; n++) // Oppdaterer verdier i listen til � v�re i rekkef�lge
				{
					spillerID[n] = spillerID[n + 1];
				}
				i--; // Oppdaterer i
			}
		}
		if (!fant) cout << "Fant ikke spilleren pa dette laget.\n";
	} while (!fant && nr != 0);
}

// Fjerner spiller nr fra laget
void Lag::fjernSpiller(int nr) {
	bool spillerFunnet = false;

	for (int i = 0; i < antSpillere; i++)
	{
		if (spillerFunnet)
		{
			// Oppdaterer arrayen ettersom det er ett mindre element enn f�r
			spillerID[i] = spillerID[i + 1];

			if (*spillerID[i] > nr)	// Hvis nr er st�rre enn nr
				(*spillerID[i])--;
		}
		else {
			if (*spillerID[i] == nr)		// Hvis spillerID er nr
			{
				spillerFunnet = true;
				delete spillerID[i];	// fjerner spillerID[i]
				spillerID[i] = nullptr;

				antSpillere--;			// oppdaterer antall spillere nummeret
				i--;					// Oppdaterer i
			}
			else if (*spillerID[i] > nr)	// Hvis nr er st�rre enn nr
				(*spillerID[i])--;
		}
	}
}

		//legger til spiller
void Lag::leggTilSpiller()
{
	bool finnesAlt;
	int nr;

	//en do/while loop s� lenge brukeren �nsker � fortsette
	cout << "Skriv inn 0 for a avbryte loopen\n";
	do
	{
		finnesAlt = false;
		nr = les("Skriv inn nummer pa spiller", 0, MAXSPILLERE);

		if (spillere.eksisterer(nr)) // Sjekker om spilleren eksisterer
		{
			for (int i = 0; i < antSpillere; i++)		//for alle spillere
			{
				if (*spillerID[i] == nr)			//hvis lik, fant!
				{
					finnesAlt = true;
				}
			}

			if (!finnesAlt)							// Sjekker om spilleren allerede er del av laget
			{
				spillerID[antSpillere] = new int;
				*spillerID[antSpillere++] = nr;		//og ant blir �kt med 1
			}
			else cout << "Denne spilleren finnes allerede pa laget.\n";
		}
		else if (nr != 0)
			cout << "Spiller nr " << nr << " eksisterer ikke!\n";
		else break; // G�r ut av loopen om man skriver inn 0
	} while (finnesAlt);

	cout << "TEST!\n";
}