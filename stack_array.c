//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Umeå University.
//Usage exept those listed above requires permission by the author.

/*
Datatypen Stack enligt definitionen på sidan 134 i Lars-Erik Janlert,
Torbjörn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Denna stack är implementerad med hjälp av en Array

Som standard så är användaren av datatypen ansvarig för att avallokera
minnet för datavärdena. Genom att anropa stack_setMemHandler och till denna
skicka med en funktion för att avallokera ett dataobjekt så kommer stacken
ta över ansvaret för minneshanteringen och automatiskt avallokera värdena
då de tas bort från stacken. OBS i detta fall så måste användaren kopiera
värdena om de ska finnas kvar efter att ha tagits bort från stacken.
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack_array.h"

/*
Syfte: Skapa en ny stack 
Returvärde: Den nyskapade stacken (stack*)
Kommentarer: Då man använt stacken färdigt så måste minnet för stacken
             avallokeras via funktionen stack_free
*/
stack *stack_empty(void) { 
   stack *s=malloc(sizeof(stack));
   s->internal_array=array_create(1,0,1000);
   s->top = -1; 
   s->maxSize=1000;
   s->freeFunc=NULL;
   return s;
}

/*
Syfte: Installera en minneshanterare för stacken så att den kan ta över
       ansvaret för att avallokera minnet för värdena då de ej finns kvar
       i stacken mer.
Parametrar: s - stacken (stack *)
            f - en funktionspekare till en funktion som tar in ett värde
                av typen data (void pekare) och avallokerar minnet för värdet
                den pekar på (ett av den typ av värden som lagras i stacken).
Kommentarer: Bör anropas direkt efter att stacken skapats om funktionaliteten
             ska användas. Stacken funkar även om denna funktion inte anropas,
             men det är då upp till användaren av datatypen att avallokera allt
             minne för datat som lagras i stacken.
*/
void stack_setMemHandler(stack *s, memFreeFunc *f) {
    s->freeFunc=f;
}

/*
Syfte: Kontrollera om stacken är tom
Parametrar: s (stack *) stack som ska kontrolleras.
Returvärde: true om stacken är tom annars false
Kommentarer:
*/
bool stack_isEmpty(stack *s) { 
   return s->top==-1; 
} 


/*
Syfte: Tar bort översta värdet på stacken.
Parametrar: s (stack *) stacken vars översta värde ska tas bort.
Kommentarer: Ej definierad för en tom stack.
*/
void stack_pop(stack *s) { 
   if (stack_isEmpty(s)) {
      fprintf(stderr,"pop on empty stack"); 
      exit(1);
   }
   else {
      if(s->freeFunc!=NULL)
          s->freeFunc(array_inspectValue(s->internal_array,s->top));
      array_setValue(s->internal_array,NULL,s->top);
      s->top--;
   }
}

/*
Syfte: Hämta värdet överst på stacken
Parametrar: l (stack *) vars översta värde man vill hämta.
Returvärde: Översta värdet på stacken (data)
Kommentarer: Ej definierad för en tom stack
*/
data stack_top(stack *s) {
   return array_inspectValue(s->internal_array,s->top);
}

/*
Syfte: Lägger till ett värde översta på stacken.
Parametrar: l (stack *) stacken.
Kommentarer: Om den underliggande arrayen skulle bli full kommer en ny
             dubbelt så stor skapas och värdena flyttas över till denna.
*/
void stack_push(stack *s, data value) { 
   if(++s->top >= s->maxSize) {
       array *arr=array_create(1,0, s->maxSize*2);
       for(int i=0; i<=s->maxSize; i++) {
           array_setValue(arr, array_inspectValue(s->internal_array, i),i);
       }
       array_setValue(arr, value , s->top);
       s->maxSize=2*s->maxSize;
       array_free(s->internal_array);
       s->internal_array=arr;
   }
   array_setValue(s->internal_array,value,s->top); 
}

/*
Syfte: Avallokera minne som används av stacken.
Parametrar: s stacken (stack *)
Kommentarer: Minne för ev värden i stacken avallokeras bara om en funktion
             för detta är satt via stack_setMemHandler. Annars är det användarens
             uppgift att avallokera minnet för alla värden i stacken.
*/
void stack_free(stack *s) {
    array_setMemHandler(s->internal_array,s->freeFunc);
    array_free(s->internal_array);
    free(s);
}


