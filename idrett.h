#if !defined(__IDRETT_H)
#define  __IDRETT_H

#include "ListTool2B.h"
#include "enumer.h"

// Er sortert etter dets navn
class Idrett : public TextElement {
private:
	List* divAvd;			// Liste av alle divisjoner/avdelinger av idretten
	TabellType tabellType;	// Enum som lagrer typen tabell(2/1/0, 3/1/0, 3/2/1/0) brukt i idretten
public:

};

#endif