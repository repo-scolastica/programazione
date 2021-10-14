# Sort.c

## Implementazione in linguaggio C dell'ordinamento di un'array di qualsiasi tipo di dato


### Prototipo:

```c   
// Prototipo della funzione
void bubble_sort (   
    void    *base, 
    int     nmem,
    int     memsize, 
    int     (*compare)(const void *, const void *)
);
```

#### Parametri:
-  Puntatore all'indirizzo di accesso dell'array `void *base`.
-  Numeri di elementi dell'array `int nmem`.
-  Quantità di memoria che ogni singolo elemento occupa: `int memsize`
-  Tipo di confronto da effettuare `int (*compare)(const void *, const void)`
----------------------------------------------------------------

### I concetti:
Per riuscire nell'implementazione della procedura bisogna prima individuare le parti che la costituiscono ed il loro relativo funzionamento:

#### Array:
*Blocco contiguo di memoria*, struttura dati lineare ove ogni elemento appartiene allo stesso tipo di dato.

> **Rappresentazione astratta:**
> [ ] [ ] [ ] [ ] [ ] < Ultimo elemento dell'array ("Cella di memoria")
>  ^
> Indirizzo di accesso dell'array

**Implementazione in C:**
Si assume l'implementazione in una macchina a 64bit
```c
int array[10];
```

Il linguaggio si occupa automaticamente della gestione della memoria e  interpreta gli indirizzi di accesso dei singoli elementi mediante le keyword inserite:

**`int`** Specifica lo spazio occupato in memoria dalla variabile
**`[10]`** Specifica il il numero di elementi da allocare in memoria

Dunque _dietro le quinte_ si ha:
```c
int array[10] 
      |
      |
      V
array = alloca_memoria_nello_stack(sizeof(int) * 10);
```
ignoriamo _alloca_memoria_nello_stack_ "ditro le quinte viene allocata la memoria per la variabile". Ci ritroviamo dunque con la variabile `array` che contiene l'indirizzo di accesso di un blocco contiguo di memoria nello stack pari a 40B (10 * sizeof(int)).

> Sia `memsize` lo spazio di memoria occupato da un singolo elemento. 

> Si osserva che il nome array indica l'indirizzo di accesso dell'array ovvero l'indirizzo di accesso del primo elemento

L'accesso ai singoli elementi consentito tramite la sintassi viene riportato sotto. Si nota che  memsize viene definito dal tipo di dato dell'array:

- `char` = 1B;
- `short` = 2B
- `int` = 4B
- `double` = 8B
- `...`

```c
array[0] = array + 0 * memsize; 
array[1] = array + 1 * memsize;
array[2] = array + 2 * memsize;
```

**Supponendo** che l'**indirizzo di accesso** dell'array sia **0x000** si ha:
```c
int array[10];
array[0] = array + 0 * sizeof(int) = 0x000 + 0 * 4 = 0x000
array[1] = array + 1 * sizeof(int) = 0x000 + 1 * 4 = 0x004
array[2] = array + 2 * sizeof(int) = 0x000 + 2 * 4 = 0x008
...

// 0x000 -> Indirizzo di accesso del primo elemento
// 0x004 -> Indirizzo di accesso del secondo elemento
// 0x008 -> Indirizzo di accesso del terzo elemento
// ...
```
----------------------------------------------------------------
**Array = Indirizzo di memoria:**
```c
int array[10];
int *ptr = array;

printf("%p, array); // Output 0x000
printf("%p, ptr); // Output 0x000
```

Si osserva che il nome dell'array **`array`** (la variabile) è un **puntatore** di tipo **int**

> Il tipo di dato dei puntatori è cruciale per la gestione implicita dell'**aritmetica dei puntatori**

```c
int *ptr = array; // 0x000

array + 1 -> 0x004
array + 2 -> 0x008
...
```


Implicitamente avviene:
```c
array + 1 = (array + 1 *sizeof(int)); 
array + 2 = (array + 2 *sizeof(int)); 
```

----------------------------------------------------------------

#### **`void *`**
Il puntatore di tipo void definisce una variabile contenente un'indirizzo di memoria senza specificarne la quantità di spazio occupante.

Esso semplifica l'aritmetica dei puntatori:
```c
void *ptr = &var;   // 0x000
ptr += 5;           // 0x005
```

consentendo di manipolare con maggiore facilità gli indirizzi di memoria.

----------------------------------------------------------------

#### Funzione di confronto:
Lo standard per il confrondo delle variabile prevede la restituzione di un valore che identifichi il risultato del confronto:

```confronta(a, b)```:
se `a > b` allora a - b > 0 
se `a < b` allora a - b < 0
se `a == b` allora a - b = 0

Dunque a seconda del valore di a - b si identifica risultato

------------------------------------------------------------------------------------------------

La funzione di confronto mediante cui si identificano le variabile da scambiare dipende dal tipo di dato delle variabili di confronto.

```c
char char_1, char_2;
short short_1, short_2;
int int_1, int_2;
double double_1, double_2;
struct foo foo_1, foo_2;
```

