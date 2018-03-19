#include <iostream> // DEBUG(så langt)
#include <fstream>
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

	inn >> numRepetasjoner;		// Vill sannsyneligvis feile
	tabellType = (TabellType)numRepetasjoner;
	inn.ignore();				// Ignorerer resten av linjen



	inn >> numRepetasjoner; // Henter nummeret av avdelinger
	inn.ignore();

	// Hver kjøring av loopen henter en ny avdeling
	for (int i = 1; i <= numRepetasjoner; i++)
	{
		inn.getline(tempAvdNavn, STRLEN);


		DivAvd* tempDiv = new DivAvd(tempAvdNavn, inn);
		divAvd->add(tempDiv); // legger til avdeling
	}
}