//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

#include "list_array.h"

/*
Datatypen Lista enligt definitionen p� sidan 44 i Lars-Erik Janlert,
Torbj�rn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Implementerar lista mha datatypen f�lt. Om det underlliggande f�ltet blir
f�r litet kommer ett nytt dubbelt s� kommer minne allokeras f�r ett dubbelt
s� stort f�lt och v�rdena kopieras �ver till detta. Listan lagrar v�rden av
typen (void * kallad data).

Som standard s� �r anv�ndaren av datatypen ansvarig f�r att avallokera
minnet f�r datav�rdena. Genom att anropa list_setMemHandler och till denna
skicka med en funktion f�r att avallokera ett dataobjekt s� kommer listan
ta �ver ansvaret f�r minneshanteringen och automatiskt avallokera v�rdena
d� de tas bort fr�n listan. OBS i detta fall s� m�ste anv�ndaren kopiera
v�rdena om de ska finnas kvar efter att ha ta gits bort fr�n listan.
*/

/*
Syfte: Skapa en ny lista
Returv�rde: Den nyskapade listan (list*)
Kommentarer: D� man anv�nt listan f�rdigt s� m�ste minnet f�r listan
             avallokeras via funktionen list_free
*/
list *list_empty(void){
    list *l=malloc(sizeof(list));
    l->freeFunc=NULL;
    l->min=0;
    l->max=2;
    l->faltet=array_create(1,l->min, l->max);
    l->last_pos=-1;

    return l;
}

/*
Syfte: Installera en minneshanterare f�r listan s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i listan mer.
Parametrar: l - listan
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i listan).
Kommentarer: Bara minne f�r v�rden som finns i listan vid tidpunkten d� en
             minneshanterare satts eller senare kommer tas bort.
             Listan funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i listan.
*/
void list_setMemHandler(list *l, memFreeFunc *f) {
   l->freeFunc=f;
}

/*
Syfte: S�tter in ett v�rde p� en viss position i listan.
Parametrar: l (list *) listan som vi ska s�tta in i
            dp (data) v�rdet som ska s�ttas in
            p (position) positionen p� vilken ins�ttningen ska g�ras
Returv�rde: Positionen f�r det nyinstoppade v�rdet.
Kommentarer: Vid felaktig position kommer programmet avslutas.
*/
list_position list_insert(list *l, data dp, list_position p){
    if(p>l->last_pos+1 || p<l->min) {
        fprintf(stderr,"List insert: Illegal position\n");
        exit(1);
    }

    array *arr;

    //Ut�kar f�ltet om det �r f�r litet
    if(l->max==l->last_pos){
        arr=array_create(1,l->min, l->max*2);
        for(int i=l->min; i<=l->max+1; i++) {
            if (i<p){
                array_setValue(arr, array_inspectValue(l->faltet, i),i);
            }
            else if(i==p){
                array_setValue(arr, dp , i);
            }
            else if(i>p){
                array_setValue(arr, array_inspectValue(l->faltet,i-1) , i);
            }
        }
        l->max=2*l->max;
        array_free(l->faltet);
        l->faltet=arr;
    }
    else {
         array_setMemHandler(l->faltet,NULL);
         for(int i=l->last_pos; i>=p; i--) {
            array_setValue(l->faltet, array_inspectValue(l->faltet,i) ,i+1);
         }  
         array_setValue(l->faltet,dp,p);
    }
 

    l->last_pos++;

    return p;
}

/*
Syfte: Kontrollera om listan �r tom
Parametrar: l (list *) listan som ska kontrolleras.
Returv�rde: true om listan �r tom annars false
Kommentarer:
*/
bool list_isEmpty(list *l){
    return (l->last_pos==-1);
}

/*
Syfte: H�mta ett v�rde p� en given plats i listan.
Parametrar: l (list *) listan som v�rdet ska h�mtas fr�n
            p (list_position) positionen f�r v�rdet
Returv�rde: V�rdet p� positionen p (data)
Kommentarer: funktionen odefinierad f�r positioner utanf�r intervalet
             list_first <= pos < list_end
*/
data list_inspect(list *l,list_position p){
    return array_inspectValue(l->faltet,p);
}

/*
Syfte: Ta fram den f�rsta positionen i listan
Parametrar: l (list *) listan
Returv�rde: den f�rsta positionen i listan
Kommentarer:
*/
list_position list_first(list *l){
    return l->min;
}

/*
Syfte: Ta fram positionen efter det sista v�rdet i listan
Parametrar: l (list *) listan
Returv�rde: Positionen efter det sista v�rdet i listan
Kommentarer: OBS inspect p� denna position �r odefinierad
*/
list_position list_end(list *l){
    return l->last_pos+1;
}

/*
Syfte: Ta fram positionen efter den givna i listan
Parametrar: l (list *) listan
            p (list_position) positionen vars efterf�ljare man vill ta fram
Returv�rde: Den efterf�ljande positionen
Kommentarer: Odefinierad f�r end
*/
list_position list_next(list *l,list_position p){
    return p+1;
}

/*
Syfte: Ta fram positionen innan den givna i listan
Parametrar: l (list *) listan
            p (list_position) positionen vars f�reg�ngare man vill ta fram
Returv�rde: Positionen innan den givna
Kommentarer: Odefinierad f�r first
*/
list_position list_previous(list *l,list_position p){
    return p-1;
}

/*
Syfte: Tar bort ett v�rde ur listan
Parametrar: l (list *) listan.
            p (list_position) positionen f�r v�rdet som ska tas bort.
Returv�rde: positionen som svarar mot den d�r v�rdet togs bort efter borttagandet
Kommentarer: Om en funktion f�r att avallokera minnet f�r datav�rdena
             via list_setMemFunc s� kommer minnet f�r datat att avallokeras,
             annars �r detta anv�ndarens ansvar.
             p:s v�rde �r odefinierat efter anropet.
*/
list_position list_remove(list *l,list_position p){
    if(l->freeFunc!=NULL)
        l->freeFunc(array_inspectValue(l->faltet,p));
    for(int i=p; i<l->last_pos; i++){
        array_setValue(l->faltet, array_inspectValue(l->faltet,i+1) , i);
    }

    l->last_pos--;
    return p;
}

/*
Syfte: Avallokera minne som anv�nds av listan.
Parametrar: listan (list *)
Kommentarer: Minne f�r ev v�rden i listan avallokeras bara om en funktion
             f�r detta �r satt via list_setMemFunc. Annars �r det anv�ndarens
             uppgift att avallokera minnet f�r alla v�rden i listan.
*/
void list_free(list *l){
    array_setMemHandler(l->faltet,l->freeFunc);
    array_free(l->faltet);
    free(l);
}
