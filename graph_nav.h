/*
 * Copyright 2012 Johan Eliasson (johane@cs.umu.se). Till�telse ges f�r anv�ndning p� kurserna 
 * i Datastrukturer och algoritmer vid Ume� Universitet. All annan anv�ndning kr�ver f�rfattarens
 * tillst�nd.
 */

/*
Implementation av ordnad oriktad graf med m�jlighet till att ha vikter p� noderna. Datatypen f�ljer till stora delar definitionen av datatypen Graf p� sidan 339 i kursboken (med undantag f�r 3 funktioner f�r att hantera vikter p� kanterna) Lars-Erik Janlert,
Torbj�rn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include "dlist.h"

//datatyp f�r en nod (valfri pekartyp)
typedef data vertice;

//Datatyp f�r en kant (best�r av tv� noder)
typedef struct edge {
    vertice v1;
    vertice v2;
} edge;

/*Datatyp f�r j�mf�relsefunktion f�r noder. Ska returnera true om de
  tv� kanterna som anges som parameter �r lika
 */
typedef bool equalityFunc(vertice v1, vertice v2);

/* Datatyp f�r funktion som avallokerar minne f�r en nod */
#ifndef __VERTICEFREEFUNC
#define __VERTICEFREEFUNC
typedef void verticeFreeFunc(vertice v);
#endif


/*Datatyp f�r funktion som avallokerar minne f�r ett kant v�rde */    
#ifndef __EDGEDATAFREEFUNC
#define __EDGEDATAFREEFUNC
typedef void edgeDataFreeFunc(data d);
#endif


//Datatyp f�r grafen. B�r endast f�r�ndras via funktionerna i gr�nsytan.
typedef struct graph {
    dlist *nodes;
    equalityFunc *verticeEq;
    verticeFreeFunc *verticeFree;
    edgeDataFreeFunc *edgeDataFree;
} graph;

/*
Syfte: Skapa en ny graf
Parametrar: eq - Funktion f�r att avg�ra om tv� noder (v�rden av typen
                 vertice) i grafen �r lika.
Returv�rde: Den nyskapade grafen
Kommentarer: Om minneshanterare f�r nod och kant v�rden installerats mha
             setXXXMemHandler funktionerna s� kommer minnet f�r dessa att
             avallokeras d� v�rdena inte l�ngre finns kvar i grafen.
             Annars ansvarar anv�ndaren av datatypen f�r att dessa
             v�rden avallokeras.
*/
graph *graph_empty(equalityFunc *eq);

/*
Syfte: Installera en funktion som avallokerar minnet f�r etikett i en nod i grafen
Parametrar: g - Grafen
            f - Funktion som avallokerar minnet f�r en nod.
Kommentarer: Om funktionen inte anropats s� kr�vs att anv�ndaren avallokerar
             minnet f�r v�rdet p� noden.
*/
void graph_setVerticeMemHandler(graph *g,verticeFreeFunc *f);

/*
Syfte: Installera en funktion som avallokerar minnet f�r etikett p� en kant i grafen
Parametrar: g - Grafen
            f - En funktion som avallokerar minnet f�r ett v�rde som �r
                satt f�r en kant.
Kommentarer: Om funktionen inte anropats s� kr�vs att anv�ndaren avallokerar
             minnet f�r v�rdet p� kanten.
*/
void graph_setEdgeDataMemHandler(graph *g,edgeDataFreeFunc *f);

/*
Syfte: Stoppa in en nod i grafen
Parametrar: g - grafen
            v - noden som ska s�ttas in
Kommentarer: noden ska inte finnas i grafen sedan tidigare
*/
void graph_insertNode(graph *g,vertice v);

/*
Syfte: Stoppa in en kant i grafen
Parametrar: g - grafen
            e - kanten som ska s�ttas in.
Kommentarer: B�da de ing�ende noderna i kanten m�ste finnas i grafen
             innan denna funktion anropas.
*/
void graph_insertEdge(graph *g,edge e);

/*
Syfte: Kontrollera om grafen �r tom
Parametrar: g - grafen
Returv�rde: returnerar true om grafen �r tom annars false
Kommentarer:
*/
bool graph_isEmpty(graph *g);

/*
Syfte: Kontrollera om grafen saknar kanter
Parametrar: g - grafen
Returv�rde: true om grafen saknar kanter, annars false
Kommentarer:
*/
bool graph_hasNoEdges(graph *g);

/*
Syfte: H�mta ut en slumpm�ssig nod ur grafen
Parametrar: g - grafen
Returv�rde: en nod som finns i grafen.
Kommentarer:
*/
vertice graph_chooseNode(graph *g);

/*
Syfte: H�mtar en lista med grannarna till en nod
Parametrar: g - grafen
            v - Noden vars grannar ska h�mtas
Returv�rde: listan med grannarna (inneh�ller v�rden av typen vertice)
Kommentarer: Anv�ndaren ansvarar f�r att avallokera minnet f�r listan
             d� denna inte beh�vs igen. Noderna i listan �gs av grafen.
*/
dlist *graph_neighbours(graph *g,vertice v);

/*
Syfte: Tabort en nod ur tr�det
Parametrar: g - grafen
            v - noden som ska tas bort
Kommentarer: Minnet f�r nodens etikett avallokeras bara om en funktion
             f�r detta satts via setVerticeMemHandler-funktionen.
*/
void graph_deleteNode(graph *g,vertice v);

/*
Syfte: Tar bort en kant fr�n grafen
Parametrar: g - grafen
            e - kanten som ska tas bort
Kommentarer: Minne f�r v�rden p� etiketten avallokeras endast om en funktion
             f�r att g�ra detta har satta via setEdgeDataMemHandler-funktionen
*/
void graph_deleteEdge(graph *g,edge e);

/*
Syfte: Unders�ka om en kant har ett associerat v�rde satt i grafen
Parametrar: g - grafen
Returv�rde: returnerar true om kanten har ett v�rde satt annars false
Kommentarer:
*/
bool graph_hasEdgeLabel(graph *g,edge e);

/*
Syfte: Associera ett v�rde med en kant i grafen
Parametrar: g - Grafen.
            e - Kanten som ska f� ett v�rde.
            label - V�rdet som kanten ska ha.
Kommentarer: kanten ska finnas i grafen innan anropet av denna funktion.
*/
void graph_setEdgeLabel(graph *g,edge e,data label);

/*
Syfte: H�mta ett v�rde p� en kant
Parametrar: g - grafen
            e - kanten vars v�rde ska h�mtas.
Returv�rde: v�rdet p� kanten
Kommentarer: Ej definierad om en kant saknas eller om ett v�rde ej satts f�r
             kanten
*/
data graph_inspectEdgeLabel(graph *g,edge e);

/*
Syfte: Avallokera allt minne som upptas av grafen
Parametrar: g - grafen
Kommentarer: Om minneshanterare installerats f�r att ta hand om kanter
             och nodetiketter kommer �ven minnet f�r dessa att avallokeras.
*/
void graph_free(graph *g);

#endif
