#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define C const

static int *merge(C int * C lhs, C int * C rhs, C size_t ll, C size_t rl);
static void rmerge(int * C merged, C int * C lhs, C int * C rhs, C size_t ll, C size_t rl);

C int *mergesort(C int * C array, C size_t length)
{
    if (length == 1) {
        return array;
    } else {
        C size_t ll = length / 2;
        C size_t rl = length - ll;

        C int * C lhs = mergesort(array, ll);
        C int * C rhs = mergesort(array + ll, rl);

        if (lhs == NULL || rhs == NULL) {
            return NULL;
        }

        return merge(lhs, rhs, ll, rl);
    }
}

static int *merge(C int * C lhs, C int * C rhs, C size_t ll, C size_t rl)
{
    int * C merged = malloc((ll + rl) * sizeof *merged);
    if (merged == NULL) {
        return NULL;
    }

    rmerge(merged, lhs, rhs, ll, rl);

    if (ll > 1) free((void *)lhs);
    if (rl > 1) free((void *)rhs);

    return merged;
}

static void rmerge(int * C merged, C int * C lhs, C int * C rhs, C size_t ll, C size_t rl)
{
    if (ll == 0 && rl == 0) {
        return;
    }

    C bool left = ll == 0 ? false : (rl == 0 ? true : (*lhs < *rhs));

    C int * C lhs_prime = left ? lhs + 1 : lhs;
    C int * C rhs_prime = left ? rhs : rhs + 1;
    C int ll_prime = left ? ll - 1 : ll;
    C int rl_prime = left ? rl : rl - 1;

    *merged = left ? *lhs : *rhs;

    rmerge(merged + 1, lhs_prime, rhs_prime, ll_prime, rl_prime);
}

#undef C

