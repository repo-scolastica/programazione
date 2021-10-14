# Liste a collegamento singolo

### Concetti
> Nodo: entità contentente un'informazione e il collegamento al nodo che lo segue

> Lista: struttura dati (ADT) costituita da un susseguirsi di Nodi.

#### Nodo
```c
    - - - - - - - -
    | DATA | MEMR |
    - - - - - - - -
```

#### Lista
```c
    head(testa)                                tail(coda)
    - - - - - - - -      - - - - - - - -      - - - - - - - -
    | DATA | MEMR |----->| DATA | MEMR |----->| DATA | MEMR |
    - - - - - - - -      - - - - - - - -      - - - - - - - -
```


### Operazioni primitive:

### Inserimento:
- In testa
- In coda
- Con criterio

### Rimozione: 
- In testa
- In coda
- Con criterio

### Restituzione
- Testa
- Coda
- Per dipendenza

### Ricerca 
- Per valore
- Per posizione

### Output
- Per Nodo
- Per Lista

Le operazioni primitive sono una serie di istruzioni tramite le quali si opera e gestisce la struttura dati consentendo un'intervento "primitivo".

Mediante le primitive si realizzano istruzioni per la gestione della lista sempre più articolate

----------------------------------------------------------------

### Implementazione in linguaggio C
#### Nodo:
```c
typedef struct Node Node;
struct Node {
    void *data;
    Node *next;
};
```

**`void *data`**: Puntatore all'indirizzo di memoria di ove allocata l'informazione

**`Node *next`**: Puntatore all'indirizzo di memoria ove allocato il nodo successivo;

#### Lista:
```c
typedef struct List List;
struct List {
    Node *head
    Node *tail;
};
```

**`Node head`**: Testa della lista (Primo nodo)
**`Node tail`**: Coda della lista (Ultimo nodo)

----------------------------------------------------------------

**NOTA**
- la funzione malloc restituisce l'indirizzo ove allocata la quantità di memoria richiesta mediante un puntatore di senza tipo (`void *`);
- In caso l'allocazione di memoria fallisca, la funzione restituisce un valore nullo (`NULL`) e dunque non si può procedere con la manipolazione della ADT dato che si tenterebbe di accedere a indirizzi di memoria inesistenti.
In questo caso si informa della mancata allocazione di memoria e si annulla la creazione della variabile

- Alcune metodologie per gestire gli errori sono le comunicazioni via stream, le funzioni di uscita (exit, abort), assert e perror.

#### Creazione dei nodi
```c
Node    *createNode(void *data)
{
    Node *_node = malloc(sizeof *_node);
    if (_node == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di un Nodo\n");
        return NULL;
    }

    _node->data = data;
    _node->next = NULL;

    return _node;
}
```

#### Creazione delle liste
```c
List    *createList(void *head_data, void *tail_data)
{
    List *_list = malloc(sizeof *_list);
    if (_list == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di una Lista\n");
        return NULL;
    }

    _list->head = createNode(head_data);
    _list->tail = createNode(tail_data);

    if (_list->head != NULL && _list->tail != NULL) { _list->head->next = _list->tail; }
    
    return _list;
}
```

