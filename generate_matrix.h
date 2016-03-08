#include "queue_array.h"
#include "array.h"
#include "graph_nav.h"

//Strukt ni ska anv�nda f�r noderna om ni t�nkt anv�nda generate matrix
typedef struct {
    bool visited; //b�r vara false f�r ny nod
    char *cityName; //minnet f�r str�ngen b�r ha lalokerats dynamiskt
} mapvertice;

//Struct f�r resultatet fr�n generateMatrixRepresentation
typedef struct arrayResult {
    array *verticeData; //inneh�ller stadsnamnen (p� samma index som de svarar
                        //mot i f�rbindelsematrisen)
    array *matrix; //inneh�ller f�rbindelsematris
} arrayResult;

/*
Syfte: Generera en f�rbindelsematris med pekare int-v�rden som inneh�ller avst�nd
       mellan noderna finns ingen f�rbindelse s� har motsvarande position v�rdet 0.
Parametrar: g- grafen. Grafen ska ha pekare till int v�rden p� kanterna och mapVertice 
               pekare som v�rden f�r noderna. Minne f�r dessa ska vara allokerat 
               dynamiskt (funktionen avallokerar sedan detta minne)
            numNodes - antalet noder i grafen
Returv�rde: Ett v�rde av typen arrayresultat (en struct) som inneh�ller en f�rbindelsematris
            (numNodes x numNodes stor indexerad fr�n 0) och en array (numNodes stor indexerat
            fr�n 0) som inneh�ller stadsnamnen i grafen f�r respektive index
            i f�rbindelsematrisen (eg p� index 0 ligger stadsnamnet som h�r till index 0 i
            matrisen osv).
Kommentarer: F�rbindelsematrisen och arrayen med stadsnamnen har b�da minneshanterare satta.
             Grafen kommer efter anrop att vara borttagen.
             Minneshaterare s�tts internt f�r grafen s� detta beh�ver ej g�ras innan anrop av
             funktionen.
*/
arrayResult generateMatrixRepresentation(graph *g,int numNodes);

//Funktion som beh�vs f�r att skapa en graf med mapVertice-noder
bool mapVerticeEqual(vertice v1,vertice v2);

/********************Hj�lpfunktioner*********************************/
//Anv�nds internt i generateMatrixRepresentation

int indexOfVertice(array *a,vertice v,int maxIndex,equalityFunc *verticeEQ);
bool mapVerticeIsVisited(vertice v);
void mapVerticeVisit(vertice v);
#ifndef __MAPVERTICEFREEFUNC
#define __MAPVERTICEFREEFUNC
void mapVerticeFree(vertice v);
#endif


bool strcmp2(void *str1,void *str2);

//strdup not available in c99 so providing my own implementation

/* Memory is allocated for the copy. Users of this function is responsible
 * for deallocating this memory */
char *strdup(const char *str);
