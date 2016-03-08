/*
 * Copyright 2012 Johan Eliasson (johane@cs.umu.se). Till�telse ges f�r anv�ndning p� kurserna 
 * i Datastrukturer och algoritmer vid Ume� Universitet. All annan anv�ndning kr�ver f�rfattarens
 * tillst�nd.
 */

#include "graph_nav.h"

//Datatyp som anv�nds internt i implementationen. Ing�r ej i gr�nsytan
//och b�r ej utnyttjas av anv�ndaren
typedef struct node {
    vertice v;
    dlist *neigbours;
}node;

//Datatyp som anv�nds internt i implementationen. Ing�r ej i gr�nsytan
//och b�r ej utnyttjas av anv�ndaren
typedef struct {
    vertice v;
    data value;
} edge_internal;

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
graph *graph_empty(equalityFunc *eq) {
    graph *theGraph=calloc(1,sizeof(graph));
    theGraph->nodes=dlist_empty();
    theGraph->verticeEq=eq;
    return theGraph;
}

/*
Syfte: Installera en funktion som avallokerar minnet f�r etikett i en nod i grafen
Parametrar: g - Grafen
            f - Funktion som avallokerar minnet f�r en nod.
Kommentarer: Om funktionen inte anropats s� kr�vs att anv�ndaren avallokerar
             minnet f�r alla etiketter manuellt.
*/
void graph_setVerticeMemHandler(graph *g,verticeFreeFunc *f) {
    g->verticeFree=f;
}

/*
Syfte: Installera en funktion som avallokerar minnet f�r etikett p� en kant i grafen
Parametrar: g - Grafen
            f - En funktion som avallokerar minnet f�r ett v�rde som �r
                satt f�r en kant.
Kommentarer: Om funktionen inte anropats s� kr�vs att anv�ndaren avallokerar
             minnet f�r v�rdet p� kanten.
*/
void graph_setEdgeDataMemHandler(graph *g,edgeDataFreeFunc *f) {
    g->edgeDataFree=f;
}

/*
Syfte: Stoppa in en nod i grafen
Parametrar: g - grafen
            v - noden som ska s�ttas in
Kommentarer: noden ska inte finnas i grafen sedan tidigare
*/ 
void graph_insertNode(graph *g,vertice v) {
    node *newNode=malloc(sizeof(node));
    newNode->v=v;
    newNode->neigbours=dlist_empty();
    dlist_insert(g->nodes,dlist_first(g->nodes),newNode);
}

/*
Syfte: Stoppa in en kant i grafen
Parametrar: g - grafen
            e - kanten som ska s�ttas in.
Kommentarer: B�da de ing�ende noderna i kanten m�ste finnas i grafen
             innan denna funktion anropas.
*/ 
void graph_insertEdge(graph *g,edge e) {
    edge_internal *e_int1=calloc(1,sizeof(edge_internal));
    edge_internal *e_int2=calloc(1,sizeof(edge_internal));
    vertice vertice1;
    vertice vertice2;
    for(dlist_position p=dlist_first(g->nodes);!dlist_isEnd(g->nodes,p);
        p=dlist_next(g->nodes,p)) {
        node *n=dlist_inspect(g->nodes,p);
        vertice v=n->v;
        if(g->verticeEq(e.v1,v)) {
            vertice1=v;
            dlist_insert(n->neigbours,dlist_first(n->neigbours),e_int1);
        }
        else if (g->verticeEq(e.v2,v)) {
            vertice2=v;
            dlist_insert(n->neigbours,dlist_first(n->neigbours),e_int2);
        }
    }
    e_int1->v=vertice2;
    e_int2->v=vertice1;
}

/*
Syfte: Kontrollera om grafen �r tom
Parametrar: g - grafen
Returv�rde: returnerar true om grafen �r tom annars false
Kommentarer:
*/ 
bool graph_isEmpty(graph *g) {
    return dlist_isEmpty(g->nodes);
}

/*
Syfte: Kontrollera om grafen saknar kanter
Parametrar: g - grafen
Returv�rde: true om grafen saknar kanter, annars false
Kommentarer:
*/ 
bool graph_hasNoEdges(graph *g) {
    for(dlist_position p=dlist_first(g->nodes);!dlist_isEnd(g->nodes,p);
        p=dlist_next(g->nodes,p)) {
        node *node=dlist_inspect(g->nodes,p);
        if(!dlist_isEmpty(node->neigbours))
            return false;
    }
    return true;
}

