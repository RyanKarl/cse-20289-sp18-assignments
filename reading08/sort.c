/* sort.c */

#include <stdio.h>
#include <stdlib.h>


/* Constants */

#define MAX_NUMBERS (1<<10)

/* Functions */

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

size_t read_numbers(FILE *stream, int numbers[], size_t n) {
    size_t i = 0;

    while (i < n && scanf("%d", &numbers[i]) != EOF) {
      // printf("%d\n", numbers[i]);
            i++;
    }

   // qsort(numbers, 4, i, cmpfunc);

    return i;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int numbers[MAX_NUMBERS];
   // int total;
    size_t nsize;
    int x = 0;

    nsize = read_numbers(stdin, numbers, MAX_NUMBERS);
    qsort(numbers, nsize, 4, cmpfunc);
    
    while (x < nsize) {
        printf("%d\n", numbers[x]);
        x++;
    }
    
    return EXIT_SUCCESS;
}
