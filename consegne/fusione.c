#include <stdio.h>
#include <time.h>
#include "liblinked_list/lib/data.h"
#include "liblinked_list/lib/list.h"
#include "liblinked_list/lib/list_util.h"

/* 
* ૮(-.-)ა Libreria completa: 
* https://github.com/repo-scolastica/programazione/tree/main/singly_linked_list/lib 
* ૮(-.-)ა 
*/

int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));
    List *list1 = createList(NULL, NULL);
    List *list2 = createList(NULL, NULL);
    List *list3 = createList(NULL, NULL);

    for (int i = 0; i < 20; ++i) {
        insertTail(list1, newInt(rand() % 100 + 1));
        insertTail(list2, newInt(rand() % 100 + 1));
    }

    deleteNode(removeHead(list1)); // Iniziallizzo una lista con due nodi NULLI, li vado a scartare
    deleteNode(removeHead(list1)); // Iniziallizzo una lista con due nodi NULLI, li vado a scartare
    deleteNode(removeHead(list2)); // Iniziallizzo una lista con due nodi NULLI, li vado a scartare
    deleteNode(removeHead(list2)); // Iniziallizzo una lista con due nodi NULLI, li vado a scartare

    fprintf(stdout, "\nPrima lista: ");
    printList(list1, printInt);

    fprintf(stdout, "\n\nSeconda lista: ");
    printList(list2, printInt);


    // Inserimento nella terza lista dei Nodi della prima 
    Node *current = list1->head;
    while (current) { 
        insertTail(list3, current->data); 
        current = current->next;
    }

    // Inserimento nella terza lista dei Nodi della seconda
    current = list2->head;
    while (current) { 
        insertTail(list3, current->data); 
        current = current->next;
    }

    deleteNode(removeHead(list3)); // Iniziallizzo una lista con due nodi NULLI, li vado a scartare
    deleteNode(removeHead(list3)); // Iniziallizzo una lista con due nodi NULLI, li vado a scartare

    fprintf(stdout, "\n\nTerza lista Ordinata: ");
    printList(list3, printInt);
    
    // Ordinamento
    sort(list3, compareInt);
    fprintf(stdout, "\n\nTerza lista Ordinata: ");
    printList(list3, printInt);

    return 0;
}
