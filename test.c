#include <stdio.h>
#include <stdlib.h>
#include "merge_sort.h"

#define N 100

void print_array(const int * const a, const size_t len);

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    int * const numbers = malloc(N * sizeof *numbers);
    if (numbers == NULL) {
        perror(NULL);
        return 1;
    }

    const size_t read = fread(numbers, sizeof *numbers, N, stdin);
    if (read != N) {
        if (ferror(stdin)) {
            perror(NULL);
        } else {
            fprintf(stderr, "Failed to read from stdin.\n");
        }
        return 1;
    }

    const int * const sorted = mergesort(numbers, N);
    if (sorted == NULL) {
        fprintf(stderr, "Failed to sort numbers.\n");
    }

    print_array(numbers, N);
    print_array(sorted, N);

    free((void *)numbers);
    free((void *)sorted);

    return 0;
}

void print_array(const int * const a, const size_t len)
{
    if (len == 0) {
        printf("\n");
        return;
    }

    printf("%d ", *a);
    print_array(a + 1, len - 1);
    return;
}

