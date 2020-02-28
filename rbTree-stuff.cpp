#include <iostream>

using namespace std;

struct myNode{
    myNode *parent;
    myNode *lchild;
    myNode *rchild;
    int value;
    //color
};

const struct myNode GLOBAL_NIL;     //how to implement sentinel nil node


/*
    make files
    exception handling
    quickUnion
    DSW algo
    RB trees
    
*/