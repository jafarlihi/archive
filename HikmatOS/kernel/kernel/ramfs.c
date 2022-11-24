#include <ds.h>
#include <string.h>
#include <kernel/ramfs.h>
#include <kernel/fs.h>
#include <arch/i386/kheap.h>

uint32_t read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
    if (size > node->length - offset)
        return 0;
    void *actual = node->actual;
    memcpy(buffer, (uint8_t *)actual + offset, size);
    return size;
}

uint32_t write(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
    if (size > node->length - offset) {
        void *new_actual = kmalloc(node->length + size - offset);
        memcpy(new_actual, node->actual, node->length);
        node->actual = new_actual;
    }
    memcpy((uint8_t *)node->actual + offset, buffer, size);
    node->length = offset + size > node->length ? offset + size : node->length;
    return size;
}

fs_node_t *readdir(fs_node_t *node, uint32_t index) {
    ll_node_t *llnode = node->children;
    for (int i = 0; i <= index; i++)
        llnode = llnode->next;
    return llnode;
}

void open(fs_node_t *node) {
    return;
}

void close(fs_node_t *node) {
    return;
}

int next_inode = 0;

static fs_node_t *new_fs_node_t() {
    fs_node_t *node = kmalloc(sizeof(fs_node_t));
    node->inode = ++next_inode;
    node->read = read;
    node->write = write;
    node->open = open;
    node->close = close;
    node->readdir = readdir;
    return node;
}

fs_node_t *init_ramfs() {
    fs_node_t *root = new_fs_node_t();
    strcpy(root->name, "dev");
    root->flags |= FS_DIRECTORY;
    root->children = create_list();

    fs_node_t *testFile = new_fs_node_t();
    strcpy(root->name, "test.txt");
    testFile->flags |= FS_FILE;
    testFile->actual = strdup("Hello world");

    ll_insert(root->children, (void *)testFile);

    return root;
}

