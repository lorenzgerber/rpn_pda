/*
 * Copyright 2012 Johan Eliasson (johane@cs.umu.se). Till�telse ges f�r anv�ndning p� kurserna 
 * i Datastrukturer och algoritmer vid Ume� Universitet. All annan anv�ndning kr�ver f�rfattarens
 * tillst�nd.
 */

#include "array.h"

/*
Datatypen Array som s� l�ngt som m�jligt f�ljer definitionen p� sidan
91 i Lars-Erik Janlert, Torbj�rn Wiberg Datatyper och algoritmer 2.,
[rev.] uppl.,Lund, Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

F�lt av godtycklig dimension och storlek kan skapas.
Datav�rden lagras i form av void pekare.
*/

/*
Syfte: Skapa en ny array (F�lt)
Parametrar: numDimensions - int som anger antalet dimensioner p� arrayen.
            low - en int per dimension. Anger l�gsta m�jliga index f�r den dimensionen
            high - en int per dimension. Anger h�gsta m�jliga index f�r den dimensionen
            Ex f�r 3-Dimensionell:
            array *arr=array_create(3,0,0,0,10,10,10);
Returv�rde: den nyskapade arrayen.
Kommentarer: Om low och high inneh�ller felaktigt antal v�rden eller low > high
             �r beteendet ospecificerat
*/
array *array_create(int numDimensions, ... /*low followed by high*/) {
    va_list high_lo;
    int arraySize=1;
    va_start(high_lo,numDimensions);
    array *arr=calloc(1,sizeof(array));
    arr->low=malloc(numDimensions*sizeof(int));
    arr->high=malloc(numDimensions*sizeof(int));
    arr->numDimensions=numDimensions;

    for(int i=0;i<numDimensions*2;i++) {
       int value=va_arg(high_lo,int);
       if(i<numDimensions) {
           arr->low[i]=value;
       }
       else {
           arr->high[i-numDimensions]=value;
           arraySize*=arr->high[i-numDimensions]-arr->low[i-numDimensions]+1;
       }
    }
    va_end(high_lo);
    arr->internal_array=calloc(arraySize,sizeof(void *));
    arr->arraySize=arraySize;
    return arr;
}

/*
Syfte: Installera en minneshanterare f�r arrayen (f�ltet) s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i f�ltet mer.
Parametrar: arr - arrayen
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i arrayen).
Kommentarer: B�r anropas direkt efter att arrayen skapats om funktionaliteten
             ska anv�ndas. Arrayen funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokra allt
             minne f�r datat som lagras i arrayen.
*/
void array_setMemHandler(array *arr, memFreeFunc *f) {
   arr->freeFunc=f;
}

/*
Endast hj�lpfunktion. Ej f�r publik anv�ndning
*/
int getInternalArrayIndex(array *arr,va_list index) {
    int internalIndex=0;
    int multiplier=1;
    for(int i=1;i<arr->numDimensions;i++) {
        multiplier*=(arr->high[i]-arr->low[i]+1);
    }
    for(int i=0;i<arr->numDimensions-1;i++) {
       internalIndex+=(va_arg(index,int)-arr->low[i])*multiplier;
       multiplier/=(arr->high[i+1]-arr->low[i+1]+1);
    }
    internalIndex+=(va_arg(index,int)-arr->low[arr->numDimensions-1]);
    return internalIndex;  
}

/*
Syfte: S�tta in ett v�rde p� en viss plats i arrayen.
Parametrar: arr - arrayen
            value - v�rdet som ska s�ttas in.
            index - index f�r arrayen. en int per dimension. low<= index <=high
Kommentarer: Beteendet �r ej specificerat f�r ogiltiga index.
*/
void array_setValue(array *arr,data value, .../*index*/) {
    va_list index;
    va_start(index, value);
    int internalIndex=getInternalArrayIndex(arr,index);
    va_end(index);
    if(arr->freeFunc!=NULL && arr->internal_array[internalIndex] != NULL)
        arr->freeFunc(arr->internal_array[internalIndex]);
    arr->internal_array[internalIndex]=value;
}

