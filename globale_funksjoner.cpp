#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include "globale_funksjoner.h"
#include <fstream>

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

// Returnerer en string skrevet av brukeren
// skrivUt avgjør om charen blir skrevet ut
// ignorerEnter avgjør om man kan skrive inn en tom tekst
void les(char* info, char* txt, int MAXLEN, bool skrivUt, bool ignoreEnter)
{
	do {
		if (skrivUt) cout << '\t' << info << ": ";
		cin.getline(txt, MAXLEN);	// Henter en linje fra brukeren og kopierer den over til txt

	// Forsikrer at brukeren ikke bare skrev inn enter med mindre det er lov
	} while (false && ignoreEnter && !strlen(txt));
}

// Returnerer en bool basert på om den sendte char arrayen er q eller Q, eller noe annet
bool isQ(char* navn, char Q) {
	
	if (strlen(navn) == 1 && Q == 'Q')
	{
		char ch = toupper(navn[0]);
		return ch == Q;
	}
	// Kode kjører 
	else if (Q != 'Q') // Hvis karakteren man søker etter ikke er Q
	{
		for (int i = 0; i < strlen(navn); i++)
		{
			if (toupper(navn[i]) != ' ' && toupper(navn[i]) != Q) return false;

			// Sjekker om navn[i] == Q og om det er siste element i arrayen
			if (toupper(navn[i]) == Q && i == strlen(navn) - 1) return true;
		}
		return false;
	}
	else return false;
}

int removeSpaces(char* tekst, int verdi) {
	// Hvis verdi er 0 blir den satt tol lengden av tekst
	if (verdi == 0) verdi = strlen(tekst);

	while (tekst[0] == ' ')
	{
		for (int i = 0; i < verdi - 1; i++)
		{
			tekst[i] = tekst[i + 1];
		}
		tekst[--verdi] = '\0';
	}
	return verdi;
}

// sjekker om sjekkErDel er en del av stringen string
bool erDel(const char* string, const char* sjekkErDel) {
	int len[2] = { strlen(string), strlen(sjekkErDel)};
	bool returnTrue;
	char* tempChar = new char[len[1] + 1];

	strcpy(tempChar, sjekkErDel);

	// Hvis første karakter er ett space


	len[1] = removeSpaces(tempChar, len[1]);


	if (len[0] >= len[1]) // Sjekker om string kan holde sjekkErDel
		for (int i = 0; i + len[1] <= len[0]; i++) // sjekker om den er lik fra i
		{
			returnTrue = true;

			for (int n = 0; n < len[1]; n++)
			{
				if (string[i + n] != tempChar[n]) // Hvis en karakter ikke er lik, avbryter loopen
				{
					returnTrue = false;
					break;
				}
			}

			// Hvis string inneholder sjekkErDel returneres true
			if (returnTrue)
			{
				delete tempChar;
				return true;
			}
		}
	delete tempChar;

	// Returnerer false hvis funksjonene kommer hit
	return false;
}

// Sjekker om filen eksisterer
bool eksistererFil(const char* fileNavn)
{
	ifstream fil(fileNavn);
	return fil.good();
}

// Sender tilbake en char som har formaten dd/mm
char* datoFormat(const char* dato) {
	char d[6] = "";
	d[0] = dato[6];
	d[1] = dato[7];
	d[2] = '/';
	d[3] = dato[4];
	d[4] = dato[5];
	d[5] = '\0';

	return d;
}