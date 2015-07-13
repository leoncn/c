/*
 * qsort.c
 *
 * Copyright 2015 U0128754 <U0128754@U0128754-TPL-A>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define BUF_SZ 100

void swap(int* i, int* j) {
    if(i == j) return;

    int t= *i;
    *i = *j;
    *j = t;
}

int partition(int* a, int from, int to) {

    int last = from, pivot = from, i;

    for(i = from + 1 ; i<to; i++) {
        if(a[i] < a[pivot]) {
            swap(&a[i], &a[++last]);
        }
    }
    swap(&a[pivot], &a[last]);

    return last;
}
void lqsort (int *a, int from, int to) {
    if(from < to) {
        int t = partition(a, from, to);
        lqsort(a , from, t);
        lqsort(a , t + 1, to);
    }
}

typedef struct pair {
   int from;
    int to;
} pair_t;
   
void it_lqsort (int *a, int from, int to) {
    stk_t stk;
    stk_init(&stk, sizeof(pair_t*), (to-from)/2);

    while(from < to || !stk_empty(&stk)) {
        if(from < to) {
           int t = partition(a, from, to);
            pair_t* p = malloc(sizeof*p);
            if(t - from > to - t) {
                p->from = from, p->to = t;
                push(&stk, p);
                from = t + 1;
            } else {
                p->from = t + 1; p->to = to;
                push(&stk, p);
                to = t;
            }
        } else {
            pair_t* p = pop(&stk);
            from = p->from;
            to = p->to;
            free(p);
        }
    }

    stk_destory(&stk);
}

void sort_prtInts(int *a, int from, int to) {
    it_lqsort(a, from , to );
    int i;
    for(i = from ; i<to; i++) {
        printf("%d ",  a[i]);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    int pre[] = {2, 0, 1, 6, 4, 12, 9, 78, 27, 21};
    int post[] = {1, 0, 4, 9, 21, 27, 78, 12, 6, 2};
    int mid[] = {0, 1, 2, 4, 6, 9, 12, 21, 27, 78};


    sort_prtInts(pre, 0, sizeof(pre)/sizeof(pre[0]));
    sort_prtInts(post, 0, sizeof(post)/sizeof(post[0]));
    sort_prtInts(mid, 0, sizeof(mid)/sizeof(mid[0]));


    return 0;
}

