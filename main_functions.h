#if !defined(__MAIN_FUNCTIONS_H)
#define  __MAIN_FUNCTIONS_H

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
void skrivTilFil();			// Skriv til fil, aktiveres når programmet avsluttes
void lesFraFil();			// Leser fra fil, aktiveres på starten av programmet

#endif