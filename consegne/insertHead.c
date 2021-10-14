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

Node *createNode(void *data);
List *createList(void *head_data, void *tail_data);

void insertHead(List *self, void *data);
void insertTail(List *self, void *data);

char *createString(const char *string);

void printString(const void *data);
void printList(List *list, void (*print)(const void *data));

int main()
{
    List *list = createList(createString("Hello"), createString("World"));
    printList(list, printString);

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

    if (_list->head != NULL || _list->tail != NULL) { _list->head->next = _list->tail; }

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

char *createString(const char *string)
{
    char *_string = calloc(strlen(string), sizeof(char));
    if (_string == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria di una Stringa\n");
        return NULL;
    }

    strcpy(_string, string);
    return _string;
}

void printString(const void *data) { fputs((char *)data, stdout); }
void printList(List *list, void (*print)(const void *data))
{
    Node *current = list->head;
    while (current != NULL) {
        print(current->data); fprintf(stdout, " ");
        current = current->next;
    }
}