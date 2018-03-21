#include <fstream>
#include <iostream> // DEBUG
#include "div_avd.h"

using namespace std;

// Standard konstruktor
DivAvd::DivAvd(char* avdelingsNavn) : TextElement(avdelingsNavn) {
	antLag = 0;						//så vi kan bruke ++ senere
}

// Konstruktor når man leser fra fil
DivAvd::DivAvd(char* avdelingsNavn, ifstream& inn) : TextElement(avdelingsNavn) {
	inn >> antLag; // Henter antall lag
	inn.ignore();
	inn.ignore();

	// cout << antLag << endl; // DEBUG

	// Leser inn alle lag
	for (int i = 0; i < antLag; i++)
	{
		lag[i] = new Lag(inn);
		inn.ignore();

		// cout << lag[i] << endl; // DEBUG
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

char* DivAvd::hentNavn()
{
	return text;			//returnerer navn
}

void DivAvd::lagLag()
{
	lag[antLag++] = new Lag;
}

void DivAvd::display()
{
	cout << text << std::endl;
}

void DivAvd::lesFraFil() {

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