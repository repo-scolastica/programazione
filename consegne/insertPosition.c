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

Node *removeNode(List *self, Node *node);

Node *findMin(List *self, int (*compare)(const void *a, const void *b));

int     *createInt(const int data);
double  *createDouble(const double data);
char    *createChar(const char data);
char    *createString(const char *string);

int compareInt(const void *a, const void *b);
int compareString(const void *a, const void *b);

void printInt(const void *data);
void printDouble(const void *data);
void printChar(const void *data);
void printString(const void *data);
void printList(List *list, void (*print)(const void *data));

void freeNode(Node *node);

int main()
{
    List *list = createList
    (
        createInt(10),
        createInt(20)
    );

    insertTail(list, createInt(5));

    List *list_stringhe = createList
    (
        createString("Hello"),
        createString("World")
    );

    insertTail(list_stringhe, createString("Ciao"));
    printList(list_stringhe, printString);  puts("");

    freeNode(removeNode(list_stringhe, findMin(list_stringhe, compareString)));
    printList(list_stringhe, printString);  puts("");

    printList(list, printInt); puts("");
    freeNode(removeNode(list, findMin(list, compareInt)));
    printList(list, printInt);

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

Node *findMin(List *self, int (*compare)(const void *a, const void *b))
{
    Node *current = self->head->next;
    Node *min = self->head;

    while (current != NULL) {
        if (compare(current->data, min->data) < 0) { min = current; }
        current = current->next;
    }

    return min;
}

Node *removeNode(List *self, Node *node)
{
    Node *current = self->head;
    while(current->next != node) { current = current->next; }

    Node *toRemove = current->next;
    current->next = toRemove->next;
    
    return toRemove;
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

int compareInt(const void *a, const void *b) { return *(int *)a - *(int *)b; }
int compareString(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
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

void freeNode(Node *node)
{
    free(node->data);
    free(node);
}