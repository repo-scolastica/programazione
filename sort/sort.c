#include <stdlib.h>
#include <stdio.h>

#define SIZE 10 /* Numero di elementi dell'array */
#define TYPE sizeof(int) /* Tipo di dato */
#define SCAN_TYPE scan_int /* Tipo di input */
#define PRINT_TYPE print_int /* Tipo di output */
#define COMPARE_TYPE compare_int /* Tipo di confronto */

/* I/O Array */
void    scan_char(void *element);
void    scan_int(void *element);
void    scan_double(void *element);
void    scan_array(void *base, size_t nmem, size_t memsize, void (*scan)(void *element));

void    print_char(const void *element);
void    print_int(const void *element);
void    print_double(const void *element);
void    print_array(const void *base, size_t nmem, size_t memsize, void (*print)(const void *element));

/* Funzioni di confronto */
int     compare_char(const void *a, const void *b);
int     compare_short(const void *a, const void *b);
int     compare_int(const void *a, const void *b);
int     compare_long(const void *a, const void *b);
int     compare_float(const void *a, const void *b);
int     compare_double(const void *a, const void *b);

/* Funzioni di ordinamento */
void    swap(void *n, void *m, size_t memsize);
void    bubble_sort
(
    void    *base,
    int     nmem,
    int     memsize, 
    int     (*compare)(const void *, const void *)
);

int main()
{
    void *arr = calloc(SIZE, TYPE);
    
    if (arr == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria dell'array\n");
        exit(EXIT_FAILURE);
    }

    scan_array(arr, SIZE, TYPE, SCAN_TYPE);
    print_array(arr, SIZE, TYPE, PRINT_TYPE);


    printf("\n");

    bubble_sort(arr, SIZE, TYPE, COMPARE_TYPE);
    print_array(arr, SIZE, TYPE, PRINT_TYPE);

    return 0;
}

void    scan_char(void *element) { scanf("%c", (char *)element); }
void    scan_int(void *element) { scanf("%d", (int *)element); }
void    scan_double(void *element) { scanf("%lf", (double *)element); }
void    scan_array(void *base, size_t nmem, size_t memsize, void (*scan)(void *element))
{
    for (int i = 0; i < nmem; ++i) { scan(base + i * memsize); }
}

void    print_char(const void *element) { printf("%c", *(char *)element); }
void    print_int(const void *element) { printf("%d", *(int *)element); }
void    print_double(const void *element) { printf("%lf", *(double *)element); }
void    print_array(const void *base, size_t nmem, size_t memsize, void (*print)(const void *element))
{
    for (int i = 0; i < nmem; ++i) { print(base + i * memsize); printf(" "); }
}

int     compare_char(const void *a, const void *b) { return ( *(char *)a - *(char *)b ); }
int     compare_short(const void *a, const void *b) { return ( *(short *)a - *(short *)b ); }
int     compare_int(const void *a, const void *b) { return ( *(int *)a - *(int *)b ); }
int     compare_long(const void *a, const void *b) { return ( *(long *)a - *(long *)b ); }
int     compare_float(const void *a, const void *b) { return ( *(float *)a - *(float *)b ); }
int     compare_double(const void *a, const void *b) { return ( *(double *)a - *(double *)b ); }

void    swap(void *n, void *m, size_t memsize)
{
    char *byte_ptr_n = (char *)n;
    char *byte_ptr_m = (char *)m;
    char temp = 0;

    for (int i = 0; i < memsize; ++i, ++byte_ptr_n, ++byte_ptr_m) {
        temp = *byte_ptr_n;
        *byte_ptr_n = *byte_ptr_m;
        *byte_ptr_m = temp;
    }
}

void    bubble_sort
(
    void    *base, 
    int     nmem,
    int     memsize, 
    int     (*compare)(const void *, const void *)
) {
    int     not_ordered =   1;

    void    *prev =         NULL;
    void    *succ =         NULL;

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