Il confronto varia a seconda del tipo di dato;
Ad esempio per due variabili di tipo `int` il confronto sarà:
```c
int comapre_int(const void *a, const void *b)
{
    return *(int *)a - *(int *) b;
}
```

mentre il confronto per due variabile di un'altro tipo di dato risulta:
```c
int comapre_char(const void *a, const void *b)
{
    return *(char *)a - *(char *) b;
}

int comapre_double(const void *a, const void *b)
{
    return *(double *)a - *(double *) b;
}

...
```
Non potendo dunque generalizzare una funzione di confronto, lo si definisce come argomento della funzione di ordinamento affinché il programmatore possa decidere il confronto in base al tipo di dato impiegato.

Nel caso di un'array di `int` la chiamata della procedura risulta:
```c
int array[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
bubble_sort(array, 10, sizeof(int), compare_int);
```

Nel caso di un'array di `double` la chiamata della procedura risulta:
```c
double array[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
bubble_sort(array, 10, sizeof(doublee), compare_double);
```

procedento nel modo sopra elencato per i vari tipi di dato.

--------------------------------------------------------------------------------
### Scambio di variabili
Il metodo migliore per scambiare due variabili consiste nella generalizzazione dello scambio:

Supponiamo di voler scambiare due `int`, il codice risulta:
```c
void swap(void *n, void *m) {
    int temp = *(int *)n;
    *(int *)n = *(int *)m;
    *(int *)m =  temp;
}
```

Supponiamo di voler scambiare due `struct`, il codice risulta:
```c
struct punto {
    int x;
    int y;
};
```
```c
void swap(void *n, void *m) {
    int temp = (struct punto *)n->x;
    (struct punto *)n->x = (struct punto *)m->x
    (struct punto *)m->x = temp;

    int temp = (struct punto *)n->y;
    (struct punto *)n->y = (struct punto *)m->y
    (struct punto *)m->y = temp;
}
```

--------------------------------------------------------------------------------

**Il metodo consiste nell'andare a scambiare ogni singolo byte delle due variabile sino a rangiungere l'ultimo:**
```c
void    swap(void *n, void *m, int memsize)
{
    char *byte_ptr_n = (char *)n;
    char *byte_ptr_m = (char *)m;
    char *temp = NULL;

    for (int i = 0; i < memsize; ++i, ++byte_ptr_n, ++byte_ptr_m) {
        *temp = *byte_ptr_n;
        *byte_ptr_n = *byte_ptr_m;
        *byte_ptr_m = *temp;
    }
}
```

-----------------------------------------------------------------------------------------------

## Implementazione

Compreso il funzionamento dei puntatori ed identificato il metodo per effetturare il controllo dei vari elementi dell'array, occorre implemenate il codice andando a sfruttare l'aritmetica dei puntatori:

### Procedure generale
```c
void    bubble_sort
(
    void    *base, 
    int     nmem,
    int     memsize, 
    int     (*compare)(const void *, const void *)
) {
    int     not_ordered =   1;

    void    *prev =        NULL;
    void    *succ =        NULL;

    for (int i = 0; i < nmem && not_ordered; ++i) {     
        not_ordered = 0;
        for (int j = 1; j < nmem; ++j) {     
            prev = base + (j - 1) * memsize;
            succ = base + j * memsize;
            if (compare(prev, succ) > 0 ) { 
                swap(prev, succ, memsize);
                not_ordered = 1; 
            }
        }
    }
}
```

Andiamo a comprendere pezzo per pezzo la struttura della procedura:

------------------------------------------------------------------------------------------------
**Bubble Sort**
L'algoritmo di bubble sort per un generico array :
```c
int     not_ordered = 1; // flag per informare dello stato "disordinato dell'array"

for (int i = 0; i < nmem && not_ordered; ++i) {     
    not_ordered = 0;
    for (int j = 1; j < nmem; ++j) {     
        if (compare(array[j - 1], array[j]) > 0 ) { 
            swap(array[j - 1], array[j]);
            not_ordered = 1; 
        }
    }
}
```
[Buble Sort](https://it.wikipedia.org/wiki/Bubble_sort)

--------------------------------------------------------------------------------
Facendo riferimento all'[implementazione generale](#procedure-generale)

**`prev`**, **`succ`** 
Inizialmente alla riga 10 e 11 inzializzo due puntatori (`void *`) a `NULL`

Lo scopo di queste due puntatore è quello di indicare l'indirizzo di memoria ove contenute le variabili di confronto.
_ovvero_:
**10. `prev` = `base[j - 1]`**
**10. `succ` = `base[j]`**

Ciò si consegue mediantel'implementazione dell'aritmetica dei puntatori; si ossevino le righe 16 e 17:

**16. `prev = base + (j - 1) * memsize;`**
**17. `succ = base + j * memsize;`**

`(j - 1) * memsize` e `j * memsize` indicano l'offset ove sono localizzate nella memoria gli indirizzi di accesso delle variabili da confrontare: `memsize` indica la dimensione del tipo di dato, necessaria per le operazioni tra puntatori in modo **esplicito**

Questo argomento viene trattato nei [Concetti, Array](#array)

----------------------------------------------------------------------

