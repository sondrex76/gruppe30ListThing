#include <fstream>
#include <iostream> // DEBUG(så langt)
#include "idrett.h"
#include "ListTool2B.h"
#include "conster.h"
#include "globale_funksjoner.h"
#include "div_avd.h"

// Standard konstruktor
Idrett::Idrett(char* indrettsNavn) : TextElement(indrettsNavn) {
	divAvdListe = new List(Sorted);
											//leser inn tall for enum
	int nr = les("Velg tabelltype, 1=(210), 2=(310), 3=(3210)\n", 1, 3);

	tabellType = (TabellType)nr;
}

// construktor for idrett når man leser fra fil
Idrett::Idrett(char* indrettsNavn, std::ifstream& inn) : TextElement(indrettsNavn) {
	divAvdListe = new List(Sorted);	// Setter divAvd listetype til Sorted

	char tempAvdNavn[STRLEN];
	int numRepetasjoner; // verdi som lagrer inter hentet ut av filen

	// Henter numerisk verdo for typen
	inn >> numRepetasjoner; 
	inn.ignore();

	// Setter over til typen
	tabellType = (TabellType)numRepetasjoner;

	// std::cout << "Tabell type: " << tabellType << std::endl; // DEBUG

	inn >> numRepetasjoner; // Henter nummeret av avdelinger
	inn.ignore();

	// std::cout << "Nummer av divisjoner: " << numRepetasjoner << std::endl; // DEBUG

	// Hver kjøring av loopen henter en ny avdeling
	for (int i = 1; i <= numRepetasjoner; i++)
	{
		inn.getline(tempAvdNavn, STRLEN);

		// std::cout << "Divisjonsnavn: " << tempAvdNavn << std::endl; // DEBUG

		DivAvd* tempDiv = new DivAvd(tempAvdNavn, inn, true);
		divAvdListe->add(tempDiv); // legger til avdeling
		inn.ignore(); // Ignorerer en linje
	}
}

// Sletter pekerene inni idrett(divisjonslisten)
Idrett::~Idrett() {
	delete divAvdListe; // Sletter divisjonslisten
}

char* Idrett::hentNavn() {
	return text; // returnerer navn
}
									//legger til ny divisjon om mulig
bool Idrett::leggTilDiv(std::ifstream& inn, char* navn)
{
	if (!divAvdListe->inList(navn))			// Hvis den ikke er i listen
	{
		DivAvd* temp = new DivAvd(navn, inn, false);

		// Leser lagnavn, lagadresser og lagmedlemmer til temp

		divAvdListe->add(temp);

		return true;
	}
	else
	{
		std::cout << "\tDette navnet finnes alt.\n";
		return false;
	}
}

//sletter en divisjon
void Idrett::slettDiv()
{
	// Sjekker om det finnes noen divisjoner
	if (divAvdListe->noOfElements())
	{
		char divisjon[STRLEN];
		std::cout << "\tSkriv Q for å avbryte\n";

		do {
			les("Skriv inn navn på divisjonen som skal slettes", divisjon, STRLEN);

			// Loop fortsetter til divisjonen du skrev fins, eller du avbrøt med å skrive q
		} while (!divAvdListe->inList(divisjon) && !isQ(divisjon));

		if (!isQ(divisjon)) // Hvis du ikke har avbrutt slettingen
		{
			std::cout << "Skriv J for å bekrefte at du ønsker å slette divisjonen " << divisjon << ": ";

			// Sjekker om brukeren er sikker på at de ønsker å fjerne den valgte divisjonen
			if (les(false) == 'J')
			{
				// Henter divisjonen som skal fjernes
				DivAvd* temp = (DivAvd*)divAvdListe->remove(divisjon);

				// Sletter divisjonen
				delete temp;
			}
			else std::cout << "Fjerning av divisjonen " << divisjon << " har blitt avbrutt!\n";
		}
	}
}

							//liten bool for å sjekke om navnene er like
bool Idrett::likSom(char* navn)
{
	return (!strcmp(navn, text));
}

bool Idrett::harDiv(char* navn)
{
	return divAvdListe->inList(navn);
}
			   //liten bool for å sjekke om div med visst navn finnes alt
bool Idrett::harIkkeDiv(char* navn)
{
	return (!divAvdListe->inList(navn));
}

void Idrett::skrivLag()
{
	char div[STRLEN];
	do
	{
		les("Skriv inn gyldig divisjonsnavn", div, STRLEN);
		if (!divAvdListe->inList(div)) std::cout << "Ugyldig divisjon!\n";
		// Loopen forsetter til brukeren skriver Q eller skriver en gyldig divisjon
	} while (!isQ(div) && !divAvdListe->inList(div));

	if (!isQ(div))
	{
		DivAvd* temp = (DivAvd*)divAvdListe->remove(div);

		temp->skrivLag();

		divAvdListe->add(temp);
	}
}

