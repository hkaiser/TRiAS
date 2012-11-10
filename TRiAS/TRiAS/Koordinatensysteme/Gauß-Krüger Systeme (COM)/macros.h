// Macros.h
// ein paar kleine Macros für dieses Projekt

// testen eines Pointers p und verlassen der Funktion mit 
// angegebenem Fehlercode erg, wenn Ptr ungültig
#define CHECKPOINTERHR(p, erg)	\
	ASSERT(p);					\
	if (NULL == p)				\
		return erg;

// dito, mit E_POINTER
#define CHECKPOINTER(p) \
	CHECKPOINTERHR(p, E_POINTER);

// define für kommentierende Pragmas
// Usage : #pragma MSG("Das ist ein sinnloser Kommentar der beim kompilieren erscheint")
#define MSG3(x) #x 
#define MSG2(x) MSG3(x)
#define MSG(a) message(__FILE__ "("MSG2(__LINE__)") : " a)
