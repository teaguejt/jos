#include <list.h>
#include <kernel.h>
#include "../io/kprintf.h"

struct list_test_struct {
    int val;
    unsigned long junk;
    struct llist list;
};

void print_list_contents(struct llist *head) {
    struct llist *cursor;
    struct list_test_struct *val;

    if(list_empty(head)) {
        kprintf("List is empty.\n");
    }
    else {
        list_iterate(head, cursor) {
            val = list_extract(cursor, list, struct list_test_struct);
            kprintf("%d ", val->val);
        }
        kprintf("\n");
    }
}    

void test_llist() {
    struct llist head;
    struct list_test_struct l1, l2, l3, l4, l5;

    list_initialize(&head);
    print_list_contents(&head);

    list_init(&l1.list);
    l1.val = 1;
    l2.val = 2;
    l3.val = 3;
    l4.val = 4;
    l5.val = 5;

    list_append(&head, &l1.list);
    print_list_contents(&head);

    list_prepend(&head, &l2.list);
    print_list_contents(&head);

    list_append(&head, &l3.list);
    print_list_contents(&head);

    list_prepend(&head, &l4.list);
    print_list_contents(&head);

    list_append(&head, &l5.list);
    print_list_contents(&head);

    list_delete(&l4.list);
    print_list_contents(&head);

    list_delete(&l1.list);
    print_list_contents(&head);

    list_delete(&l2.list);
    print_list_contents(&head);

    list_delete(&l5.list);
    print_list_contents(&head);

    list_delete(&l3.list);
    print_list_contents(&head);
}
