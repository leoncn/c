/*
 * stack_test.c
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
#include <time.h>
#include "stack.h"

int r_num(int lo, int hi) {
    return lo + rand()%(hi - lo + 1);
}

/**
 * This program test the stack api, performs a insert sort by using
 * two stacks.
 **/
#define MAX 10
int main(int argc, char **argv)
{
    stk_t stk, aux_stk;

    stk_init(&stk, sizeof(int*), MAX), stk_init(&aux_stk, sizeof(int*), MAX);
    time_t t;
    srand((unsigned)time(&t));

    int i, a[MAX], lo = 15, hi = 40;

    for(i = 0; i<MAX; i++) {
        a[i] = r_num( lo,  hi);
    }
    for(i = 0; i<MAX; i++) {
        printf(" ======Process %d @ %p======\n", a[i], &a[i]);
        //drain all elemements larger than n
        int* p = NULL;
        while(!stk_empty(&stk) && *(p = (int*)peek(&stk)) <a[i]) {
            printf("<-%p\n", p);
            push(&aux_stk, pop(&stk));
        }

        //push to stk
        push(&stk, &a[i]);
        //move all previously moved elements back
        while(!stk_empty(&aux_stk) && !stk_full(&stk)) {
            p = (int*)pop(&aux_stk);
            printf("->%p\n", p);
            push(&stk, p);
        }
    }

    while(!stk_empty(&stk)) {
        printf("%d ", *((int*)pop(&stk)));
    }

    stk_destory(&stk);
    stk_destory(&aux_stk);
    return 0;
}

