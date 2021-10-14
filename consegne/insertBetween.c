#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node Node;
typedef struct list List;

struct node {
    void *data;
    Node *next;
};

struct list {
    Node *head;
    Node *tail;
};

Node    *createNode(void *data);
List    *createList(void *head_data, void *tail_data);
    
void    insertHead(List *self, void *data);
void    insertTail(List *self, void *data);
void    insertBeetween(List *self, const char *previus, const char *successive, void *data);

int     *createInt(const int data);
double  *createDouble(const double data);
char    *createChar(const char data);
char    *createString(const char *string);

void printInt(const void *data);
void printDouble(const void *data);
void printChar(const void *data);
void printString(const void *data);
void printList(List *list, void (*print)(const void *data));


int main()
{
    List *list = createList
    (
        createString("Hello"), 
        createString("World")
    );
    
    insertBeetween(list, "Hello", "World", "Wonderful");
    printList(list, printString);

    puts("");

    List *list2 = createList
    (
        createInt(10),
        createInt(20)
    );

    insertTail(list2, createInt(30));
    printList(list2, printInt);
    
    List *list3 = createList
    (
        createList
        (
            createInt(0),
            createInt(5)
        ),

        createList
        (
            createInt(6),
            createInt(10)
        )
    );

    return 0;
}


Node *createNode(void *data)
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

List *createList(void *head_data, void *tail_data)
{
    List *_list = malloc(sizeof *_list);
    if (_list == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di una Lista\n");
        return NULL;
    }

    _list->head = head_data ? createNode(head_data) : NULL;
    _list->tail = tail_data ? createNode(tail_data) : NULL;

    if (_list->head != NULL && _list->tail != NULL) { _list->head->next = _list->tail; }
    
    return _list;
}

void insertHead(List *self, void *data)
{
    Node *_head = createNode(data);
    if (_head == NULL) {
        fprintf(stderr, "Errore di inserimento in Testa alla Lista\n");
        return;
    }

    _head->data = data;
    _head->next = self->head;

    self->head = _head;
}

void insertTail(List *self, void *data)
{
    self->tail->next = createNode(data);
    if (self->tail->next == NULL) {
        fprintf(stderr, "Errore di inserimento in Coda alla Lista\n");
        return;
    }

    self->tail = self->tail->next;
}

void insertBeetween(List *self, const char *previus, const char *successive, void *data)
{
    Node *current = self->head;
    while (
        current->next && 
        strcmp((char *)current->data, previus) &&
        strcmp((char *)current->next->data, successive)
    ) { current = current->next; }

    if (current->next == NULL) { 
        fprintf(stderr, "Errore di inserimento: Nodo inesistente\n");
        return;
    }

    Node *middle = createNode(data);
    if (middle == NULL) { 
        fprintf(stderr, "Nodo non inserito\n");
        return;
    }

    middle->next = current->next;
    current->next = middle;
}

int     *createInt(const int data)
{
    int *_data = malloc(sizeof *_data);
    if (_data == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di un'Intero\n");
        return NULL;
    }

    *_data = data;
    return _data;
}

double  *createDouble(const double data)
{
    double *_data = malloc(sizeof *_data);
    if (_data == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di un Double\n");
        return NULL;
    }

    *_data = data;
    return _data;
}

char    *createChar(const char data)
{
    char *_data = malloc(sizeof *_data);
    if (_data == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di un Carattere\n");
        return NULL;
    }

    *_data = data;
    return _data;
}

char    *createString(const char *string)
{
    char *_string = calloc(strlen(string), sizeof(char));
    if (_string == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di una Stringa\n");
        return NULL;
    }

    strcpy(_string, string);
    return _string;
}

void printInt(const void *data) { fprintf(stdout, "%i", *(int *)data); }
void printDouble(const void *data) { fprintf(stdout, "%lf", *(double *)data); }
void printChar(const void *data) { fprintf(stdout, "%c", *(char *)data); }
void printString(const void *data) { fputs((char *)data, stdout); }

void printList(List *list, void (*print)(const void *data))
{
    Node *current = list->head->next;

    print(list->head->data);
    while (current != NULL) { fprintf(stdout, " "); print(current->data); current = current->next; }
}