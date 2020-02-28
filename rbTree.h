#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <iostream>

using namespace std;

typedef enum COLOR{
    RED,
    BLACK
}n_COLOR;

// typedef struct COLOR{
//     char color;
// }n_COLOR;

typedef struct NODE{
    NODE *parent;
    NODE *lChild;
    NODE *rChild;
    int value;
    n_COLOR color;
}* t_NODE;

const t_NODE GLOBAL_NIL;     //how to implement sentinel nil node

class rbTree{
    public:
        rbTree();
        ~rbTree();

        void insertNode(int);
        void deleteNode(int);
        void printTree(void);


    private:
        t_NODE p_Root;

        t_NODE p_CreateNode(int);
        void p_InsertNode(t_NODE);
        int p_DeleteNode(t_NODE);
        int p_SearchNode(int);
        void p_DumpTree(t_NODE, int);
        int p_LeftRotate(t_NODE);
        int p_RightRotate(t_NODE);




};

#endif