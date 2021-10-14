#include <stdio.h>
#include "lib/list_util.h"
#include "lib/list.h"
#include "lib/data.h"

int main(int argc, char **argv)
{
    List *list = createList(newInt(9), newInt(8));
    for (int i = 7; i > 0; --i) { insertTail(list, newInt(i)); }

    fprintf(stdout, "Lista inserita: "); printList(list, printInt); fprintf(stdout, "\n");
    sort(list, compareInt);
    fprintf(stdout, "Lista ordinata: "); printList(list, printInt); fprintf(stdout, "\n");

    return 0;
}