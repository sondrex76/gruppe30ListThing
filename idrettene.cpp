#include <iostream>
#include "idrettene.h"
#include "conster.h"
#include "idrett.h"
#include "globale_funksjoner.h"

// Konstruktor
Idrettene::Idrettene() {
	idrettListe = new List(Sorted);
}

void Idrettene::opprett()
{
	
	char navn[STRLEN]; 
	les("Skriv inn idrettens navn", navn, STRLEN);
	Idrett temp;
	//idrett->add(1);

}

void Idrettene::lesFraFil() {

}

void Idrettene::skrivTilFil() {

}