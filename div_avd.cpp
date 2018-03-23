#include <fstream>
#include <iostream> // DEBUG
#include "div_avd.h"
#include "globale_funksjoner.h"

using namespace std;

// Konstruktor når man leser fra fil
DivAvd::DivAvd(char* avdelingsNavn, ifstream& inn, bool start) : TextElement(avdelingsNavn) {
	inn >> antLag; // Henter antall lag
	inn.ignore();
	inn.ignore();

	if (start) // starten av programmet
	{

		// cout << antLag << endl; // DEBUG

		// Leser inn alle lag
		for (int i = 0; i < antLag; i++)
		{
			lag[i] = new Lag(inn, start);
			inn.ignore();

			// cout << lag[i] << endl; // DEBUG
		}
	}
	else { // leser inn fra en ny_div fil
		// cout << antLag << endl; // DEBUG

		// Leser inn alle lag
		for (int i = 0; i < antLag; i++)
		{
			lag[i] = new Lag(inn, start);
			inn.ignore();
		}
	}

	char tempVerdi[9]; // lagrer dato

	// Leser inn alle resultater
	for (int i = 0; i < antLag; i++)
	{
		for (int n = 0; n < antLag; n++)
		{
			inn >> tempVerdi; // Henter den første verdien
							  //cout << tempVerdi << endl; // DEBUG

			if (strcmp(tempVerdi, "0") != 0) // Hvis dette opsettet eksisterer
			{
				resultater[i][n] = new Resultat(inn, tempVerdi);
			}
			else
			{
				resultater[i][n] = nullptr;
				inn.ignore();
			}
		}
	}
}

// Destruktor
DivAvd::~DivAvd() {
	for (int i = 0; i < antLag; i++)
	{
		// Sletter lag i
		if (lag[i] != nullptr) delete lag[i];

		// Sletter alle resultater i
		for (int n = 0; n < antLag; n++)
		{
			if (resultater[i][n] != nullptr) delete resultater[i][n];
		}
	}
}

char* DivAvd::hentNavn()
{
	return text;			//returnerer navn
}

void DivAvd::redigerSpiller()
{
	char navn[STRLEN];
	les("Skriv inn lagets navn", navn, STRLEN);
	for (int i = 0; i < antLag; i++)
	{
		if (!strcmp(lag[i]->sendNavn(), navn))
		{
			char valg;
			do
			{
				cout << "Vil du (F)jerne eller (L)egge til spiller?";
				valg = les(false);
				valg = toupper(valg);
			} while (valg != 'F' && valg != 'L');

			if (valg == 'F')
			{
				lag[i]->fjernSpiller();
			}
			else 
			{
				lag[i]->leggTilSpiller();
			}
		}
	}
}

// Skriver ut data fra I <navn>
void DivAvd::display()
{
	cout << text << endl;
	cout << "Nummer av lag: " << antLag << endl;

	// Skriver ut alle lags navn, adresse og antall spillere
	for (int i = 0; i < antLag; i++)
	{
		lag[i]->display();
		cout << endl;
	}
}

void DivAvd::skrivTilFil(ofstream& ut) {
	ut << text << endl; // skriver inn divisjonsnavn
	ut << antLag << endl << endl;

	for (int i = 0; i < antLag; i++)
	{
		lag[i]->skrivTilFil(ut);
	}

	// resultater
	for (int i = 0; i < antLag; i++)
	{
		for (int n = 0; n < antLag; n++)
		{
			if (i != n) // To lag skal mot hverandre
			{
				resultater[i][n]->skrivTilFil(ut);
			}
			else ut << 0 << endl; // Hvis lagene som skal mot hverandre er det samme
		}

		ut << endl;
	}
}