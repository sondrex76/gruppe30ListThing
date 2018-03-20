# include <iostream>
#include "globale_funksjoner.h"

using namespace std;
//
//	les() funksjoner
//




// Returnerer en int mellom min og max
int les(char* info, int min, int max)
{
	int verdi; // Lagrer verdien man skriver inn

	do {
		cout << '\t' << info << "(" << min << "-" << max << ")"; // Printer ut info i tilleg til "(min-max)"
		cin >> verdi; // Henter verdien
		cin.ignore();
	} while (verdi > max || verdi < min); // checks if value is valid

	return verdi;
}

// Leser en enkelt char
char les(bool ignorerAndre)
{
	char ch;
	cin >> ch;

	// Ignorerer resten av karakterene hvis ignorerAndre == true
	if (ignorerAndre) cin.ignore();
	
	return toupper(ch);
}

// Returnerer en ikke tom string skrevet av brukeren
void les(char* info, char* txt, int MAXLEN)
{
	do {
		cout << '\t' << info << ": ";
		cin.getline(txt, MAXLEN);	// Henter en linje fra brukeren og kopierer den over til txt
	} while (strlen(txt) == 0);	// Forsikrer at brukeren ikke bare skrev inn enter
}

// Returnerer en bool basert på om den sendte char arrayen er q eller Q, eller noe annet
bool isQ(char* navn) {
	if (strlen(navn) == 1)
	{
		char ch = toupper(navn[0]);

		return ch == 'Q';
	}
	else return false;

}