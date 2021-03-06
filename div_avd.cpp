#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream>
#include <iostream>
#include <iomanip>
#include "div_avd.h"
#include "globale_funksjoner.h"
#include "enumer.h"

using namespace std;

// Konstruktor n�r man leser fra fil
DivAvd::DivAvd(char* avdelingsNavn, ifstream& inn, bool start) : TextElement(avdelingsNavn) {
	inn >> antLag; // Henter antall lag
	inn.ignore();
	inn.ignore();

	// Leser inn alle lag
	for (int i = 0; i < antLag; i++)
	{
		lag[i] = new Lag(inn, start);
		inn.ignore();
	}

	char tempVerdi[9]; // lagrer dato

	// Leser inn alle resultater
	for (int i = 0; i < antLag; i++)
	{
		for (int n = 0; n < antLag; n++)
		{
			inn >> tempVerdi; // Henter den f�rste verdien

			if (strcmp(tempVerdi, "0")) // Hvis dette opsettet eksisterer
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

// Returnerer navnet p� divisjonen
char* DivAvd::hentNavn()
{
	return text;			//returnerer navn
}

// Skriver ut termninlisten
void DivAvd::skrivTerminListe()
{
	char filnavn[STRLEN];
	cout << "\tSkriv inn filnavn(klikk enter for aa skrive til skjerm): ";
	cin.getline(filnavn, STRLEN);	// Bruker ikke les funksjonen,
									//fordi den ikke aksepterer "enter"
	if (strlen(filnavn) == 0)		// Sjekker om brukeren svarte med "enter"
	{
		cout << "\n\n\tTerminliste:\n";
		cout << "\tDato\t\tH-maal\tB-maal\tOvertid\tH-lag\t\tB-lag\n";
		for (int i = 0; i < antLag; i++)
		{
			for (int n = 0; n < antLag; n++)
			{
				if (i != n && resultater[i][n] != nullptr) // To lag skal mot hverandre
				{

					resultater[i][n]->displayTabell();
					cout << "\t" << lag[i]->sendNavn();
					if (strlen(lag[i]->sendNavn()) < 8)
					{
						cout << "\t";
					}
					cout << "\t" << lag[n]->sendNavn() << "\n";
				}
			}
		}
		cout << endl;
	}
	else
	{
		strcat_s(filnavn, ".DTA");
		cout << "Skriver til fil(" << filnavn << ")\n";
		ofstream ut(filnavn);
		ut << "\n\n\tTerminliste:\n";
		ut << "\tDato\t\tH-maal\tB-maal\tOvertid\t\tH-lag\t\t\t\tB-lag\n";
		for (int i = 0; i < antLag; i++)
		{
			for (int n = 0; n < antLag; n++)
			{
				if (i != n && resultater[i][n] != nullptr)	// To lag skal mot hverandre
				{
					resultater[i][n]->skrivTabell(ut);		// Skriver ut dato,resultat, etc.
					ut << "\t\t\t" << lag[i]->sendNavn();	// Skriver ut Lag 1 (navn)
					int y = 0;
					for (int x = 5; x > 0; x--)				// Sjekker hvor mange \t trengs
															//og skriver dem ut
					{
						if (y <= strlen(lag[i]->sendNavn()) && strlen(lag[i]->sendNavn()) < y + 4)
						{
							for (int z = 0; z < x; z++)
							{
								ut << "\t";
							}
						}
						y += 4;
					}
					ut << lag[n]->sendNavn() << "\n";		// Skriver ut Lag 2
				}
			}
		}
		ut.close();
	}
}

// Skriver ut spiller ID, navn og adresse til alle spillere p� et lag
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
			}						//g�r videre
		}
		if (!funnet) cout << "Dette laget eksisterer ikke!\n";
	} while (!isQ(div)); // kj�rer til div er Q
}

void DivAvd::sjekkDato(char* tall, int x, int y)
{
	if (resultater[x][y]->returnDato())
	{
		if (!strcmp(resultater[x][y]->returnDato(), tall))
		{
			resultater[x][y]->display(lag[x]->sendNavn(), lag[y]->sendNavn());
		}
	}
}

