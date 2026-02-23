#ifndef ADS_BASICS_SLIST_H
#define ADS_BASICS_SLIST_H

#include <stddef.h>

typedef struct snode_s {
    int data;
    struct snode_s * next;
} snode_t;

typedef struct {
    snode_t * head;
    snode_t * tail;
    size_t size;
} slist;

slist*  slist_create();
void  slist_destroy(slist* l);

snode_t *slist_find(const slist *l, int value);
snode_t *slist_find_parent(const slist *l, int value);

void slist_insert_head(slist* l, int value);
void slist_insert_tail(slist* l, int value);
void slist_insert_after(slist *l, snode_t* pos, int value);

void slist_delete_head(slist *l);
void slist_delete_tail(slist *l);
void slist_delete_after(slist *l, snode_t *pos);
void slist_delete_byValue(slist* l, int value);

void slist_print(const slist *l);

#endif //ADS_BASICS_SLIST_H