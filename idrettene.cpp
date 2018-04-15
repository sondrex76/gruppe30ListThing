#include <fstream>
#include <iostream>
#include "idrettene.h"
#include "conster.h"
#include "idrett.h"
#include "globale_funksjoner.h"

using namespace std;

// Konstruktor
Idrettene::Idrettene() {
	idrettListe = new List(Sorted);
}

// Opretter ny idrett
void Idrettene::opprett()
{
					
	char navn[STRLEN];						// Navnetemp
	bool erIListen;							// Midlertidig verdi for å lagre om idretten allerede eksisterer

	do {
		les("Skriv inn idrettens navn", navn, STRLEN); // Henter idrettens navn

		erIListen = idrettListe->inList(navn);

		if (erIListen)
		cout << "Idretten eksisterer allerede!\nSkriv inn Q for a avslutte loopen\n";
	} while (erIListen && !isQ(navn));
	
	// Lag peker til idrettobjekt og legg til
	if (!isQ(navn)) // kjører koden hvis navn ikke er lik 'Q'(eller 'q')
	{
		cout << "Lager ny idrett.\n";
		Idrett* temp = new Idrett(navn);
		idrettListe->add(temp);
	}
	// idrettListe->displayList();			// DEBUG
	
}

						//returner nummeret til idretten i lista. evt 0
int Idrettene::faaNr(char* nvn)
{
	int nr = 0;
	if (idrettListe->inList(nvn))				//hvis i lista
	{
		for (int i = 1; i <= idrettListe->noOfElements(); i++)
		{
			//temp som sjekker om de matcher
			Idrett* temp = (Idrett*)idrettListe->removeNo(i);

			if (temp->likSom(nvn))				//er de like?
			{
				nr = i;
			}
			idrettListe->add(temp);			//legges tilbake i lista
		}
	}
	return nr;		//returnerer 0 om ikke funnet. eller nummer i lista
}

void Idrettene::leggTilDiv(int nr)
{
	Idrett* temp = (Idrett*)idrettListe->removeNo(nr);	//lager temp

	char navn[STRLEN];

	// Finn filnavn eller skriv inn Q

	cout << "Skriv inn Q for a avbryte\n";

	do {
		les("Skriv inn navn pa fil(inkludert ending)", navn, STRLEN);
		
		// Sjekker om filen eksisterer
	} while (!ifstream(navn) && !isQ(navn));


	// Hvis koden ikke skal avbrytes
	if (!isQ(navn))
	{
		ifstream nyDiv(navn); // lager ny ifstream for filen

		// Loop kjører til q er skrevet, eller ett nytt avdelingsnavn er skrevet
		do {
			les("Skriv inn navnet pa div/avd", navn, STRLEN);
		} while (!temp->leggTilDiv(nyDiv, navn) && !isQ(navn));

		nyDiv.close(); // Lukker filen
	}


	idrettListe->add(temp); // kjører koden hvis brukeren ikke skrev inn Q
}

// Fjerner idretten navn
void Idrettene::fjernIdrett(char* navn)
{
	if (idrettListe->inList(navn))
	{
		// Henter idretten som skal fjernes
		Idrett* temp = (Idrett*)idrettListe->remove(navn);

		//dobbeltsjekker at man vil slette
		cout << "Skriv Y for a bekrefte at du onsker a slette idretten " << navn << endl;
		
		// Sjekekr om brukeren skrev in Y for å bekrefte sletting av idretten
		if (les(false) != 'Y')
		{
			idrettListe->add(temp);
			cout << "Sletting av idretten " << navn << " har blitt avbrutt.\n";
		}
		else
			delete temp; // Sletter idretten
	}
	else cout << "Denne idretten finnes ikke.\n";
}

// Fjerner en divisjon innenfor idretten navn
void Idrettene::fjernDiv()
{
	char navn[STRLEN];
	bool temp;

	do {
		les("Skriv inn navn pa divisjonens idrett", navn, STRLEN);
		temp = idrettListe->inList(navn);

		if (!temp && !isQ(navn)) cout << "Idretten " << navn << " var ikke funnet!\n";
	} while (!temp && !isQ(navn));

	if (!isQ(navn))
	{
		// Henter idrettens navn
		Idrett* temp = (Idrett*)idrettListe->remove(navn);

		// Sletter en divisjon(hvilken blir valgt inni funksjonen
		temp->slettDiv();
		
		// Legegr tilbake tmep til listen
		idrettListe->add(temp);
	}
}

bool Idrettene::harIdrett(char* navn)
{
	return idrettListe->inList(navn);
}

void Idrettene::skrivTerminListe(char* navn)
{
	Idrett* temp = (Idrett*)idrettListe->remove(navn); // Lager temp

	temp->skrivTerminListe();						// Går videre

	idrettListe->add(temp);					// Legger tilbake til listen
}

//skriver ut kamp basert på dato
void Idrettene::skrivKamp(char* navn)
{
	Idrett* temp = (Idrett*)idrettListe->remove(navn); //temp

	temp->skrivKamp();	// Leser inn divisjon, filnavn og dato og skriver ut eller til fil

	idrettListe->add(temp);            //legger tilbake i lista
}

void Idrettene::skrivLag(char* navn)
{
		Idrett* temp = (Idrett*)idrettListe->remove(navn); // Lager temp

		temp->skrivLag();						// Går videre

		idrettListe->add(temp);					// Legger tilbake til listen
}

void Idrettene::redigerSpiller(char* navn)
{
	Idrett* temp = (Idrett*)idrettListe->remove(navn); //temp

	temp->redigerSpiller();

	idrettListe->add(temp);			//legger tilbake i lista
}

