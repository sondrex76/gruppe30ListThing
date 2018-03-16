#if !defined(__GLOBALE_FUNKSJONER_H)
#define  __GLOBALE_FUNKSJONER_H

int les(char* info, int min, int max);		// Leser en int mellom min og max
char les(bool);								// Leser en enkelt char og kan ignorere resten av inputtet(true)
void les(char* info, char* txt, int MAXLEN);// Leser inn tekst(en linje)

void skrivSpiller();		// S A | <nr> | <navn> - skriv Alle spillere eller spiller med <nr> / <navn>
void skrivIdrett();			// I A <navn> - skriv Alle idrettene eller idretten <navn>
void lagNy();				// N S | I  D - Ny spiller, idrett eller divisjon
void fjern();				// F S | I | D - Fjern spiller, idrett eller divisjon
void skrivTerminListe();	// L Skriv terminliste for en gitt divisjon til skjerm eller fil
// (K)skriv resultatet av alle kampene en gitt dato for ne idrett eller en divisjon til skjerm eller fil
void skrivKampene();		
void skrivTabell();			// (T)Skriv tabell(er) for en hel idrett eller en divisjon til fil eller skjerm
void lesResultat();			// (R)Les resultatliste fra fil
void skrivLag();			// (D)Data om alle spillerne i et lag
void redigerSpiller();		// (E)Endre spillere på et lag(legg til/fjern)


#endif