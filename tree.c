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

#define SZ 10

typedef struct node* link;

//typedef link stk_element;


typedef struct node {
    int value;
    link left,right;
};

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

    while(1) {
        if(node != NULL) {
            printf("%d ", node->value);
            if(node->right != NULL) {
                push(&stk, node->right);
            }
            node = node->left;
        } else if(!stk_empty(&stk)){
            node = pop(&stk);
        } else {
			break;
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
			printf("%d ", node->value);
			node = node->right;
		}
	}
    
    stk_destory(&stk);
}

int main(int argc, char **argv)
{
    int test[] = {2,6,12,78,4,0,21,1};

    link root = NULL;

    int i = 0;

    for(i = 0; i< sizeof(test)/sizeof(int) ; i++) {
        root = append(test[i], root);
    }

    printf("preorder\n");
    preorder(root);
    printf("\n");
    it_preorder(root);
    printf("\npreorder done\n");

    printf("midorder\n");
    midorder(root);
    printf("\n");
    it_midorder(root);
    printf("\nmidorder done\n");

    enqueue(root);

    while(head%SZ != tail) {

        link l = dequeue();
        printf("%d ", l->value);

        if(l->left != NULL)  enqueue(l->left);
        if(l->right != NULL)  enqueue(l->right);

        free(l);
    }

    return 0;
}

