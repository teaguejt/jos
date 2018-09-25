#ifndef __JOS_LIST_H__
#define __JOS_LIST_H__

struct llist {
    struct llist *prev;
    struct llist *next;
};

int list_initialize(struct llist *);
void list_add_before(struct llist *, struct llist *);
void list_add_after(struct llist *, struct llist *);
void list_prepend(struct llist *, struct llist *);
void list_append(struct llist *, struct llist *);
void list_delete(struct llist *);

#define list_init(list)                                                 \
    list_initialize((struct llist *)list)

#define list_iterate(head, cursor)                                      \
    for(cursor = head->next; cursor != head; cursor = cursor->next)

#define list_extract(src, list, type)                                     \
    (type *)((unsigned long)(src) - struct_offset(type, list))

#define list_empty(list)                                                \
    (((struct llist *)(list)->next == list ) &&                         \
    ((struct llist *)(list)->prev == list))

void test_llist();

#endif
