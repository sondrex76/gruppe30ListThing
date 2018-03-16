#if !defined(__DIV_AVD_H)
#define  __DIV_AVD_H

#include "ListTool2B.h"
#include "lag.h"

// Er en divisjon/avdeling av en sport
// Sortert etter navn av divisjon/avderling
class DivAvd : TextElement {
private:
	int antLag;		// Antall lag i divisjon
	Lag lag[30];	// Lagene i divisjonen
	// Mangler to dimensjonal matrise av Resultat objekter for terminlisten av resultater
public:
	DivAvd();
};

#endif