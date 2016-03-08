#include "generate_matrix.h"
#include <string.h>

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
arrayResult generateMatrixRepresentation(graph *g,int numNodes) {
    arrayResult result;
    int i,j;
    int nodeIndex=0;
    graph_setVerticeMemHandler(g,mapVerticeFree);
    graph_setEdgeDataMemHandler(g,free);
    result.matrix=array_create(2,0,0,numNodes-1,numNodes-1);
    array_setMemHandler(result.matrix,free);
    result.verticeData=array_create(1,0,numNodes-1);
    array_setMemHandler(result.verticeData,free);
    vertice startV;
    while(!graph_isEmpty(g)) {
        startV=graph_chooseNode(g);
        if(mapVerticeIsVisited(startV)) {
            graph_deleteNode(g,startV);
        }
        else {
            queue *q=queue_empty();
            queue_enqueue(q,startV);
            mapVerticeVisit(startV);
            while(!queue_isEmpty(q)) {
                mapvertice *v=queue_front(q);
                int indexOfV=indexOfVertice(result.verticeData,v->cityName,nodeIndex,strcmp2);
                if(indexOfV==-1) {
                    array_setValue(result.verticeData,strdup(v->cityName),nodeIndex);
                    indexOfV=nodeIndex;
                    nodeIndex++;
                }
                queue_dequeue(q);
                dlist *neighbours=graph_neighbours(g,v);
                for(dlist_position p=dlist_first(neighbours);
                    !dlist_isEnd(neighbours,p);
                    p=dlist_next(neighbours,p)) {
                    mapvertice *v2=dlist_inspect(neighbours,p);
                    if(!mapVerticeIsVisited(v2)) {
                        queue_enqueue(q,v2);
                        mapVerticeVisit(v2);
                    }
                    int indexOfV2=indexOfVertice(result.verticeData,v2->cityName,nodeIndex,strcmp2);
                    if(indexOfV2==-1) {
                        array_setValue(result.verticeData,strdup(v2->cityName),nodeIndex);
                        indexOfV2=nodeIndex;
                        nodeIndex++;
                    }
                    edge e={v,v2};
                    int *ip=malloc(sizeof(int));
                    *ip=*(int *) graph_inspectEdgeLabel(g,e);
                    int *ip2=malloc(sizeof(int));
                    *ip2=*ip;
                    array_setValue(result.matrix,ip,indexOfV,indexOfV2);
                    array_setValue(result.matrix,ip2,indexOfV2,indexOfV);
                    graph_deleteEdge(g,e);
                }
                dlist_free(neighbours);
            }
            queue_free(q);
        }
    }
    
    //Fill remaining positions in the array with zeros
    for(i=0;i<nodeIndex;i++) {
        for(j=0;j<nodeIndex;j++) {
            if(!array_hasValue(result.matrix,i,j)) {
                array_setValue(result.matrix,calloc(1,sizeof(int)),i,j);
            }
        }
    }
    graph_free(g);
    return result;
}




/******************************Hj�lpfunktioner*************************************/
bool strcmp2(void *str1,void *str2) {
    return strcmp((char *)str1,(char *)str2)==0;
}

bool mapVerticeEqual(vertice v1,vertice v2) {
   mapvertice *mv1=v1;
   mapvertice *mv2=v2;
   return strcmp(mv1->cityName,mv2->cityName)==0;
}

bool mapVerticeIsVisited(vertice v) {
    mapvertice *mv=v;
    return mv->visited;
}

void mapVerticeVisit(vertice v) {
    mapvertice *mv=v;
    mv->visited=true;
}

void mapVerticeFree(vertice v) {
    mapvertice *mv=v;
    free(mv->cityName);
    free(mv);
}

int indexOfVertice(array *a,vertice v,int maxIndex,equalityFunc *verticeEQ) {
    for(int i=0;i<maxIndex;i++) {
        if(verticeEQ(v,array_inspectValue(a,i)))
            return i;
    }
    return -1;
}
