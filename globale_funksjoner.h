#if !defined(__GLOBALE_FUNKSJONER_H)
#define  __GLOBALE_FUNKSJONER_H


int removeSpaces(char*, int = 0);
int les(char*, int, int);		// Leser en int mellom min og max
char les(bool);								// Leser en enkelt char og kan ignorere resten av inputtet(true)
void les(char*, char*, int, bool = true, bool = true);// Leser inn tekst(en linje)
bool isQ(char*, char = 'Q');							// Sjekker om den sendte char arrayen er lik q eller Q
void skrivQ();				//Skriver at man kan skrive Q for avslutning
bool erDel(const char*, const char*);
bool eksistererFil(const char*);
char* datoFormat(const char*);
#endif