/*
 * stack.c
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
#include <stddef.h>
#include <stdlib.h>
#include "stack.h"

void* pop(stk_t *stk) {
    if( stk == NULL || stk_empty(stk)) {
        perror("stack is empty.\n");
    }
    int offset = stk->top--;
    return *(stk->data + offset * stk->el_sz/sizeof(void*));
}

void* peek(stk_t *stk) {
    if( stk == NULL || stk_empty(stk)) {
        perror("stack is empty.\n");
    }

    return *(stk->data + stk->top * stk->el_sz/sizeof(void*));
}

void push(stk_t *stk, void* el) {
    if( stk == NULL || stk_full(stk)) {
        perror("stack is full.\n");
    }

    int offset = ++stk->top;
    *(stk->data + offset * stk->el_sz/sizeof(void*)) = el;
}

int stk_empty(stk_t *stk) {
    return stk->top < 0 ? 1 : 0;
}

int stk_full(stk_t *stk) {
    return stk->top + 1 == stk->max_sz ? 1 : 0;
}

void stk_init(stk_t *stk, size_t el_sz, int max_sz) {
    stk->top = -1, stk->el_sz = el_sz, stk->max_sz = max_sz;
    stk->data = malloc(stk->el_sz * stk->max_sz);

    if(stk->data == NULL) {
        fprintf(stderr,"Insufficient memory to init stack.\n");
        exit(1);
    }
}

void stk_destory(stk_t *stk) {
    free(stk->data);
    stk->top = -1, stk->el_sz = 0, stk->max_sz = 0, stk->data = NULL;
}
