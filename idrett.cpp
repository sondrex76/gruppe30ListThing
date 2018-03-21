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

								//fikser enum
	switch (nr)
	{
	case 1: tabellType = ToEnNull; break;
	case 2: tabellType = TreEnNull; break;
	case 3: tabellType = TreToEnNull; break;
	default: std::cout << "wtf happnd? enum failz? :c"; //burde ikke komme
	}
}

// construktor for idrett når man leser fra fil
Idrett::Idrett(char* indrettsNavn, std::ifstream& inn) : TextElement(indrettsNavn) {
	divAvdListe = new List(Sorted);	// Setter divAvd listetype til Sorted

	char tempAvdNavn[STRLEN];
	int numRepetasjoner; // verdi som lagrer inter hentet ut av filen

	// Henter numerisk verdo for typen
	inn >> numRepetasjoner; 
	inn.ignore();

	// Oversetter til den faktiske typen
	if (numRepetasjoner == 0) tabellType = ToEnNull;
	else if (numRepetasjoner == 1) tabellType = TreEnNull;
	else tabellType = TreToEnNull;

	// std::cout << "Tabell type: " << tabellType << std::endl; // DEBUG

	inn >> numRepetasjoner; // Henter nummeret av avdelinger
	inn.ignore();

	//std::cout << "Nummer av divisjoner: " << numRepetasjoner << std::endl; // DEBUG

	// Hver kjøring av loopen henter en ny avdeling
	for (int i = 1; i <= numRepetasjoner; i++)
	{
		inn.getline(tempAvdNavn, STRLEN);

		//std::cout << "Divisjonsnavn: " << tempAvdNavn << std::endl; // DEBUG

		DivAvd* tempDiv = new DivAvd(tempAvdNavn, inn);
		divAvdListe->add(tempDiv); // legger til avdeling
	}
}

char* Idrett::hentNavn() {
	return text; // returnerer navn
}
									//legger til ny divisjon om mulig
bool Idrett::leggTilDiv(char* navn)
{
	if (!divAvdListe->inList(navn))			//hvis den ikke er i lista
	{
		DivAvd* temp = new DivAvd(navn);

		divAvdListe->add(temp);

		//display();			//for å sjekke at det virker
		return true;
	}
	else
	{
		std::cout << "Dette navnet finnes alt.\n";
		return false;
	}
}

//sletter en divisjon
void Idrett::slettDiv()
{
	if (divAvdListe->noOfElements())		//hvis ikke tom
	{
	char navn[STRLEN];
	les("Skriv inn navn pa idrett du vil fjerne", navn, STRLEN);

	if (divAvdListe->inList(navn))				//hvis navn finnes
	{
		//looper igjennom alle divisjonene
		for (int i = 1; i <= divAvdListe->noOfElements(); i++)
		{
			//temp som sjekker om de matcher
			DivAvd* temp = (DivAvd*)divAvdListe->removeNo(i);

			if (strcmp(temp->hentNavn(), navn))		//hvis ulik navn
			{
				divAvdListe->add(temp);
			}
			else
			{
				//ellers ber vi om vi skal slette
				std::cout << "Vil du virkelig slette divisjonen? Y/N ";
				if (les(false) != 'Y')
				{
					std::cout << "Sletter...\n";
					divAvdListe->add(temp);
				}
				else std::cout << "Sletter ikke.\n";
			}
		  }
		}
		else std::cout << "Finner ikke divisjon.\n";
	}
	else std::cout << "Det er ingen divisjoner i denne idretten.\n";
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

void Idrett::laglag(char* navn)
{
	if (divAvdListe->inList(navn))
	{
		for (int i = 1; i <= divAvdListe->noOfElements(); i++)
		{
			//temp som sjekker om de matcher
			DivAvd* temp = (DivAvd*)divAvdListe->removeNo(i);
			
			if (!strcmp(temp->hentNavn(), navn))		//hvis ulik navn
			{
				temp->lagLag();
			}
			divAvdListe->add(temp);
		}
	}
	else if (!divAvdListe->noOfElements())
	{
		std::cout << "Ingen divisjoner.\n";
	}
	else std::cout << "Fant ikke divisjonen.\n";
}

							//displayer objektets variabler
void Idrett::display()
{
	std::cout << "Skriver ut navn: " << text << std::endl
		<< "Tabelltype: " << tabellType << std::endl;

	if (divAvdListe->noOfElements())
	{
		std::cout << "Divisjoner: \n" << std::endl;
		divAvdListe->displayList();		// displayer alle divisjoner
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Ingen divisjoner tilgjengelig.\n";
	}
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