/*
Syfte: H�mta ut en slumpm�ssig nod ur grafen
Parametrar: g - grafen
Returv�rde: en nod som finns i grafen.
Kommentarer:
*/ 
vertice graph_chooseNode(graph *g) {
    node *n=dlist_inspect(g->nodes,dlist_first(g->nodes));
    return n->v;
}

/*
Syfte: H�mtar en lista med grannarna till en nod
Parametrar: g - grafen
            v - Noden vars grannar ska h�mtas
Returv�rde: listan med grannarna (inneh�ller v�rden av typen vertice)
Kommentarer: Anv�ndaren ansvarar f�r att avallokera minnet f�r listan
             d� denna inte beh�vs igen. Noderna i listan �gs av grafen.
*/ 
dlist *graph_neighbours(graph *g,vertice v) {
    dlist *list=dlist_empty();
    for(dlist_position p=dlist_first(g->nodes);!dlist_isEnd(g->nodes,p);
        p=dlist_next(g->nodes,p)) {
        node *n=dlist_inspect(g->nodes,p);
        if(g->verticeEq(v,n->v)) {
            for(dlist_position p2=dlist_first(n->neigbours);
                !dlist_isEnd(n->neigbours,p2);
                p2=dlist_next(n->neigbours,p2)) {
                edge_internal *myedge=dlist_inspect(n->neigbours,p2);
                dlist_insert(list,dlist_first(list),myedge->v);
            }
        }
    }
    return list;
}

/*
Syfte: Tabort en nod ur tr�det
Parametrar: g - grafen
            v - noden som ska tas bort
Kommentarer: Minnet f�r nodens etikett avallokeras bara om en funktion
             f�r detta satts via setVerticeMemHandler-funktionen.
*/ 
void graph_deleteNode(graph *g,vertice v) {
    for(dlist_position p=dlist_first(g->nodes);!dlist_isEnd(g->nodes,p);p=dlist_next(g->nodes,p)) {
        node *n=dlist_inspect(g->nodes,p);
        vertice v2=n->v;
        if(g->verticeEq(v,v2)) {
            dlist_remove(g->nodes,p);
            dlist_free(n->neigbours);
            if(g->verticeFree && n->v)
                g->verticeFree(n->v);
            free(n);
            return;
        }
    }
}

/*
Syfte: H�mta ett v�rde p� en kant
Parametrar: g - grafen
            e - kanten vars v�rde ska h�mtas.
Returv�rde: v�rdet p� kanten
Kommentarer: Ej definierad om en kant saknas eller om ett v�rde ej satts f�r
             kanten
*/ 
data graph_inspectEdgeLabel(graph *g,edge e) {
    for(dlist_position p=dlist_first(g->nodes);!dlist_isEnd(g->nodes,p);p=dlist_next(g->nodes,p)) {
        node *n=dlist_inspect(g->nodes,p);
        vertice v=n->v;
        if(g->verticeEq(e.v1,v)) {
            for(dlist_position p2=dlist_first(n->neigbours);
                !dlist_isEnd(n->neigbours,p2);
                p2=dlist_next(n->neigbours,p2)) {
                edge_internal *e_int=dlist_inspect(n->neigbours,p2);
                if(g->verticeEq(e.v2,e_int->v)) {
                    return e_int->value;
                }
            }
        }
    }
    return NULL;
}

/*
Syfte: Associera ett v�rde med en kant i grafen
Parametrar: g - Grafen.
            e - Kanten som ska f� ett v�rde.
            label - V�rdet som kanten ska ha.
Kommentarer: kanten ska finnas i grafen innan anropet av denna funktion.
*/ 
void graph_setEdgeLabel(graph *g,edge e,data label) {
    for(dlist_position p=dlist_first(g->nodes);
        !dlist_isEnd(g->nodes,p);p=dlist_next(g->nodes,p)) {
        node *n=dlist_inspect(g->nodes,p);
        vertice v=n->v;
        if(g->verticeEq(e.v1,v)) { //If its the first vertice
            for(dlist_position p2=dlist_first(n->neigbours);
                !dlist_isEnd(n->neigbours,p2);
                p2=dlist_next(n->neigbours,p2)) {
                edge_internal *e_int=dlist_inspect(n->neigbours,p2);
                if(g->verticeEq(e.v2,e_int->v)) {
                    e_int->value=label;
                }
            }
        }
        if(g->verticeEq(e.v2,v)) { //If its the second vertice
            for(dlist_position p2=dlist_first(n->neigbours);
                !dlist_isEnd(n->neigbours,p2);
                p2=dlist_next(n->neigbours,p2)) {
                edge_internal *e_int=dlist_inspect(n->neigbours,p2);
                if(g->verticeEq(e.v1,e_int->v)) {
                    e_int->value=label;
                }
            }
        }
    }
}