/*
Syfte: H�mta ett givet v�rde fr�n arrayen
Parametrar: arr - arrayen
            index - index f�r arrayen. en int per dimension. low<= index <=high
Returv�rde: Det efterfr�gade v�rdet.
Kommentarer: Beteendet �r ej specificerat f�r ogiltiga index
             och om hasValue(index) �r false
*/
data array_inspectValue(array *arr,... /*index*/) {
    va_list index;
    va_start(index, arr);
    int internalIndex=getInternalArrayIndex(arr,index);
    va_end(index);
    return arr->internal_array[internalIndex];
}

/*
Syfte: Kolla om ett v�rde satts f�r ett givet index i arrayen.
Parametrar: arr - arrayen
            index - index f�r arrayen. en int per dimension. low<= index <=high
Returv�rde: bool som indikerar om ett v�rde har satts f�r index i arrayen.
Kommentarer: Beteendet �r ej specificerat f�r ogiltiga index.
*/
bool array_hasValue(array *arr,... /*index*/) {
    va_list index;
    va_start(index, arr);
    int internalIndex=getInternalArrayIndex(arr,index);
    va_end(index);
    return arr->internal_array[internalIndex]!=NULL;
}

/*
Syfte: H�mta de h�gsta m�jliga index som �r giltiga f�r arrayen.
Parametrar: arr - arrayen.
Returv�rde: Endimensionell array med ett v�rde per dimension i arrayen som man
            vill kontrolera de giltiga indexen f�r. Arrayen inneh�ller int-pekare.
            low f�r den returnerade arrayen �r 0 och high antalet dimensioner-1.
Kommentarer: Anv�ndaren av funktionen �r ansvarig f�r att avallokera minnet
             f�r den returnerade arrayen.
             Minne f�r v�rdena i den returnerade arrayen f�r ej avallokeras.
             Datav�rdena i den returnerade arrayen �r endast tillg�ngliga s�
             l�nge som man ej avallokerat minnet f�r den ursprungliga arrayen.
*/
array * array_high(array * arr) {
    array *highIndex=array_create(1,0,arr->numDimensions-1);
    for(int i=0;i<arr->numDimensions;i++) {
        array_setValue(highIndex,&(arr->high[i]),i);
    }
    return highIndex;
}

/*
Syfte: H�mta de l�gsta m�jliga index som �r giltiga f�r arrayen.
Parametrar: arr - arrayen.
Returv�rde: Endimensionell array med ett v�rde per dimension i arrayen som man
            vill kontrolera de giltiga indexen f�r. Arrayen inneh�ller int-pekare.
            low f�r den returnerade arrayen �r 0 och high antalet dimensioner-1.
Kommentarer: Anv�ndaren av funktionen �r ansvarig f�r att avallokera minnet
             f�r den returnerade arrayen.
             Minne f�r v�rdena i den returnerade arrayen f�r ej avallokeras.
             Datav�rdena i den returnerade arrayen �r endast tillg�ngliga s�
             l�nge som man ej avallokerat minnet f�r den ursprungliga arrayen.
*/
array * array_low(array * arr) {
    array *lowIndex=array_create(1,0,arr->numDimensions-1);
    for(int i=0;i<arr->numDimensions;i++) {
        array_setValue(lowIndex,&(arr->low[i]),i);
    }
    return lowIndex;
}

/*
Syfte: Avallokerar allt minne som anv�nds av arrayen.
Parametrar: arr - Arrayen vars minne ska avallokeras.
Kommentarer: Efter anropet �r det ej m�jligt att anv�nda arrayen.
             Minne f�r datat i arrayen m�ste innan anropet avallokeras av anv�ndaren av datatypen
             f�r att f�rhindra minnesl�ckor om minne allokerats dynamiskt f�r dessa.
*/
void array_free(array * arr) {

    if(arr->freeFunc!=NULL) {
        for(int i=0;i<arr->arraySize;i++) {
            if(arr->internal_array[i]!=NULL) {
                arr->freeFunc(arr->internal_array[i]);
            }
        }
    }
    free(arr->internal_array);
    free(arr->high);
    free(arr->low);
    free(arr);
}
