/*
 * tree.c
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


#define SZ  20
typedef struct node* link;

typedef struct node {
    int value;
    link left,right;
} node;

link queue[SZ+1];
int  tail = 0, head = SZ;
link dequeue()
{
    tail %= SZ;
    return queue[tail++];
}

void enqueue(link l) {
    head = head%SZ;
    queue[head] = l;
    head++;
}

void clearQ() {
    tail = 0, head = SZ;
}

link append(int i, link root) {
    if (root == NULL) {
        root = malloc(sizeof *root);
        root->value = i, root->left = root->right = NULL;
        return root;
    }

    if (root->value > i) {
        root->left = append(i, root->left);
    } else {
        root->right = append(i, root->right);
    }
    return root;
}

void preorder(link root) {
    if(root == NULL) return;

    printf("%d ", root->value);

    preorder(root->left);
    preorder(root->right);
}

void it_preorder(link root) {
    if( root == NULL) return;

    stk_t stk;
    stk_init(&stk, sizeof(link), SZ);

    link node = root;

    while(node != NULL || !stk_empty(&stk)) {
        if(node != NULL) {
            printf("%d, ", node->value);
            if(node->right != NULL) {
                push(&stk, node->right);
                //~ printf("-> %d\n" , node->right->value);
            }
            node = node->left;
        } else  {
            node = pop(&stk);
            //~ printf("<- %d\n" , node->value);
        }
    }

    stk_destory(&stk);
}

void midorder(link root) {
    if(root == NULL) return;

    midorder(root->left);
    printf("%d ", root->value);
    midorder(root->right);
}

void it_midorder(link root) {
    if( root == NULL) return;

    stk_t stk;
    stk_init(&stk, sizeof(link), SZ);

    link node = root;

    while(!stk_empty(&stk) || node != NULL) {
        if(node != NULL) {
            push(&stk, node);
            node = node->left;
        } else {
            node = pop(&stk);
            printf("%d, ", node->value);
            node = node->right;
        }
    }

    stk_destory(&stk);
}

int max(int i, int j) {
    return i>j? i: j;
}
void postorder(link root) {
    if(root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->value);
}


int treeHight(link root) {
    if(root == NULL) return 0;

    return max( treeHight(root->left), treeHight(root->right) ) + 1;
}


void it_postorder(link root) {
    if(root == NULL) return;

    stk_t stk;
    stk_init(&stk, sizeof(link), SZ);

    link n = root, last = NULL;

    //int l = 0, r = 0, m = 0;

    while(n != NULL || !stk_empty(&stk)) {
        if(n) {
            if(last != n) {
                push(&stk, n), n = n->left;
            } else {
                n = NULL;
            }
        } else {
            n = pop(&stk);
            if(n->right && last != n->right) {
                push(&stk, n), n = n->right;
            } else {
                printf("%d, ", n->value);
                last = n;
            }
        }
    }
}
void r_prtTree(int deepth, link node) {
    int i = deepth;
    if(node != NULL) {
        r_prtTree(deepth+1, node->right);
        while(i-->0) printf("%s","\t");
        printf("%d\n", node->value);
        r_prtTree(deepth+1, node->left);
    } else {
        while(i-->0) printf("%s","\t");
        printf("%s\n", "*");
    }
}

void prtTree(link root) {
    r_prtTree(0, root);
}

int indexOf(int v, int *p, int len) {
    int i = 0;
    for(; i<len; i++) {
        if(*(p+i) == v)
            return i;
    }

    return -1;
}

typedef struct {
    int* order_one;
    int* order_two;
    int len;
    link n;
} sub_tree;


link makeNode(int v) {
    link l = malloc(sizeof*l);

    if(l == NULL) {
        perror("mem out!\n");
        exit(1);
    }

    l->value = v, l->left = l->right = NULL;

    return l;
}

link build_pre_mid_Tree(int *pre, int *mid, int len) {
    if(len < 1 ) return NULL;
    
   
//~ // Inerative with a stack below
    link u = makeNode(pre[0]);

    stk_t stk;
    stk_init(&stk, sizeof(sub_tree*), len/2);

    sub_tree *st = malloc(sizeof *st);
    st->order_one = pre;
    st->order_two = mid;
    st->len = len;
    st->n = u;

   // push(&stk, st);
  

    while(!stk_empty(&stk)) {
        sub_tree *t = pop(&stk);
        if(t->len > 1) {
            int root_i = indexOf(t->n->value, t->order_two, t->len);
            int left_len = root_i;
            int right_len = t->len - root_i - 1;
            
               sub_tree *left_st = malloc(sizeof *left_st);
               left_st->order_one = t->order_one + 1;
               left_st->order_two = t->order_two;
               left_st->len = left_len;
               left_st->n = makeNode(left_st->order_one[0]);
               t->n->left = left_st->n;

             
               //~ printf("l->%d : %d\n", left_st->n->value, left_st->len);
           
               sub_tree *r_st = malloc(sizeof *r_st);
               r_st->order_one = t->order_one + 1 + left_len;
               r_st->order_two = t->order_two + root_i + 1;
               r_st->len = right_len;
               r_st->n =  makeNode(r_st->order_one[0]);
               t->n->right = r_st->n;
               
               if(left_len > right_len) {
                  push(&stk, left_st);
                  push(&stk, r_st);
               } else {
                  push(&stk, r_st);
                  push(&stk, left_st);
               }
               printf("r->%d : %d\n", r_st->n->value, r_st->len);
        } 
        free(t);
    }
    
    // Recusive below
    //~ if(len > 1) {
    //~
    //~ l->left = build_pre_mid_Tree(pre + 1, mid, left_len);
    //~ l->right = build_pre_mid_Tree(pre + 1 + left_len, mid + root_i + 1, right_len);
    //~ }
  
    return u;
}

link build_mid_post_tree(int* mid, int* post , int len) {
    if (len < 1) return NULL;

    link l = malloc(sizeof*l);

    if(l == NULL) {
        perror("mem out!\n");
        exit(1);
    }

    int root_i = indexOf(post[len-1], mid, len);

    l->value = post[len-1], l->left = l->right = NULL;

    if(len > 1) {
        int left_len = root_i;
        int right_len = len - root_i - 1;
        l->left  = build_mid_post_tree(mid, post, left_len);
        l->right  = build_mid_post_tree(mid + left_len + 1, post + left_len ,right_len);
    }
    return l;


}

link build_pre_post_tree(int *pre, int* post, int len) {
    if (len < 1) return NULL;

    if(pre[0] != post[len-1]) return NULL;


    link l = malloc(sizeof*l);

    if(l == NULL) {
        perror("mem out!\n");
        exit(1);
    }

    l->value = pre[0], l->left = l->right = NULL;

    if(len>1) {
        int child = post[len - 2];

        int child_i = indexOf(child, pre, len);

        int left_len = child_i - 1;

        int right_len = len - child_i ;

        l->left  = build_pre_post_tree(pre + 1, post, left_len);
        l->right = build_pre_post_tree(pre + left_len + 1, post + left_len ,right_len);
    }

    return l;

}
int main(int argc, char **argv)
{
    int test[] = {2,6,12,78,4,27,9,0,21,1};

    link root = NULL;

    int i = 0;

    for(i = 0; i< sizeof(test)/sizeof(test[0]) ; i++) {
        root = append(test[i], root);
    }
    
    //~
    //~ printf("preorder\n");
    //~ preorder(root);
    //~ printf("\n");
    //~ it_preorder(root);
    //~ printf("\npreorder done\n");
    //~
    //~ printf("midorder\n");
    //~ midorder(root);
    //~ printf("\n");
    //~ it_midorder(root);
    //~ printf("\nmidorder done\n");

    prtTree(root);
    it_preorder(root);
    printf("\n");
    it_midorder(root);
    printf("\n");
    it_postorder(root);

    printf("\n tree hight : %d\n",treeHight(root));

    int pre[] = {2, 0, 1, 6, 4, 12, 9, 78, 27, 21};
    int post[] = {1, 0, 4, 9, 21, 27, 78, 12, 6, 2};
    int mid[] = {0, 1, 2, 4, 6, 9, 12, 21, 27, 78};


   // prtTree( build_pre_mid_Tree(pre, mid, sizeof(test)/sizeof(int)) );
   // prtTree( build_mid_post_tree( mid, post, sizeof(test)/sizeof(int)) );

    prtTree( build_pre_post_tree(pre, post, sizeof(test)/sizeof(test[0])) );
    enqueue(root);

    while(head%SZ != tail) {

        link l = dequeue();
        //  printf("%d ", l->value);

        if(l->left != NULL)  enqueue(l->left);
        if(l->right != NULL)  enqueue(l->right);

        free(l);
    }
    return 0;
}



