


#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


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
=======
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

    n->next = NULL, n->v = v;

    return n;

}


void prt_list(list_t head) {
    list_t t = NULL;

    for(t = head; t!=NULL; t=t->next) {
        printf("%d ", t->v);
    }
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

    for(t = head; t->next!=NULL; t=t->next) {
        ;
    }

    t->next = l;
}

list_t insert_sort(list_t head) {

    list_t r = malloc(sizeof *r), u, t;
    r->next = NULL;

    while(head != NULL) {
        u = head;
        head = head->next;

        for(t = r; t->next != NULL && t->next->v < u->v; t = t->next) {
        }
        insertAfter(t, u);
    }
    head = r->next;
    free(r);
    return head;
}
list_t find(list_t head, int v) {
    list_t t = NULL;
    for( t = head; t!= NULL && t-> v != v; t = t->next) {
        ;
    }

    return t;
}

list_t del(list_t head, int v) {
    list_t prv, u;
    prv = u = newNode(0);
    prv->next = head;

    while(prv->next!=NULL) {
        if(prv->next->v == v) {
            list_t matched = prv->next;
            prv->next = prv->next->next;
            free(matched);
        } else {
            prv = prv->next;
        }
    }
    prv = u;
    u = prv->next;
    free(prv);

    return u;
}

list_t merge(list_t a, list_t b) {
   
   list_t head, tail, u;
   head = tail = malloc(sizeof *head);
   head->next = NULL;
   
   while(a!=NULL || b!=NULL) {
      if(a == NULL) {
        append(tail,b);
        break;
      }
      
      if( b == NULL) {
        append(tail,a);
        break;
      }
      
      if(a->v < b->v) {
         u = a;
         a = a->next;
         u->next = NULL;
        
      } else {
         u = b;
         b = b->next;
         u->next = NULL;
      }
       append(tail,u);
       tail = u; 
   }
   
   list_t r = head->next;
   
   free(head);
   
   return r;
}

int main(int argc, char **argv)
{
    time_t t;
    time(&t);
    srand((unsigned)t);
    
    list_t heada, headb;
    heada = headb = NULL;
    int values[10];
    int len = sizeof(values)/sizeof(values[0]) , i = 0;
   
    for(i = 0; i< len; i++) {
       values[i] = rand()%100;
    }
    
     for(i = 0; i< len; i++) {
        heada = insertBefore(heada, newNode(values[i]));
    }
   
   for(i = 0; i< len; i++) {
       values[i] = rand()%100;
    }
    
    headb = newNode(values[--i]);
    while(i>0) {
        insertAfter(headb, newNode(values[--i]));
    }
    
    printf("list a is:\n");
    prt_list(heada);
    printf("\nlist b is:\n");
    prt_list(headb);
    
    heada = insert_sort(heada);
    headb = insert_sort(headb);
    printf("\nsorted list a is:\n");
    prt_list(heada);
    printf("\nsorted b is:\n");
    prt_list(headb);
   
    printf("\nmerge a & b :\n");
    prt_list(merge(heada, headb));
    //~ for(i = 0; i< len && heada!=NULL; i++) {
        //~ printf("removing %d \n", values[i]);
        //~ heada = del(heada, values[i]);
        //~ prt_list(heada);
        //~ printf("\n");
    //~ }

    return 0;
}