Risorse in merito:
- [What does 'stream' mean?](https://stackoverflow.com/questions/38652953/what-does-stream-mean-in-c)
- [`assert.h`](https://it.wikipedia.org/wiki/Assert.h)
- [Should we use exit](https://stackoverflow.com/questions/31501142/should-we-use-exit-in-c/31501322)
- [K & R : Malloc in "The C Programming Language](http://computer-programming-forum.com/47-c-language/a9c4a586c7dcd3fe.htm)

- [Allocazione dinamica della memoria](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [Do I cast the rusult of malloc?](https://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc)

### Primitive:
```c
//?     FUNZIONI DI INSERIMENTO MEDIANTE DATO
void    insertHead(List *self, void *data);
void    insertTail(List *self, void *data);

//?     FUNZIONI DI INSERIMENTO MEDIANTE NODO
void    insertHeadNode(List *self, Node *_node);
void    insertTailNode(List *self, Node *_node);
```

**FUNZIONI DI INSERIMENTO MEDIANTE DATO**
La procedura ha come argomenti l'indirizzo di accesso della lista (`List *self`) su cui si va ad operare e l'indirizzo di memroia dell'informazione (`void *data`) da inserire.

**FUNZIONI DI INSERIMENTO MEDIANTE NODO**
La procedura ha come argomenti l'indirizzo di accesso della lista (`List *self`) su cui si va ad operare e l'indirizzo di memroia del nodo (`Node *_node`) da inserire.

_Successivamente vengono evidenziate le casistiche di scelta di una rispetto l'altra._

----------------------------------------------------------------

```c
//?     FUNZIONI DI RIMOZIONE DEI NODI 
Node    *removeHead(List *self);
Node    *removeTail(List *self);
Node    *removeNode(List *self, Node *_node);
```

**FUNZIONI DI RIMOZIONE DEI NODI**:
La funzione ha come argomenti l'indirizzo di accesso della lista (`List *self`) su cui si va ad operare. La funzione _`Node    *removeNode(List *self, Node *_node)`_ ha come seconod parametro il nodo da rimuovere dalla lista  

_Successivamente viene illustrata la motivazione di quest'utlima funzione_

---------------------------------
```c
//?     FUNZIONI DI RESTITUZIONE
void    *getData(Node *self);

Node    *getHead(List *self);
Node    *getTail(List *self);
Node    *getNodeAt(List *self, int index);
Node    *getNodeBefore(List *self, Node *_node);
Node    *getNodeAfter(Node *self);
```

**FUNZIONI DI RESTITUZIONE**:
Funzione che restituiscono l'indirizzo di memoria ove allocata la variabile (Nodo o informazione) per consentirne l'uso.
La funzione ha come argomenti l'indirizzo di accesso della lista (`List *self`) su cui si va ad operare e, a seconda della tipologia di restituzione, un parametro che definisce le operazioni di "accesso" alle variabile.

----------------------------------------------------------------
```c
//?     FUNZIONI DI RICERCA
Node    *findValue(List *self, void *data, int (*compare)(const void *a, const void *b));
Node    *findMin(List *self, int (*compare)(const void *a, const void *b));
Node    *findMax(List *self, int (*compare)(const void *a, const void *b));
```

**FUNZIONI DI RICERCA**
Funzioni tramite cui si trovano determinati all'interno della lista.

La funzione restituisce l'indirizzo di accesso ove memorizzata la veriabile se trovata, `NULL` in caso contrario. Ha come argomenti lista (`List *self`) ove si ricerca il nodo ed il tipo di confronto da effetturare fra i vari dati della lista (`int (*compare)(const void *a, const void *b)`). Quest'ultima variabile è dovuta alla generalità della lista: accedendo all'informazione mediante un puntatore senza tipo (`void *`) consente la gestione della memoria a piacimento del programmatore. Il casting del puntatore ne definisce il tipo. 

_questa parte viene discussa nell'articolo: [variabili generalizzate e polimorfismo]()_

----------------------------------------------------------------

```c
//?     FUNZIONI DI OUTPUT
void    printNode(Node *node, void printData(const void *data));
void    printList(List *self, void printData(const void *data));
```
**FUNZIONI DI OUTPUT**
Funzioni per l'output delle variabili.

Le funzioni hanno come parametro il nodo (Node *node) o la lista(List *self) da mandare in Output e il tipo di stampa. La funzione di stampa si ricollega al discorso della generalità della lista:
_questa parte viene discussa nell'articolo: [variabili generalizzate e polimorfismo]()_

---------------------------------

### Implementazione delle primitive:
> prototipi delle primitive [list.h](lib/list.h)
> file sorgente: [list.c](lib/list.c)

---------------------------------

### Funzioni derivate dalle primitive:
Obbiettivo: Ordinare una lista di interi (ordine crescente).
La procedura viene implementata mediante l'uso delle primitive:

**Una prima immagine**
Data la lista `listaInteri = {9, 8, 7, 6, 5, 4, 3, 2, 1 }`, che viene graficamente rappresentata come

```c
-- - - - - - - -    -- - - - - - - - -   -- - - - - - - - -   -- - - - - - - - -  
 |  9  | 0x110 |----->|  8  | 0x120  |----->|  7  | 0x130 |----->|  6  | ... |  ...
-- - - - - - - -    -- - - - - - - - -   -- - - - - - - - -   -- - - - - - - - - 
0x100                  0x110                0x120                  0x130
```
l'ordinamento si consegue mediante le relative oprazioni **primitive**:
- Si utilizzano due liste: la lista da cui si estrapolano i nodi disordinati, la lista in cui si inseriscono i nodi nell'ordine definito.
- Si trovata il Nodo contentente il Dato avente valore minore mediante la funzione primitiva **`Node    *findMin(List *self, int (*compare)(const void *a, const void *b))`**
- Si rimuove il Nodo dalla lista mediante la funzione primitiva **`Node    *removeNode(List *self, Node *_node)`** e lo si memorizza in una variabile di appoggio **`min`**
  
- Si inserisce il nodo rimosso nella seconda lista come ultimo elemento mediante la funzione primitiva **`void    insertTailNode(List *self, Node *_node)`**

- Si procede fino a quando la lista iniziale presente Nodi (**`while(list->head != NULL)`**)

**Il prototipo della procedura idealizzata risulta**:
```c
void sort(List *self, int (*compare)(const void *a, const void *b))
```
ove compare definisce il confronto tra tipo di dato (_questa parte viene discussa nell'articolo: [variabili generalizzate e polimorfismo]()_) ed il corpo della procedura viene implementato:

**Sort**
```c
void sort(List *self, int (*compare)(const void *a, const void *b))
    Node *min = NULL;
    List *list = createList(NULL, NULL);

    while(self->head) {
        min = findMin(self, compare);
        min = min != self->head? removeNode(self, min) : removeHead(self); 
        insertTailNode(list, min);
    }

    free(removeHead(list)); // I primi due nodi della lista 
    free(removeHead(list)); // vengono inizializzati vuoti (senza dato)

    self->head = list->head;
    self->tail = list->tail;

    free(list);
}
```

### Implementazione delle funzioni derivate dalle primitive:
> prototipi delle funzioni [list_util.h](lib/list_util.h)
> file sorgente: [list_util.c](lib/list_util.c)

---------------------------------------------------------------------------

#### Risorse relative le implementazione delle varie funzioni non speigate:

- [GNULib](https://www.gnu.org/software/gnulib/MODULES.html)
- [`void *`#1](https://stackoverflow.com/questions/11626786/what-does-void-mean-and-how-to-use-it)
- [`void *`#2](https://stackoverflow.com/questions/692564/concept-of-void-pointer-in-c-programming)
- [Programmazione generalizzata](http://cs.boisestate.edu/~amit/teaching/253/handouts/07-c-generic-coding-handout.pdf)
- [Una lista generalizzata](https://stackoverflow.com/questions/21238185/generic-programming-in-c)
- [Implementazione di uno stack generale](https://www.lvguowei.me/post/generic-programming-in-c/)
- [`malloc` vs `calloc`](https://stackoverflow.com/questions/1538420/difference-between-malloc-and-calloc?rq=1)
