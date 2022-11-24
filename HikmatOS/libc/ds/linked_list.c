#include <ds.h>
#include <stddef.h>

ll_node_t *create_list() {
    return kmalloc(sizeof(ll_node_t));
}

void ll_insert(ll_node_t *ll, void *value) {
    if (ll->value == NULL) {
        ll->value = value;
        return;
    }
    while (ll->next != NULL)
        ll = ll->next;
    ll->next = kmalloc(sizeof(ll_node_t));
    ll->value = value;
}

void ll_remove_value(ll_node_t *ll, void *value) {
    ll_node_t *prev = ll;
    for (ll_node_t *i = ll; i->next != NULL; i = i->next) {
        if (i->value == value) {
            prev->next = i->next;
            kfree(i);
        }
        prev = i;
    }
}

