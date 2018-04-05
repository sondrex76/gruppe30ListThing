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

// Returnerer navnet på divisjonen
char* DivAvd::hentNavn()
{
	return text;			//returnerer navn
}

// Skriver ut spiller ID, navn og adresse til alle spillere på et lag
void DivAvd::skrivLag()
{
	char div[STRLEN];
	bool funnet;

	do {
		les("Skriv navnet til laget", div, STRLEN);
		funnet = false;

		for (int i = 0; i < antLag; i++)
		{
			if (!strcmp(lag[i]->sendNavn(), div))		//sjekker om navnene er like
			{
				cout << "\nLaget:\n";
				lag[i]->display();
				cout << "\nSpillere:\n";
				lag[i]->skrivLag();
				return; // Avbryter funksjonen ettersom et gyldig resultat har blitt funnet
			}						//går videre
		}
		if (!funnet) cout << "Dette laget eksisterer ikke!\n";
	} while (!isQ(div)); // kjører til div er Q
}

// Redigerer spillere på et lag, man kan enten legge til eller fjerne en spiller
void DivAvd::redigerSpiller()
{
	char navn[STRLEN];
	bool navnFunnet;
	int n; // lagrer verdien til i

	do {
		navnFunnet = false;

		les("Skriv inn lagets navn", navn, STRLEN);
		
		for (int i = 0; i < antLag; i++)
		{
			if (!strcmp(lag[i]->sendNavn(), navn))
			{
				navnFunnet = true;
				n = i;
			}
		}

		if (!navnFunnet && !isQ(navn)) cout << "Ugyldig idrettsnavn!\n";
	} while (!isQ(navn) && !navnFunnet);

	if (!isQ(navn)) // Hvis E ikke har blitt avbrutt
	{
		char valg;
		do
		{
			cout << "Vil du (F)jerne eller (L)egge til spiller?";
			valg = les(false);
		} while (valg != 'F' && valg != 'L' && valg != 'Q');

		if (valg == 'F')		// Fjerner spiller
		{
			lag[n]->fjernSpiller();
		}
		else if (valg == 'L')	// Legger til spiller
		{
			lag[n]->leggTilSpiller();
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

// Sjekker eller leser inn dataer til en divisjon
bool DivAvd::lesResultat(bool oppdater, std::ifstream& inn) {
	int antallDatoer, antallKamper;
	char tempDato[9];

	inn >> antallDatoer; // Henter antall datoer
	inn.ignore();

	// Hver loop sjekker en dato
	for (int i = 0; i < antallDatoer; i++)
	{
		inn >> tempDato; // Henter en dato
		inn.ignore();

		inn >> antallKamper; // Henter antall kamper
		inn.ignore();

		for (int i = 0; i < antallKamper; i++)
		{
			// SJekk om datoen for kampen mellom dem er riktig
		}
	}

	return true;
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