//sammenligner dato. hvis like displayes kampen
void DivAvd::sjekkDatoFil(char* tall, int x, int y, ofstream& ut)
{
	if (resultater[x][y]->returnDato())
	{
		if (!strcmp(resultater[x][y]->returnDato(), tall))
		{
			resultater[x][y]->display(lag[x]->sendNavn(), lag[y]->sendNavn(), ut);
		}
	}
}

// Redigerer spillere p� et lag, man kan enten legge til eller fjerne en spiller
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

	// Funksjonalitet er der, men et av de mulige errorene "de to lagene har ikke spilt mot hverandre denne dagen. " gir ingen mening i konteksten av filstrukturen

	inn >> antallDatoer; // Henter antall datoer
	inn.ignore();

	// Hver loop sjekker en dato
	for (int i = 0; i < antallDatoer; i++)
	{
		inn >> tempDato; // Henter en dato
		inn.ignore();

		inn >> antallKamper; // Henter antall kamper
		inn.ignore();
		inn.ignore();

		// G�r gjennom alle kamper og sjekker om lagene eksisterer
		for (int i = 0; i < antallKamper; i++)
		{
			char lagHjemme[STRLEN], lagBorte[STRLEN];

			lagHjemmeFins = lagBorteFins = false; // resetter begge verdier

			inn.getline(lagHjemme, STRLEN);
			inn.getline(lagBorte, STRLEN);

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

				// G�r ut av ytterste for loop hvis begge har blitt funnet
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
			if (oppdater) // Oppdaterer data p� kampen p� datoen epesifisert mellom lagene
			{
				if (resultater[hjemme][borte] != nullptr)
					resultater[hjemme][borte]->lesResultat(inn); // leser inn resultatene
				else resultater[borte][hjemme]->lesResultat(inn);
			}
			else 
			{
				// Sjekker om det fins bare en kamp mellom de to lagene p� den rette datoen
				if ((resultater[hjemme][borte]  != nullptr && !strcmp(resultater[hjemme][borte]->returnDato(), tempDato) ||
					resultater[borte][hjemme] != nullptr && !strcmp(resultater[borte][hjemme]->returnDato(), tempDato)))  // resultater[borte][hjemme] eksisterer
				{
					// Sjekker om det allerede fins en kamp mellom de to lagene, som ville v�re en logisk feil
					// Denne logiske filen kommer hvis mer enn ett resultat mellom dem eksisterer
					// Feilen kommer ogs� hvis det bare er et resultat, men det ikke er et tomt resultat
					if (((resultater[hjemme][borte] != nullptr &&
						resultater[borte][hjemme] == nullptr &&
						resultater[hjemme][borte]->erTom()) || (
						resultater[borte][hjemme] != nullptr &&
						resultater[hjemme][borte] == nullptr && 
						resultater[borte][hjemme]->erTom())))
					{
						char t[STRLEN];

						// Ignorerer tre linjer, inn.ignore() ignorerer bare neste ikke-space, ikke hele linjen
						inn.getline(t, STRLEN);
						inn.getline(t, STRLEN);
						inn.getline(t, STRLEN);
					}
					else {
						cout << "Det er allerede en kamp mellom " << lagHjemme << " og " << lagBorte << " registrert!" << endl;
						return false;
					}
				}
				else
				{
					cout << "Det var ingen kamp mellom " << lagHjemme 
						 << " og " << lagBorte << " pa datoen " 
						 << tempDato << "!" << endl;
					return false;
				}
			}
		}
	}

	return true;
}

// Fjerner spiller nr fra alle lag og resultater, og oppdaterer spiller id-er
void DivAvd::fjernSpiller(int nr) {
	for (int i = 0; i < antLag; i++)
	{
		// Fjerner spilleren, opdaterer arrayen av spillere om spilleren var der og oppdaterer verdier over spillerens nr
		lag[i]->fjernSpiller(nr);

		// Resultater
		for (int n = 0; n < antLag; n++)
		{
			if (resultater[i][n] != nullptr) resultater[i][n]->fjernSpiller(nr);
		}
	}
}

