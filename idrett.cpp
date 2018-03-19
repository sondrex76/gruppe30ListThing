#include <fstream>
#include <iostream> // DEBUG(så langt)
#include "idrett.h"
#include "ListTool2B.h"
#include "conster.h"
#include "globale_funksjoner.h"
#include "div_avd.h"

// Standard konstruktor
Idrett::Idrett(char* indrettsNavn) : TextElement(indrettsNavn) {

}

// construktor for idrett når man leser fra fil
Idrett::Idrett(char* indrettsNavn, std::ifstream& inn) : TextElement(indrettsNavn) {
	divAvd = new List(Sorted);	// Setter divAvd listetype til Sorted

	char tempAvdNavn[STRLEN];
	int numRepetasjoner;

	// Henter numerisk verdo for typen
	inn >> numRepetasjoner;
	inn.ignore();

	// Oversetter til den faktiske typen
	if (numRepetasjoner == 0) tabellType = ToEnNull;
	else if (numRepetasjoner == 1) tabellType = TreEnNull;
	else tabellType = TreToEnNull;

	std::cout << "Tabell type: " << tabellType << std::endl; // DEBUG

	inn >> tempAvdNavn; // Henter nummeret av avdelinger
	inn.ignore();
	numRepetasjoner = atoi(tempAvdNavn);

	std::cout << "Nummer av divisjoner: " << numRepetasjoner << std::endl; // DEBUG

	// Hver kjøring av loopen henter en ny avdeling
	for (int i = 1; i <= numRepetasjoner; i++)
	{
		inn.getline(tempAvdNavn, STRLEN);

		std::cout << "Divisjonsnavn: " << tempAvdNavn << std::endl;

		DivAvd* tempDiv = new DivAvd(tempAvdNavn, inn);
		divAvd->add(tempDiv); // legger til avdeling
	}
}