//sjekker om lista ikke er tom
bool Idrettene::ikkeTom()
{
	return idrettListe->noOfElements();
}

void Idrettene::skrivUt()
{
	char input[STRLEN];
	bool alle;

	// Henter idrettsnavn, verdien Q eller verdien A
	les("", input, STRLEN, false);

	if (isQ(input, 'A'))
		alle = true;
	else
		alle = false;

	removeSpaces(input);					// Fjerner eventuelle spacer fra starten

	if (!idrettListe->inList(input) && !isQ(input) && !isQ(input, 'A')) 
		cout << "Idretten " << input << " eksisterer ikke!\n";
	else {
		if (alle)	// Skriver ut alle idretter, nummer av divisjoner og tabelltype
		{
			if (idrettListe->noOfElements())			//sjekker at ikke tom
			{
				idrettListe->displayList();

				cout << endl;
			}
			else cout << "Det finnes ingen idretter.\n";
		}
		else		// Skriver ut idretten <navn>s nummer av divisjoner, tabelltype og divisjonsnavn i tilleg til antall lag i hver divisjon, navnene og adressene til disse lagene og antall spillere i hvert lag
		{
			// Displayer elementet om det eksisterer og skriver ut en beskje om det ikke eksisterer
			if (idrettListe->displayElement(input))
			{
				// Henter idrett <navn>
				Idrett* temp = (Idrett*)idrettListe->remove(input);

				// Skriver ut I <navn> spesifik info
				temp->displayResten();

				// Legger adressen tilbake i listen
				idrettListe->add(temp);
			}
			else	// Skriver ut reseten av den nødvendige infoen
				cout << "idretten " << input << " ble ikke funnet!\n";
		}
	}
}

// SJekker om RESULTAT.DTA er valid, eller skriver dataene basert på verdien til oppdater
bool Idrettene::lesResultat(bool oppdater) {
	bool tempBool; // Holder en verdi til alt nødvendig arbeid er gjort
	char temp[STRLEN];

	ifstream inn("RESULTAT.DTA");

	// Hver loop av while sjekker/leser inn en idrett
	while (!inn.eof()) // Mens filen ikke har sluttet
	{
		inn.getline(temp, STRLEN); // Henter idrettens navn

		// cout << "DEBUG: " << temp << endl; // DEBUG

		if (idrettListe->inList(temp)) // Idretten finnes
		{
			Idrett* tempIdrett = (Idrett*)idrettListe->remove(temp);

			inn.ignore();

			tempBool = tempIdrett->lesResultat(oppdater, inn);
			inn.ignore();
			idrettListe->add(tempIdrett); // Legger tilbake idretten i listen

			// Hvis indrettens data i RESULTAT.DTA hadde feil returnerer den false(og lukker ifstream)
			if (!tempBool) { inn.close(); return false; }
		}
		else // Idretten finnes ikke
		{
			cout << "Idretten " << temp << " eksisterer ikke!\n";
			inn.close();
			return false;
		}
	}

	// Hvis ingenting har returnert false til nå returnerer den true
	inn.close();
	return true;
}

// Skriver ut tabell av idrett eller div til fil eller skjerm
void Idrettene::skrivTabell(char* navn) {
	bool temp;
	Idrett* tempIdrett;

	// Henter idretten
	tempIdrett = (Idrett*)idrettListe->remove(navn);

	tempIdrett->skrivTabell();

	idrettListe->add(tempIdrett); // Legger idretten tilbake i listen
}

// Fjerner spiller nr fra alle divisjoner den er del av, og oppdaterer id-ene over i lagene den eksisterer
void Idrettene::fjernSpiller(int nr) {
	// Henter antall elementer o listen
	int antallIdretter = idrettListe->noOfElements();
	Idrett* temp;

	// Går gjennom alle idretter
	for (int i = 0; i < antallIdretter; i++) {
		temp = (Idrett*)idrettListe->removeNo(i);

		// Fjerner spiller nummer nr og oppdaterer relevante spiller ider
		temp->fjernSpiller(nr);

		// Legger idretten tilbake i listen
		idrettListe->add(temp);
	}
}

// Leser fra fil
void Idrettene::lesFraFil() {
	ifstream inn("IDRETTENE.DTA");

	Idrett* tempIdrett = nullptr;
	char tempNavn[STRLEN];
	int numSport = 0;

	inn >> numSport;
	inn.ignore();

	// cout << numSport << endl; // DEBUG

	// Hver loop henter en idrett
	for (int i = 0; i < numSport; i++) // leser fra fil så lenge den ikke slutter
	{
		//cout << i << endl; // DEBUG
		// cout << tempNavn << endl; // DEBUG
		// Henter sports navn
		// Loop for å forsikre at det er riktig linje
		do {
			inn.getline(tempNavn, STRLEN); // Henter sportsnavnet
		} while (!strlen(tempNavn));

		tempIdrett = new Idrett(tempNavn, inn);
		idrettListe->add(tempIdrett);				// Legger til idretten
	}

	inn.close();
}

// Skriver til fil i slutten av programmet
void Idrettene::skrivTilFil() {
	ofstream ut("IDRETTENE.DTA");
	
	// Antall sporter
	int sporter;
	sporter = idrettListe->noOfElements();
	ut << sporter << endl; // skriver sporter til fil

	Idrett* tempIdrett = nullptr;

	for (int i = 1; i <= sporter; i++)
	{
		// Henter sport nummer i
		tempIdrett = (Idrett*)idrettListe->removeNo(i);

		ut << tempIdrett->hentNavn() << endl;
		tempIdrett->skrivTilFil(ut);

		// Legger sport nr i tilbake i listen
		idrettListe->add(tempIdrett);
	}

	ut.close();
}