// Skriver ut tabell av divisjon til skjerm
void DivAvd::skrivTabell(TabellType type, char* filnavn) {
	const char filler = ' ';
	char temp[STRLEN + 4] = "", temp2[3];

	// Skriver ut divisjonsnavn
	cout << text << endl;
	cout << left << setw(LEN_RESULTS) << setfill(filler) << "Lag";

	// Resten av f�rste rad
	for (int i = 1; i <= antLag; i++)
	{
		// Skriver cout hver kvadrant
		cout << left << setw(LEN_ROW_RESULTS) << setfill(filler) << i;
	}

	cout << endl << endl;

	for (int i = 0; i < antLag; i++)
	{
		// lager en enkelt char array fra dataen
		// "[" << (i + 1) << "] " << lag[i]->sendNavn()
		strcpy(temp, "[");

		_itoa(i + 1, temp2, 10);
		strcat(temp, temp2);

		strcat(temp, "]");
		strcat(temp, lag[i]->sendNavn());

		// F�rste kolonne
		cout << setw(LEN_RESULTS) << setfill(filler) << temp;

		// Resultater for alle kamper, alle andre kolonner
		for (int n = 0; n < antLag; n++)
		{
			// Skriver cout poengene lag i - 1 fikk n�r de gikk opp mot lag n - 1(- 1 p� grunn av at de har nummer 0-29 i strukturen)
			// Ettersom bare en kamp kan eksistere mellom to lag i en avdeling er denne sjekken her for � sjekke den ene kampen som er der
			if (resultater[n][i] != nullptr)
				cout << setw(LEN_ROW_RESULTS) << setfill(filler) << resultater[n][i]->poengResultat(type, true);
			else if (resultater[i][n] != nullptr)
				cout << setw(LEN_ROW_RESULTS) << setfill(filler) << resultater[i][n]->poengResultat(type, false);
			else
				cout << setw(LEN_ROW_RESULTS) << "X";
		}
		cout << endl;
	}
}

// Skriv ut hele divisjonens tabell til fil
void DivAvd::skrivTabellFil(TabellType type, char* filnavn, ofstream& ut) {
	const char filler = ' ';
	char temp[STRLEN + 4] = "", temp2[3];

	// Skriver ut divisjonsnavn
	ut << text << endl;
	ut << left << setw(LEN_RESULTS) << setfill(filler) << "Lag";

	// Resten av f�rste rad
	for (int i = 1; i <= antLag; i++)
	{
		// Skriver ut hver kvadrant
		ut << left << setw(LEN_ROW_RESULTS) << setfill(filler) << i;
	}

	ut << endl << endl;

	for (int i = 0; i < antLag; i++)
	{
		// lager en enkelt char array fra dataen
		// "[" << (i + 1) << "] " << lag[i]->sendNavn()
		strcpy(temp, "[");

		_itoa(i + 1, temp2, 10);
		strcat(temp, temp2);

		strcat(temp, "]");
		strcat(temp, lag[i]->sendNavn());

		// F�rste kolonne
		ut << setw(LEN_RESULTS) << setfill(filler) << temp;

		// Resultater for alle kamper, alle andre kolonner
		for (int n = 0; n < antLag; n++)
		{
			// Skriver ut poengene lag i - 1 fikk n�r de gikk opp mot lag n - 1(- 1 p� grunn av at de har nummer 0-29 i strukturen)
			// Ettersom bare en kamp kan eksistere mellom to lag i en avdeling er denne sjekken her for � sjekke den ene kampen som er der
			if (resultater[n][i] != nullptr)
				ut << setw(LEN_ROW_RESULTS) << setfill(filler) << resultater[n][i]->poengResultat(type, true);
			else if (resultater[i][n] != nullptr)
				ut << setw(LEN_ROW_RESULTS) << setfill(filler) << resultater[i][n]->poengResultat(type, false);
			else
				ut << setw(LEN_ROW_RESULTS) << "X";
		}
		ut << endl;
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
			// Sjekker at lagene ikke er det samme og at det er et resultat � skrive ut
			if (i != n && resultater[i][n] != nullptr) // To lag skal mot hverandre
			{
				resultater[i][n]->skrivTilFil(ut);
			}
			else ut << 0 << endl; // Hvis lagene som skal mot hverandre er det samme
		}
	 ut << endl;
	}
}