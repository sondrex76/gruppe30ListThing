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


	// cout << antLag << endl; // DEBUG

	// Leser inn alle lag
	for (int i = 0; i < antLag; i++)
	{
		lag[i] = new Lag(inn, start);
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
	int antallDatoer, antallKamper, hjemme, borte;
	char tempDato[9];
	bool lagHjemmeFins, lagBorteFins;


	inn >> antallDatoer; // Henter antall datoer
	inn.ignore();

	// Hver loop sjekker en dato
	for (int i = 0; i < antallDatoer; i++)
	{
		inn >> tempDato; // Henter en dato
		inn.ignore();

		inn >> antallKamper; // Henter antall kamper
		inn.ignore();

		// cout << "DEBUG: " << antallDatoer << ", " << tempDato << ", " << antallKamper << endl;

		inn.ignore();

		// Går gjennom alle kamper og sjekker om lagene eksisterer
		for (int i = 0; i < antallKamper; i++)
		{
			char lagHjemme[STRLEN], lagBorte[STRLEN];

			lagHjemmeFins = lagBorteFins = false; // resetter begge verdier

			inn.getline(lagHjemme, STRLEN);
			inn.getline(lagBorte, STRLEN);

			// cout << "DEBUG: " << lagHjemme << ", " << lagBorte << endl;


			// Sjekker om lagene finnes
			for (int i = 0; i < antLag; i++)
			{

				if (!strcmp(lagHjemme, lag[i]->sendNavn())) // sjekker om de to char arrayene er like
				{
					lagHjemmeFins = true;
					hjemme = i;
				}

				if (!strcmp(lagBorte, lag[i]->sendNavn())) // sjekker om de to char arrayene er like
				{
					lagBorteFins = true;
					borte = i;
				}

				// cout << "DEBUG: Et lag som er funnet - " << lag[i]->sendNavn() << endl;

				// cout << "DEBUG: " << lagHjemme << ", " << lagBorte << endl; // DEBUG

				// Går ut av ytterste for loop hvis begge har blitt funnet
			}

			// Sjekker om hjemmelaget ikke eksisterer
			if (!lagHjemmeFins)
			{
				cout << "Laget(hjemme) " << lagHjemme << " eksisterer ikke!\n";
				return false;
			}

			// Sjekker om bortelaget ikke eksisterer
			if (!lagBorteFins)
			{
				cout << "Laget(borte) " << lagBorte << " eksisterer ikke!\n";
				return false;
			}

			// Sjekk om datoen for kampen mellom dem er riktig eller skriver dataen inn
			if (oppdater) // Oppdaterer data på kampen på datoen epesifisert mellom lagene
			{
				resultater[hjemme][borte]->lesResultat(inn, false); // leser inn resultatene
				cout << "DEBUG: Suksess!\n"; // DEBUG
			}
			else {
				// Sjekker om det fins en kamp mellom de to lagene på den datoen
				if (!strcmp(resultater[hjemme][borte]->returnDato(), tempDato)) // Sjekker om kampen mellom de to lagene er like
				{
					char t[STRLEN]; // Lagrer verdiene slik at de kan bli forkastet, inn.ignore() ignorerte bare fram itl neste element

					inn.getline(t, STRLEN);
					// cout << "DEBUG(1): " << t << endl; // DEBUG
					inn.getline(t, STRLEN);
					// cout << "DEBUG(2): " << t << endl; // DEBUG
					inn.getline(t, STRLEN);
					// cout << "DEBUG(3): " << t << endl; // DEBUG
				}
				else
				{
					cout << "Det var ingen kamp mellom hjemmelaget " << lagHjemme << " og bortelaget " << lagBorte << " på datoen " << tempDato << "!" << endl;

					return false;
				}
			}
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