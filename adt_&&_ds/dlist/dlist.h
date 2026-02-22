//
// Created by ASUS on 2/1/2026.
//

#ifndef ADS_BASICS_DLIST_H
#define ADS_BASICS_DLIST_H


typedef struct dnode {
    int data;
    struct dnode* next;
    struct dnode* prev;
} dnode_t;

typedef struct {
    dnode_t* head;
    dnode_t* tail;
    size_t size;
} dlist;

// --- Creation & Destruction ---
dlist* dlist_create();
void     dlist_destroy(dlist* l);

// --- Insertion ---
void     dlist_insert_head(dlist* l, int value);
void     dlist_insert_tail(dlist* l, int value);
void     dlist_insert_after(dlist* l, dnode_t* pos, int value);
void     dlist_insert_before(dlist* l, dnode_t* pos, int value);

// --- Traversal/Search ---
dnode_t* dlist_find(const dlist* l, int value);
void     dlist_print(const dlist* l);

// --- Deletion ---
void     dlist_delete_head(dlist* l);
void     dlist_delete_tail(dlist* l);
void     dlist_delete_node(dlist* l, dnode_t* node);
void     dlist_delete_byValue(dlist* l, int value);

#endif //ADS_BASICS_DLIST_H