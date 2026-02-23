#ifndef ADS_BASICS_CLIST_H
#define ADS_BASICS_CLIST_H

typedef struct cnode {
    int data;
    struct cnode* next;
} cnode_t;

typedef struct {
    cnode_t* head;
    cnode_t* tail;
    size_t size;
} clist;

// --- Creation & Destruction ---
clist* clist_create();
void     clist_destroy(clist* l);

// --- Insertion ---
void     clist_insert_head(clist* l, int value);
void     clist_insert_tail(clist* l, int value);
void     clist_insert_after(clist* l, cnode_t* pos, int value);

// --- Traversal/Search ---
cnode_t* clist_find(const clist* l, int value);
cnode_t* clist_find_parent(const clist* l, int value);

void     clist_print(const clist* l);

// --- Deletion ---
void     clist_delete_head(clist* l);
void     clist_delete_tail(clist* l);
void     clist_delete_after(clist* l, cnode_t* pos);
void     clist_delete_byValue(clist* l, int value);

#endif //ADS_BASICS_CLIST_H