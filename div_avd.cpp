#include <fstream>
#include "div_avd.h"

using namespace std;

// Standard konstruktor
DivAvd::DivAvd(char* avdelingsNavn) {

}

// Konstruktor når man leser fra fil
DivAvd::DivAvd(char* avdelingsNavn, ifstream& inn) : TextElement(avdelingsNavn) {
	inn >> antLag; // Henter antall lag
	inn.ignore();
	inn.ignore();

	// Leser inn alle lag
	for (int i = 0; i < antLag; i++)
	{
		lag[i] = new Lag(inn);
		inn.ignore();
	}

	// Leser inn alle resultater


}

void DivAvd::lesFraFil() {

}

void DivAvd::skrivTilFil() {

}