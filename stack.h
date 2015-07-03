/*
 * stack.h
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
#include <stddef.h>
 
#ifndef _STACK_H
#define _STACK_H

typedef struct stack {
	void **data;
	int   top;
	int   max_sz;
	size_t  el_sz;
} stk_t;

void* pop(stk_t *stk);

void* peek(stk_t *stk);

void push(stk_t *stk, void* el);

int stk_empty(stk_t *stk);

int stk_full(stk_t *stk);

void stk_init( stk_t *stk, size_t el_sz, int max_sz);

void stk_destory(stk_t *stk);

#endif  /* not defined _STACK_H */
