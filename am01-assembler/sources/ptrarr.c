#include "ptrarr.h"

static const int STEP_SIZE = 10;

Ptrarr *pa_init() {
    Ptrarr *pa = malloc(sizeof(Ptrarr));
    pa->arr = malloc(sizeof(void *) * STEP_SIZE);
    return pa;
}

void pa_add(Ptrarr *pa) {

}

void pa_trim(Ptrarr *pa) {

}

void pa_free(Ptrarr *pa) {
    free(pa->arr);
    free(pa);
}
