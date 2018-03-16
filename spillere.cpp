#include "spillere.h"

// Konstruktor for Spillere
Spillere::Spillere() {
	spiller = new List(Sorted); // setter spiller listen som sorted
}