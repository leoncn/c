/*
 * list.c
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

typedef  struct list* list_t;

typedef struct list {
      int v;
      list_t next;
} list;

void* ealloc(size_t sz) {
   void *p = malloc(sz);
   
   if(p == NULL) {
      perror("Fail to allocate memory.\n");
      exit(1);
   }
   
   return p;
}
list_t newNode(int v) {
   list_t n = ealloc(sizeof v);
   
   n->v = v;
   
   return n;
   
}

list_t insertBefore(list_t head, list_t l) {
   l->next = head;
   return l;
}

void  insertAfter(list_t curr, list_t nx) {
   nx->next = curr->next, curr->next = nx;
}

void append(list_t head, list_t l) {
   list_t t = NULL;
   
   for(t = head; t->next!=NULL;t=t->next) {
         ;
   }
   
   t->next = l;
}

list_t find(list_t head, int v) {
   list_t t = NULL;
   for( t = head; t!= NULL && t-> v != v; t = t->next) {
         ;
   }
   
   return t;
}

void del(list_t head, int v) {
   list dummy_head;
   list_t prv = &dummy_head;
   
   for(prv->next = head; prv->next!=NULL; prv = prv->next) {
      if(prv->next->v == v) {
         list_t matched = prv->next;
         insertAfter(prv, matched->next);
         free(matched);
      }
   }
   return;
}

void prt_list(list_t head) {
      list_t t = NULL;
      
      for(t = head; t!=NULL; t=t->next) {
         printf("%d ", t->v);
      }
}

int main(int argc, char **argv)
{
	return 0;
}

