#if !defined(__GLOBALE_FUNKSJONER_H)
#define  __GLOBALE_FUNKSJONER_H


int les(char* info, int min, int max);		// Leser en int mellom min og max
char les(bool);								// Leser en enkelt char og kan ignorere resten av inputtet(true)
void les(char* info, char* txt, int MAXLEN);// Leser inn tekst(en linje)
bool isQ(char*);							// Sjekker om den sendte char arrayen er lik q eller Q
#endif