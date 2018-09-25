#include <kernel.h>
#include <list.h>

int list_initialize(struct llist *list) {
    if(!list) {
        return -1;
    }

    list->prev = list;
    list->next = list;

    return 0;
}

void list_add_before(struct llist *existing, struct llist *new) {
    new->prev = existing->prev;
    new->next = existing;
    existing->prev->next = new;
    existing->prev = new;
}

void list_add_after(struct llist *existing, struct llist *new) {
    new->prev = existing;
    new->next = existing->next;
    existing->next->prev = new;
    existing->next = new;
}

void list_prepend(struct llist *head, struct llist *new) {
    list_add_after(head, new);
}

void list_append(struct llist *head, struct llist *new) {
    list_add_before(head, new);
}

void list_delete(struct llist *list) {
    list->prev->next = list->next;
    list->next->prev = list->prev;
    list->next = NULL;
    list->prev = NULL;
}
