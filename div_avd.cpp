#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <fstream>
#include <iostream> // DEBUG
#include <iomanip>
#include "div_avd.h"
#include "globale_funksjoner.h"
#include "enumer.h"

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

			if (strcmp(tempVerdi, "0")) // Hvis dette opsettet eksisterer
			{
				// cout << i << ", " << n << " - 1" << endl; // DEBUG
				resultater[i][n] = new Resultat(inn, tempVerdi);
			}
			else
			{
				// cout << i << ", " << n << " - 0" << endl; // DEBUG
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

void DivAvd::sjekkDato(char* tall, int x, int y)
{

	if (resultater[x][y]->returnDato())
	{
		if (!strcmp(resultater[x][y]->returnDato(), tall))
		{
			resultater[x][y]->display();
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
			resultater[x][y]->skrivTilFil(ut);
		}
	}
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
				if (resultater[hjemme][borte] != nullptr)
					resultater[hjemme][borte]->lesResultat(inn); // leser inn resultatene
				else resultater[borte][hjemme]->lesResultat(inn);
				// cout << "DEBUG: Suksess!\n"; // DEBUG
			}
			else 
			{
				// Sjekker om det fins bare en kamp mellom de to lagene på den rette datoen
				if ((resultater[hjemme][borte]  != nullptr && !strcmp(resultater[hjemme][borte]->returnDato(), tempDato) ||
					resultater[borte][hjemme] != nullptr && !strcmp(resultater[borte][hjemme]->returnDato(), tempDato)))  // resultater[borte][hjemme] eksisterer
				{
					// DEBUG
					// cout << (resultater[hjemme][borte] == nullptr) << ", " << (resultater[borte][hjemme] == nullptr) << endl;

					// Sjekker om det allerede fins en kamp mellom de to lagene, som ville være en logisk feil
					// Denne logiske filen kommer hvis mer enn ett resultat mellom dem eksisterer
					// Feilen kommer også hvis det bare er et resultat, men det ikke er et tomt resultat
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

						// cout << "DEBUG(1): " << t << endl; // DEBUG
						inn.getline(t, STRLEN);
						// cout << "DEBUG(2): " << t << endl; // DEBUG
						inn.getline(t, STRLEN);
						// cout << "DEBUG(3): " << t << endl; // DEBUG
					}
					else {
						// DEBUG
						/*
						cout << "DEBUG:\n";
						if ((
							resultater[hjemme][borte] != nullptr &&
							resultater[borte][hjemme] == nullptr))
						{
							if
								(resultater[hjemme][borte]->erTom()) cout << "!1\n";
							else cout << "1 er ikke tom!\n";
						}
						else cout << "1 har ikke en nullptr og en ikke nullptr!\n";

						if ((
							resultater[borte][hjemme] != nullptr &&
							resultater[hjemme][borte] == nullptr))
						{
							if (resultater[borte][hjemme]->erTom()) cout << "!2\n";
							else cout << "2\n";
						}
						else cout << "2 har ikke en nullptr og en ikke nullptr!\n";
						*/

						cout << "Det er allerede en kamp mellom " << lagHjemme << " og " << lagBorte << " registrert!" << endl;
						return false;
					}
				}
				else
				{
					cout << "Det var ingen kamp mellom " << lagHjemme << " og " << lagBorte << " på datoen " << tempDato << "!" << endl;

					return false;
				}
			}
		}
	}

	return true;
}

// Skriver ut tabell av divisjon enten til fil eller skjerm
void DivAvd::skrivTabell(TabellType type, bool skrivTilFil, char* filnavn) {
	if (skrivTilFil)	// Skriv til fil
	{
		ofstream ut(filnavn, ios::app); // Skriver til fil utne å endre allerede eksisterende innhold

		// Skriv ut hele divisjonens tabell til fil

		const char filler = ' ';
		char temp[STRLEN + 4] = "", temp2[3];

		// Skriver ut divisjonsnavn
		ut << text << endl;
		ut << left << setw(LEN_RESULTS) << setfill(filler) << "Lag";

		// Resten av første rad
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


			// Første kolonne
			ut << setw(LEN_RESULTS) << setfill(filler) << temp;

			// Resultater for alle kamper, alle andre kolonner
			for (int n = 0; n < antLag; n++)
			{
				// Skriver ut poengene lag i - 1 fikk når de gikk opp mot lag n - 1(- 1 på grunn av at de har nummer 0-29 i strukturen)
				// Ettersom bare en kamp kan eksistere mellom to lag i en avdeling er denne sjekken her for å sjekke den ene kampen som er der
				if (resultater[n][i] != nullptr)
					ut << setw(LEN_ROW_RESULTS) << setfill(filler) << resultater[n][i]->poengResultat(type, true);
				else if (resultater[i][n] != nullptr)
					ut << setw(LEN_ROW_RESULTS) << setfill(filler) << resultater[i][n]->poengResultat(type, false);
				else
					ut << setw(LEN_ROW_RESULTS) << "X";
			}
			ut << endl;
		}
		ut.close();
	}
	else {
		const char filler = ' ';
		char temp[STRLEN + 4] = "", temp2[3];

		// Skriver ut divisjonsnavn
		cout << text << endl;
		cout << left << setw(LEN_RESULTS) << setfill(filler) << "Lag";

		// Resten av første rad
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

			
			// Første kolonne
			cout << setw(LEN_RESULTS) << setfill(filler) << temp;

			// Resultater for alle kamper, alle andre kolonner
			for (int n = 0; n < antLag; n++)
			{
				// Skriver cout poengene lag i - 1 fikk når de gikk opp mot lag n - 1(- 1 på grunn av at de har nummer 0-29 i strukturen)
				// Ettersom bare en kamp kan eksistere mellom to lag i en avdeling er denne sjekken her for å sjekke den ene kampen som er der
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
			// Sjekker at lagene ikke er det samme og at det er et resultat å skrive ut
			if (i != n && resultater[i][n] != nullptr) // To lag skal mot hverandre
			{
				resultater[i][n]->skrivTilFil(ut);
			}
			else ut << 0 << endl; // Hvis lagene som skal mot hverandre er det samme
		}

		ut << endl;
	}
}