void Idrett::redigerSpiller()
{
	char nvn[STRLEN];

	do {
		les("Skriv inn gyldig divisjonsnavn", nvn, STRLEN);

		if (!divAvdListe->inList(nvn)) std::cout << "Ugyldig divisjon!\n";
		// Loopen forsetter til brukeren skriver Q eller skriver en gyldig divisjon
	} while (!isQ(nvn) && !divAvdListe->inList(nvn));

	if (!isQ(nvn))
	{
		DivAvd* temp = (DivAvd*)divAvdListe->remove(nvn);

		temp->redigerSpiller();

		divAvdListe->add(temp);
	}
}

void Idrett::sporDato(char* div)
{
	
	char filnavn[STRLEN];
	
	std::cout << "\tSkriv inn filnavn (inkludert ending) : ";
	std::cin.getline(filnavn, STRLEN);

	char dato[DATOLEN];
	les("Skriv inn dato (aaaammdd)", dato, DATOLEN, true);


	if (!std::ifstream(filnavn))
	{
		bool enDiv = false;		//sjekker om man vil skrive ut fra en viss div

		if (harDiv(div))
		{
			//skriver alle kampene fra en viss div fra denne idretten
			std::cout << "Skriver ut fra divisjon " << div << std::endl;
			enDiv = true;
		}
		else
		{
			//skriver alle kampene fra alle divs fra denne idretten
			std::cout << "Skriver ut fra alle divisjoner.\n";
		}
		std::cout << std::endl;

		DivAvd* temp = nullptr;				//sjekker navn og dato
		for (int i = 0; i < divAvdListe->noOfElements(); i++)
		{
			temp = (DivAvd*)divAvdListe->removeNo(i);

			if (enDiv)	//hvis 1 div, skriver bare ut når divnavn er like
			{
				if (!strcmp(temp->hentNavn(), div))
				{
					for (int i = 0; i < MAXLAG; i++)
					{
						for (int j = 0; j < MAXLAG; j++)
						{
							//alle kamper må sjekkes, så jeg bruker en
							//2-dim. array, og dersom datoen matcher
							//så skrives resultatet ut
							
							temp->sjekkDato(dato, i, j);
						}
					}
				}
			}
			//hvis ikke skrives kamper fra alle divisjoner på gitt dato
			else
			{
				for (int i = 0; i < MAXLAG; i++)
				{
					for (int j = 0; j < MAXLAG; j++)
					{
						temp->sjekkDato(dato, i, j);
					}
				}
			}
			divAvdListe->add(temp);

		}
	}
	else
	{
		//skriver til fil
	}
	std::cout << std::endl;
}

// Skriver ut objektets verdier(eksklusivt verdier som trengs i I A)
void Idrett::display()
{
	std::cout << "Navn: " << text << std::endl
		<< "Tabelltype: " << tabellType << std::endl;

	if (divAvdListe->noOfElements())
	{
		std::cout << "Divisjoner: " << divAvdListe->noOfElements() << std::endl;
		std::cout << std::endl;
	}
	else
		std::cout << "Ingen divisjoner tilgjengelig.\n";
}

// Displayer data som skal skrives i I <navn>
void Idrett::displayResten() {
	divAvdListe->displayList();		// displayer alle divisjoner
}

// Sjekker om resultat er valid for spesifik idrett i RESULTAT.DTA
bool Idrett::lesResultat(bool oppdater, std::ifstream& inn) {
	char temp[STRLEN];	// char array som inneholder midlertidige verdier
	int numDiv;			// Antall divisjoner
	bool tempBool;

	inn >> numDiv; // Antall divisjoner for idretten som skal leses inn 
	inn.ignore();

	// Hver loop sjekker en divisjon
	for (int i = 0; i < numDiv; i++)
	{
		tempBool = true;
		inn.getline(temp, STRLEN); // Divisjon

		if (divAvdListe->inList(temp))  // Divisjonen temp eksisterer
		{
			DivAvd* tempDiv = (DivAvd*)divAvdListe->remove(temp);

			tempBool = tempDiv->lesResultat(oppdater, inn); // Sjekker data innenfor divisjon og oppdaterer dem om oppdater == true

			divAvdListe->add(tempDiv);	// Legger divisjonen tilbake i listen

			if (!tempBool) return false; // Hvis en feil var funnet, avbryt
		}
		else // temp eksisterer ikke
		{
			std::cout << "Divisjon " << temp << " eksisterer ikke!\n";
			return false;
		}
	}
	return true; // Hvis ingen feil er funnet vil koden komme hit og returnere true
}

void Idrett::skrivTilFil(std::ofstream& ut) {
	ut << tabellType << std::endl; // Kommer muligens ikke til å skrive riktig verdi

	// henter nummer av divisjoner
	int numDiv = divAvdListe->noOfElements();
	ut << numDiv << std::endl;

	DivAvd* tempDiv = nullptr;

	for (int i = 1; i <= numDiv; i++)
	{
		// Henter avdeling i
		tempDiv = (DivAvd*)divAvdListe->removeNo(i);

		tempDiv->skrivTilFil(ut);

		// Legger tilbake avdeling i
		divAvdListe->add(tempDiv);
	}
}