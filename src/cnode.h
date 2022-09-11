/*
Author: Diego Palmerin

Description:
- A cnode stands for a link list of type char, but for simplicity was called cnode. 

- Each time the user adds a new line, two cnodes are also added. The first one the begin line
  character which indicates when is the beginning of a line and the enter character.
  In reallity the enter character are two values '\r' and '\n', they are only added when the
  function getcnodeListToString is called.
*/

/*** Includes ***/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*** Defines ***/
#define BEGIN_LINE 0
#define ENTER 1

/*** Structs ***/
struct cnode {
    // Character of cnode
    char c;
    // Next cnode
    struct cnode * next;
    // Previos cnode
    struct cnode * prev;
};

struct cnodeList {
    // Size of cnodeList
    size_t size;

    unsigned int totalLines;

    // Begining of cnodeList
    struct cnode * begin;
    // Last cnode position
    struct cnode * currentcnode;
};

/*** Functions ***/
struct cnode * createcnode(char c);
void initcnodeList(struct cnodeList * clist);
int addcnode(struct cnodeList * clist, char c);
char * getcnodeListToString(struct cnodeList * clist);
int movecnodeUp(struct cnodeList * clist);
int movecnodeDown(struct cnodeList * clist);
int movecnodeLeft(struct cnodeList * clist);
int movecnodeRight(struct cnodeList * clist);
int deletecnode(struct cnodeList * clist);
