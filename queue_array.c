//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

/*
Datatypen K� enligt definitionen p� sidan 155 i Lars-Erik Janlert,
Torbj�rn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Implementerar k� med hj�lp av en array

Som standard s� �r anv�ndaren av datatypen ansvarig f�r att avallokera
minnet f�r datav�rdena. Genom att anropa queue_setMemHandler och till denna
skicka med en funktion f�r att avallokera ett dataobjekt s� kommer k�n
ta �ver ansvaret f�r minneshanteringen och automatiskt avallokera v�rdena
d� de tas bort fr�n k�n. OBS i detta fall s� m�ste anv�ndaren kopiera
v�rdena om de ska finnas kvar efter att ha tagits bort fr�n k�n.
*/

#include <stdlib.h>
#include "queue_array.h"

/*
Syfte: Skapa en ny k�
Returv�rde: Den nyskapade k� (queue *)
Kommentarer: D� man anv�nt k�n f�rdigt s� m�ste minnet f�r k�n
             avallokeras via funktionen queue_free
*/
queue *queue_empty() {
   queue *q = calloc(1, sizeof(queue));
   q->data=array_create(1,0,128);
   q->maxSize=128;
   q->start=q->stop=-1;
   return q;
}

/*
Syfte: Installera en minneshanterare f�r k�n s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i k�n mer.
Parametrar: q - K�n (queue *)
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i k�n).
Kommentarer: B�r anropas direkt efter att k�n skapats om funktionaliteten
             ska anv�ndas. K�n funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i k�n.
*/
void queue_setMemHandler(queue *q, memFreeFunc *f) {
    q->freeFunc=f;
}

/*
Syfte: Avallokera minne f�r k�n.
Parametrar: q - K�n (queue *)
Kommentarer: Minne f�r ev v�rden i k�n avallokeras bara om en funktion
             f�r detta �r satt via queue_setMemFunc. Annars �r det anv�ndarens
             uppgift att avallokera minnet f�r alla v�rden i k�n.
*/
void queue_free(queue *q) {
   if(q->freeFunc!=NULL) {
      while(!queue_isEmpty(q)) {
         queue_dequeue(q);
      }
   }
   array_free(q->data);
   free(q);
}

/*
Syfte: L�gga till ett v�rde sist i k�n
Parametrar: q - K�n (queue *)
            p - v�rdet som ska l�ggas till (data)
Kommentarer:
*/
void queue_enqueue(queue *q, data p) {
   q->size++;
   if(q->size == q->maxSize) {
       array *arr=array_create(1,0,q->maxSize*2);
       for(int i=0;i<q->maxSize;i++)
          array_setValue(arr,array_inspectValue(q->data,(q->start+1+i)%q->maxSize),i);
       array_free(q->data);
       q->start=-1;
       q->stop=q->size-2;
       q->data=arr;
       q->maxSize=q->maxSize*2;
   }
   q->stop = (q->stop+1)%q->maxSize;
   array_setValue(q->data,p,q->stop);
}

/*
Syfte: Konrollera om k�n �r tom
Parametrar: q - K�n (queue *)
Returv�rde: true om k�n �r tom false annars
Kommentarer:
*/
bool queue_isEmpty(queue *q) {
   return q->size == 0;
}

/*
Syfte: H�mtar f�rsta v�rdet i k�n
Parametrar: q - K�n (queue *)
Returv�rde: v�rdet som fanns l�ngst ram i k�n
Kommentarer: ej definierad f�r tom k�.
*/
data queue_front(queue *q) {
   if(q->size==0)
      return NULL;
   return array_inspectValue(q->data,(q->start+1)%q->maxSize);
}

/*
Syfte: Ta bort f�rsta v�rdet i k�n
Parametrar: q - K�n (queue *)
Kommentarer: odefinierad f�r en tom k�
*/
void queue_dequeue(queue *q) {
   if(q->size==0)
      abort();
   if(q->freeFunc!=NULL) 
      q->freeFunc(array_inspectValue(q->data,(q->start+1)%q->maxSize));
   q->size--;
   q->start = (q->start+1)%q->maxSize;
}

