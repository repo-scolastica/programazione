#include <stdio.h>
#include "liblinked_list/lib/data.h" // <-- Creata da me (〜￣▽￣)〜
#include "liblinked_list/lib/list.h" // <-- Creata da me 〜(￣▽￣〜)
#include "liblinked_list/lib/list_util.h" // <-- Creata da me ヘ(￣ω￣ヘ)

/* 
* ૮(-.-)ა Libreria completa: 
* https://github.com/repo-scolastica/programazione/tree/main/singly_linked_list/lib 
* ૮(-.-)ა 
*/

void enqueue(List *_queue, void *data) { insertHead(_queue, data); }
Node *dequeue(List *_queue) { return removeTail(_queue); }

void printQueue(List *self, void printData(const void *data)) { printList(self, printData); }

int isServiced(List *self, int commandCount);

int main(int argc, char **argv)
{
    int comando = 1, n = 1, cnt = 0;
    List *coda = createList(NULL, NULL);
    removeHead(coda);
    removeHead(coda);

    Node *toDelete = NULL;

    while (comando != 0) {
        fprintf(stdout, "> ");
        scanf("%d", &comando);
        switch (comando) {
            case 1: 
                ++cnt;
                if (cnt == 3) 
                {
                    fprintf(stdout, "Serviamo il clienti:\n");
                    toDelete = dequeue(coda); 
                    printNode(toDelete, printInt); printf("\n");
                    deleteNode(toDelete);
                    cnt = 0;
                }
                 
                else 
                {
                    if (coda->head == NULL) { coda->head = createNode(newInt(n)); coda->tail = coda->head; }
                    else { enqueue(coda, newInt(n)); }
                    ++n;
                }
                

            break;

            case 2: 
                cnt = 0;
                fprintf(stdout, "Serviamo i clienti:\n");

                int i = 0;
                while (coda->head && i < 2) {
                    toDelete = dequeue(coda);
                    printNode(toDelete, printInt);
                    deleteNode(toDelete);
                }
            break;

            case 3: 
                cnt = 0;
                fprintf(stdout, "Serviamo i clienti:\n");
                printList(coda, printInt); printf("\n");
                while (coda->head) {    
                    toDelete = removeHead(coda);
                    deleteNode(toDelete);
                }
            break;

            case 4: 
                if(coda->head) { printList(coda, printInt); } 
                else { printf("Lista vuota"); }
                break; 
        }
    }

    return 0;
}