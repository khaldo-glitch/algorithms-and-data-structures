#include <stdio.h>
#include "slist.h"
#include <stdlib.h>

slist*  slist_create() {
    slist* l = (slist*) malloc(sizeof(slist));
    if (l == NULL) {
        fprintf(stderr, "Memory allocation failed for list\n");
        return NULL;
    }
    l->head= NULL;
    l->tail= NULL;
    l->size= 0;
    return l;
}

void  slist_destroy(slist* l) {
    if (l==NULL) {
        fprintf(stderr,"Single-Linked List Pointer is NULL\n");
        return;
    }
    snode_t* node = l->head;
    while (node != NULL) {
        snode_t* next = node->next;
        free(node);
        node = next;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    free(l);
}

void slist_insert_head(slist* l, int value) {
    if (l==NULL) {
        fprintf(stderr,"Single-Linked List Pointer is NULL\n");
        return;
    }

    snode_t* node = (snode_t*) malloc(sizeof(snode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data= value;
    node->next= l->head;
    l->head = node;
    if (l->tail== NULL) {
        l->tail = node;
    }
    l->size++;
}


snode_t *slist_find(const slist *l, int value) {
    if (l==NULL) {
        fprintf(stderr,"Single-Linked List Pointer is NULL\n");
        return NULL;
    }
    snode_t* node = l->head;
    while (node!=NULL) {
        if (node->data==value) {
            return node;
        }
        node=node->next;
    }

    fprintf(stderr,"No node contains the value\n");
    return NULL;
}

snode_t *slist_find_parent(const slist *l, int value) {
    if (l==NULL || l->head==NULL) {
        fprintf(stderr,"Single-linked list pointer OR its head pointer is NULL\n");
        return NULL;
    }

    if (l->head->data ==value) {
        fprintf(stderr,"The head node contains the desired value (NO PARENT EXISTS)\n");
        return NULL;
    }
    snode_t* node = l->head;
    while (node->next !=NULL) {
        if (node->next->data==value) {
            return node;
        }
        node=node->next;
    }
    fprintf(stderr,"No node data matches the value %d\n", value);
    return NULL;
}

void slist_insert_tail(slist* l, int value) {
    if (l==NULL) return;

    snode_t* node = (snode_t*) malloc(sizeof(snode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data = value;
    node->next = NULL;
    if (l->tail != NULL) {
        l->tail->next= node;
    }else {
        l->head= node;
    }
    l->tail = node;
    l->size++;
}

void slist_insert_after(slist *l, snode_t* pos, int value) {
    if (l == NULL || pos == NULL) return;
    snode_t* node = (snode_t*) malloc(sizeof(snode_t));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    node->data=value;
    node->next= pos->next;
    if (pos->next == NULL)
        l->tail = node;
    pos->next= node;
    l->size++;
}

void slist_delete_head(slist *l) {
    if (l==NULL ||l->head==NULL) return;
    snode_t* tmp = l->head;
    l->head= l->head->next;
    if (l->head==NULL) {
        l->tail = NULL;
    }
    free(tmp);
    l->size--;
}

void slist_delete_tail(slist *l) {
    if (l==NULL || l->head==NULL ) return;
    if (l->head==l->tail) {
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
        l->size=0;
        return;
    }
    snode_t * node= l->head;

    while (node->next != l->tail) {
        node = node->next;
    }
    free(l->tail);
    node->next=NULL;
    l->tail=node;
    l->size--;
}

void slist_delete_after(slist *l, snode_t *pos) {
    if (l == NULL || pos==NULL || pos->next==NULL)
        return;
    snode_t* tmp = pos->next;
    if (tmp== l->tail)
        l->tail=pos;
    pos->next = tmp->next;
    free(tmp);
    l->size--;
}

void slist_delete_byValue(slist* l, int value) {
    if (l == NULL || l->head == NULL) return;

    if (l->head->data == value) {
        slist_delete_head(l);
        return;
    }
    snode_t* node = slist_find_parent(l,value);
    if (node!=NULL) {
        slist_delete_after(l,node);
    }
}

void slist_print(const slist *l) {
    if (l == NULL) {
        printf("[List is NULL]\n");
        return;
    }

    printf("List (size=%zu): ", l->size);
    snode_t *node = l->head;
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