/*
Syfte: Unders�ka om en kant har ett associerat v�rde satt i grafen
Parametrar: g - grafen
Returv�rde: returnerar true om kanten har ett v�rde satt annars false
Kommentarer:
*/ 
bool graph_hasEdgeLabel(graph *g,edge e) {
    for(dlist_position p=dlist_first(g->nodes);!dlist_isEnd(g->nodes,p);p=dlist_next(g->nodes,p)) {
        node *n=dlist_inspect(g->nodes,p);
        vertice v2=n->v;
        if(g->verticeEq(e.v1,v2)) {
            for(dlist_position p2=dlist_first(n->neigbours);
                !dlist_isEnd(n->neigbours,p2);
                p2=dlist_next(n->neigbours,p2)) {
                edge_internal *e_int=dlist_inspect(n->neigbours,p2);
                if(g->verticeEq(e.v2,e_int->v)) {
                    return e_int->value!=NULL;
                }
            }
        }
    }
    return false;
}

/*
Syfte: Tar bort en kant fr�n grafen
Parametrar: g - grafen
            e - kanten som ska tas bort
Kommentarer: Minne f�r v�rden p� etiketten avallokeras endast om en funktion
             f�r att g�ra detta har satta via setEdgeDataMemHandler-funktionen
*/ 
void graph_deleteEdge(graph *g,edge e) {
    for(dlist_position p=dlist_first(g->nodes);!dlist_isEnd(g->nodes,p);
        p=dlist_next(g->nodes,p)) {
        node *n=dlist_inspect(g->nodes,p);
        vertice v2=n->v;
        if(g->verticeEq(e.v1,v2)) {
            for(dlist_position p2=dlist_first(n->neigbours);
                !dlist_isEnd(n->neigbours,p2);
                p2=dlist_next(n->neigbours,p2)) {
                edge_internal *e_int=dlist_inspect(n->neigbours,p2);
                if(g->verticeEq(e.v2,e_int->v)) {
                    if(g->edgeDataFree && e_int->value) {
                         g->edgeDataFree(e_int->value);
                    }
                    free(e_int);
                    dlist_remove(n->neigbours,p2);
                    break; //Only one edge possible between two nodes
                }
            }
        }
        if(g->verticeEq(e.v2,v2)) {
            for(dlist_position p2=dlist_first(n->neigbours);
                !dlist_isEnd(n->neigbours,p2);
                p2=dlist_next(n->neigbours,p2)) {
                edge_internal *e_int=dlist_inspect(n->neigbours,p2);
                if(g->verticeEq(e.v1,e_int->v)) {
                    //memory only allocated once for edge values so we
                    //don't need to do it here
                    //if(g->edgeDataFree && e_int->value) {
                    //     g->edgeDataFree(e_int->value);
                    //}
                    free(e_int);
                    dlist_remove(n->neigbours,p2);
                    break; //Only one edge possible between two nodes
                }
            }
        }
    }
}

/*
Syfte: Avallokera allt minne som upptas av grafen
Parametrar: g - grafen
Kommentarer: Om minneshanterare installerats f�r att ta hand om kanter
             och nodetiketter kommer �ven minnet f�r dessa att avallokeras.
*/ 
void graph_free(graph *g) {
    while(!dlist_isEmpty(g->nodes)) {
        node *n=dlist_inspect(g->nodes,dlist_first(g->nodes));
        while(!dlist_isEmpty(n->neigbours)) {
            edge_internal *e_int=dlist_inspect(n->neigbours,dlist_first(n->neigbours));
            edge e={n->v,e_int->v};
            graph_deleteEdge(g,e);
        }
        graph_deleteNode(g,n->v);
    }
    dlist_free(g->nodes);
    free(g);
}
