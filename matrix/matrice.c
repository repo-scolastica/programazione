#include <stdlib.h>
#include <stdio.h>

void scan_char(void *element) { scanf("%c", (char *)element); }
void scan_int(void *element) { scanf("%d", (int *)element); }
void scan_double(void *element) { scanf("%lf", (double *)element); }

void print_char(const void *element) { printf("%c", *(char *)element); }
void print_int(const void *element) { printf("%d", *(int *)element); }
void print_float(const void *element) { printf("%lf", *(float *)element); }

void insertMatrix
(
    void *base, 
    int ncols, 
    int memsize, 
    int rows, 
    int cols, 
    void (*scan)(void *)
) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            scan(base + (i * ncols + j) * memsize);
        }
    }    
}

void outputMatrix
(
    void *base,
    int ncols,
    int memsize,
    int rows,
    int cols,
    void (*print)(const void *)
) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            print(base + (i * ncols + j) * memsize);
            printf(" ");
        }   printf("\n");
    }
}

int main()
{
    int matrix_int[3][3] = { 0 };

    insertMatrix(matrix_int, 3, sizeof(int), 2, 2, scan_int);
    outputMatrix(matrix_int, 3, sizeof(int), 2, 2, print_int);
    
    return 0;
}