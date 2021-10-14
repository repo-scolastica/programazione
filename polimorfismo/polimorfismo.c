#include <string.h>
#include <stdlib.h>
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

    void (*print)(void *data);
};

//Genera variabili:
Node *createNode(void *data);
List *createList(void *head_data, void *tail_data, void (*print)(void *data));

int *newInt(int data);
float *newFloat(float data);
char *newString(const char *string);

// Operazioni Lista
void insertHead(List *self, void *data);
void insertTail(List *self, void *data);

// I/O
void printInt(void *data);
void printFloat(void *data);
void printString(void *data);
void printLinkedList(void *data);

void printList(List *self);

int main(int argc, char **argv)
{

    List *list = createList
    (
        createList(newInt(1), newInt(2), printInt), 
        createList(newFloat(4.5), newFloat(5.5), printFloat),
        printLinkedList
    );
    
    insertTail(list, createList(newString("Hello"), newString("World"), printString));

    // Il codice soptra riportato equivale:
    /* 
    List *list_i = createList(newInt(1), newInt(2), printInt);
    insertTail(list_i, newInt(3));

    fprintf(stdout, "Lista di interi: "); 
    printList(list_i);  puts("");

    // Lista di reali
    List *list_f = createList(newFloat(4.5), newFloat(5.5), printFloat);
    insertTail(list_f, newFloat(6.5));

    fprintf(stdout, "\nLista di reali: "); 
    printList(list_f); puts("");

    // Lista di stringhe
    List *list_s = createList(newString("Hello"), newString("World"), printString);

    fprintf(stdout, "\nLista di stringhe: "); 
    printList(list_s); puts("");

    // Lista di liste
    List *list = createList
    (
        list_i,
        list_f,
        printLinkedList
    );

    insertTail(list, list_s);
    */

    fprintf(stdout, "\nLista di liste di diverso tipo:\n"); 
    printList(list); puts("");

    return 0;
}

Node *createNode(void *data)
{
    Node *_node = malloc(sizeof(Node));
    if (_node == NULL) { 
        fprintf(stderr, "Errore di allocazione della memoria di un Nodo\n");
        return NULL; 
    }

    _node->data = data;
    _node->next = NULL;

    return _node;
}

List *createList(void *head_data, void *tail_data, void (*print)(void *data))
{
    List *_list = malloc(sizeof(List));
    if (_list == NULL) { 
        fprintf(stderr, "Errore di allocazione della memoria di una Lista\n");
        return NULL;
    }

    _list->head = createNode(head_data);
    _list->tail = createNode(tail_data);
    _list->print = print;

    if (_list->head && _list->tail) { _list->head->next = _list->tail; }
    return _list;
}

void insertHead(List *self, void *data)
{
    Node *_head = createNode(data);
    if (_head == NULL) { return; }

    _head->next = self->head;
    self->head = _head;
}

void insertTail(List *self, void *data)
{
    self->tail->next = createNode(data); if (self->tail->next == NULL) { return; }
    self->tail = self->tail->next;
}

int *newInt(int data)
{
    int *_data = malloc(sizeof(int));
    if (_data == NULL) { return NULL; }

    *_data = data;
    return _data;
}

float *newFloat(float data)
{
    float *_data = malloc(sizeof(float));
    if (_data == NULL) { return NULL; }

    *_data = data;
    return _data;
}

char *newString(const char *string)
{
    char *_string = calloc(strlen(string), sizeof(char));
    if (_string == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di una Stringa\n");
        return NULL;
    }

    strcpy(_string, string);
    return _string;
}

void printInt(void *data) { printf("%d", *(int *)data); }
void printFloat(void *data) { printf("%f", *(float *)data); }
void printString(void *data) { fputs((char *)data, stdout); }

void printLinkedList(void *data)
{
    List *_list = (List *)data;
    printf("[");
    printList(data);
    printf("]");
}

void printList(List *self)
{
    Node *current = self->head->next;
    self->print(self->head->data);
    while (current != NULL) {
        fprintf(stdout, ", ");
        self->print(current->data); 
        current = current->next;
    }
}
