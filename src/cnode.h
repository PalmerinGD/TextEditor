#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct cnode {
    char c;
    struct cnode * next;
    struct cnode * prev;
};

struct cnodeList {
    // Size of cnodeList
    size_t size;
    struct cnode * begin;
    struct cnode * end;
    struct cnode * currentcnode;
};

struct cnode * createcnode(char c);
struct cnode * cnodeParent(struct cnode * cn);

/* Init functions */
void initcnodeList(struct cnodeList * clist);

int addcnode(struct cnodeList * clist, char c);
int getTotalcnodes(struct cnode * cn);
int movecnode(struct cnodeList * clist, int n);
int printcnodeList(int fd, struct cnodeList * clist);

//int moveCurrentcnodeDown(struct cnode ** cn);
//int moveCurrentcnodeUp(struct cnode ** cn);
//int moveCurrentcnodeLeft(struct cnode ** cn);
//int moveCurrentcnodeRight(struct cnode ** cn);
