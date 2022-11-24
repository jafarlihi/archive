struct nlist {
    struct nlist* next;
    char* name;
    char* defn;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

unsigned hash(char*);
struct nlist* lookup(char*);
struct nlist* install(char*, char*);
int undef(char*);
