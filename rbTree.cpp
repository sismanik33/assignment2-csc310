#include <iomanip>
#include <rbTree.h>
#include <myException.h>



/**************************** PUBLIC: Constructor ****************************/
rbTree::rbTree(){
    GLOBAL_NIL = new NODE;  

    GLOBAL_NIL->value = -1;
    GLOBAL_NIL->lChild = nullptr;
    GLOBAL_NIL->rChild = nullptr;
    GLOBAL_NIL->color = BLACK;
    p_Root = GLOBAL_NIL;
}

/**************************** PUBLIC: Destructor ****************************/
rbTree::~rbTree(){
    try {
        p_DeleteTree();
        delete GLOBAL_NIL;
    } catch(MyException &exc) {
        cerr << exc.what() << '\n';
    }
}

/**************************** PUBLIC: insertNode ****************************/
void rbTree::insertNode(int nodeValue){
    t_NODE nodeToInsert = NULL;
    
    try {
        p_SearchExcWhenPresent(p_GetRoot(), nodeValue);
        t_NODE nodeToInsert = p_CreateNode(nodeValue);
        p_InsertNode(nodeToInsert);
    } catch(MyException &exc) {
        cerr << exc.what() << '\n';
    }
    
}

/**************************** PUBLIC: printTree ****************************/
void rbTree::printTree(void){
    try {
        t_NODE root = NULL;
        root = p_GetRoot(); 
        p_DumpTree(root, 1); 
        // p_InOrderPrint(root);
    } catch(MyException &exc) {
        cerr << exc.what() << '\n';
    }
}

/**************************** PUBLIC: searchNode ****************************/
void rbTree::searchNode(int key){
   try {
        p_SearchExcWhenAbsent(p_GetRoot(), key);
        cout<<key<<" found in tree."<<endl;
    } catch(MyException &exc) {
        cerr << exc.what() << '\n';
    } 
}
    
/**************************** PUBLIC: deleteNode ****************************/
void rbTree::deleteNode(int valueToDelete){
    try {
        p_SearchExcWhenAbsent(p_GetRoot(), valueToDelete);
        t_NODE nodeToDelete = p_GetNode(p_GetRoot(), valueToDelete);
        p_DeleteNode(nodeToDelete);
    } catch(MyException &exc) {
        cerr << exc.what() << '\n';
    }
}

/**************************** PUBLIC: deleteTree ****************************/
void rbTree::deleteTree(void){
    try{
        p_DeleteTree();
    }catch(MyException &exc){
        cerr<<exc.what()<<endl;
    }   
}


/**************************** PRIVATE: p_GetRoot ****************************/
t_NODE rbTree::p_GetRoot(void){
    return p_Root;
}


/**************************** PRIVATE: p_CreateNode ****************************/
t_NODE rbTree::p_CreateNode(int nodeValue){

    //if value already in tree or <= 0 do not create
    if (nodeValue <= 0){
        throw MyException("Node values must be greater than 0", WARNING);
    }

    t_NODE newNode = NULL;

    try {
        t_NODE newNode = new NODE;
        newNode->value = nodeValue;
        newNode->lChild = GLOBAL_NIL;
        newNode->rChild = GLOBAL_NIL;
        newNode->color = RED;
        
        return newNode;
    } catch(bad_alloc &exc) {
        string exceptionStr = string("p_CreateNode(bad_alloc): ") + exc.what();
        throw MyException(exceptionStr, SYSTEM_FAILURE);
    } catch(exception &exc){
        string exceptionStr = string("General failure (p_CreateNode): ") + exc.what();
        throw MyException(exceptionStr, SYSTEM_FAILURE);
    }
    
}

/**************************** PRIVATE: p_InsertNode ****************************/
void rbTree::p_InsertNode(t_NODE nodeToInsert){
    try {
        t_NODE follower = GLOBAL_NIL;
        t_NODE walker = p_Root;

        while ( walker != GLOBAL_NIL){
        follower = walker;
            if (nodeToInsert->value < walker->value){
                walker = walker->lChild;
            } else{
                walker = walker->rChild;
            }
        }
        nodeToInsert->parent = follower;

        if(follower == GLOBAL_NIL){
            p_Root = nodeToInsert;
        } else if (nodeToInsert->value < follower->value){
            follower->lChild = nodeToInsert;
        } else {
            follower->rChild = nodeToInsert;
        } 

        p_InsertHelper(nodeToInsert);
    } catch(exception &exc) {
        throw MyException("Problem encountered during execution of p_InsertNode", WARNING);
    }

}

/**************************** PRIVATE: p_InsertHelper ****************************/
void rbTree::p_InsertHelper(t_NODE newChild){
    while (newChild->parent->color == RED){
        if (newChild->parent == newChild->parent->parent->lChild){
            t_NODE uncleNode = newChild->parent->parent->rChild;
            if (uncleNode->color == RED){
                newChild->parent->color = BLACK;
                uncleNode->color = BLACK;
                newChild->parent->parent->color = RED;
                newChild = newChild->parent->parent;
            } else{ 
                if (newChild == newChild->parent->rChild){
                newChild = newChild->parent;
                p_LeftRotate(newChild);
                }
            newChild->parent->color = BLACK;
            newChild->parent->parent->color = RED;
            p_RightRotate(newChild->parent->parent);
            }
        } else{
            t_NODE uncleNode = newChild->parent->parent->lChild;
            if (uncleNode->color == RED){
                newChild->parent->color = BLACK;
                uncleNode->color = BLACK;
                newChild->parent->parent->color = RED;
                newChild = newChild->parent->parent;
            } else {
                if (newChild == newChild->parent->lChild){
                newChild = newChild->parent;
                p_RightRotate(newChild);
                } 
            newChild->parent->color = BLACK;
            newChild->parent->parent->color = RED;
            p_LeftRotate(newChild->parent->parent);
            }
        }
    }
    p_Root->color = BLACK;
}


/**************************** PRIVATE: p_LeftRotate ****************************/
int rbTree::p_LeftRotate(t_NODE x){
    try {
        t_NODE y = x->rChild;
        x->rChild = y->lChild;
        if(y->lChild != GLOBAL_NIL){
            y->lChild->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == GLOBAL_NIL){
            p_Root = y;
        } else if (x == x->parent->lChild){
            x->parent->lChild = y;
        } else {
            x->parent->rChild = y;
        }
        y->lChild = x;
        x->parent = y;        
    } catch(exception &exc) {
        throw MyException("Error during execution of p_LeftRotate", WARNING);
    }
}

/**************************** PRIVATE: p_RightRotate ****************************/
int rbTree::p_RightRotate(t_NODE x){
    try {
        t_NODE y = x->lChild;
        x->lChild = y->rChild;
        if(y->rChild != GLOBAL_NIL){
            y->rChild->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == GLOBAL_NIL){
            p_Root = y;
        } else if (x == x->parent->rChild){
            x->parent->rChild = y;
        } else {
            x->parent->lChild = y;
        }
        y->rChild = x;
        x->parent = y;
        } catch(exception &exc) {
       throw MyException("Error during execution of p_RightRotate", WARNING);
    }
}

/************************* PRIVATE: p_DumpTree *************************/
void rbTree::p_DumpTree(t_NODE node, int indent){
    if( GLOBAL_NIL == node ){
        return;
    } else {
        this->p_DumpTree(node->lChild, indent+4);
        if( -1 != node->value ){
            if( indent ){
                cout<<setw(indent)<<" ";
            }
            cout<<node->value<<": ";
            if( BLACK == node->color ){
                cout<<"BLACK"<<endl;
            } else {
                cout<<"RED"<<endl;
            }
        }
        this->p_DumpTree(node->rChild, indent+4);
    }
}

/**************************** PRIVATE: p_InOrderPrint ****************************/
void rbTree::p_InOrderPrint(t_NODE node){
    if(node != GLOBAL_NIL){
        p_InOrderPrint(node->lChild);
        cout<<node->value<<"."<<node->color<<" - ";
        p_InOrderPrint(node->rChild);
    }
}

/**************************** PRIVATE: p_SearchExcWhenAbsent ****************************/
void rbTree::p_SearchExcWhenAbsent(t_NODE root, int key){
    if (root == GLOBAL_NIL || root->value == key){
    if(root->value == key){
        return;
    } else {
        throw MyException("Node with value " + to_string(key) + " not present in tree.", WARNING);
    }
    }
    if (key < root->value){
        return p_SearchExcWhenAbsent(root->lChild, key);
    } else{
        return p_SearchExcWhenAbsent(root->rChild, key);
    }
}

/**************************** PRIVATE: p_SearchExcWhenPresent ****************************/
void rbTree::p_SearchExcWhenPresent(t_NODE root, int key){
    if (root == GLOBAL_NIL || root->value == key){
        if(root->value == key){
            throw MyException("Node with value " + to_string(key) + " already present in tree.", WARNING);
        } else {
            return;
        }
    }
    if (key < root->value){
        return p_SearchExcWhenPresent(root->lChild, key);
    } else{
        return p_SearchExcWhenPresent(root->rChild, key);
    }
}

/**************************** PRIVATE: p_GetNode ****************************/
t_NODE rbTree::p_GetNode(t_NODE root, int key){
    if(root == GLOBAL_NIL || root->value == key){
        if (root->value == key){
            return root;
        } else {
            throw MyException("Node with value " + to_string(key) + " not in tree.", WARNING);
        }
    }
    if (key < root->value){
        return p_GetNode(root->lChild, key);
    } else {
        return p_GetNode(root->rChild, key);
    }
}

/**************************** PRIVATE: p_Predecessor ****************************/
t_NODE rbTree::p_GetPredecessor(t_NODE predecessor){
    while (predecessor->lChild != GLOBAL_NIL) {
        predecessor = predecessor->lChild;
    }
    return predecessor;
}

/**************************** PRIVATE: p_DeleteNode ****************************/
void rbTree::p_DeleteNode(t_NODE z){
    t_NODE y = z;
    t_NODE x;
    n_COLOR yOriginalColor = y->color;
    if(z->lChild == GLOBAL_NIL){
        x = z->rChild;
        p_Transplant(z, z->rChild);
    } else if (z->rChild == GLOBAL_NIL){
        x = z->lChild;
        p_Transplant(z, z->lChild);
    } else{
        y = p_GetPredecessor(z->rChild);
        yOriginalColor = y->color;
        x = y->rChild;
        if(y->parent == z){
            x->parent = y;
        } else{
            p_Transplant(y, y->rChild);
            y->rChild = z->rChild;
            y->rChild->parent = y;
        }
        p_Transplant(z, y);
        y->lChild = z->lChild;
        y->lChild->parent = y;
        y->color = z->color;
    }
    if(yOriginalColor == BLACK){
        p_DeleteHelper(x);
    }
    delete z;
}

/**************************** PRIVATE: p_Transplant ****************************/
void rbTree::p_Transplant(t_NODE u, t_NODE v){
    if(u->parent == GLOBAL_NIL){
        p_Root = v;
    } else if (u == u->parent->lChild){
        u->parent->lChild = v;
    } else{
        u->parent->rChild = v;
    }
    v->parent = u->parent;
}

/**************************** PRIVATE: p_DeleteHelper ****************************/
void rbTree::p_DeleteHelper(t_NODE x){
    t_NODE w;
    while (x != p_Root && x->color == BLACK) {
        if (x == x->parent->lChild){
            w = x->parent->rChild;
            if (w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                p_LeftRotate(x->parent);
                w = x->parent->rChild;
            }
            if (w->lChild->color == BLACK && w->rChild->color == BLACK){
                w->color = RED;
                x = x->parent;
            } else {
                if (w->rChild->color == BLACK){
                    w->lChild->color = BLACK;
                    w->color = RED;
                    p_RightRotate(w);
                    w = x->parent->rChild;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->rChild->color = BLACK;
                p_LeftRotate(x->parent);
                x = p_Root;
            }
        } else {
            w = x->parent->lChild;
            if (w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                p_RightRotate(x->parent);
                w = x->parent->lChild;
            }
            if (w->rChild->color == BLACK && w->lChild->color == BLACK){
                w->color = RED;
                x = x->parent;
            } else {
                if (w->lChild->color == BLACK){
                    w->rChild->color = BLACK;
                    w->color = RED;
                    p_LeftRotate(w);
                    w = x->parent->lChild;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->lChild->color = BLACK;
                p_RightRotate(x->parent);
                x = p_Root;
            }
        }
    }
    x->color = BLACK;
}

/**************************** PRIVATE: p_DeleteTree ****************************/
void rbTree::p_DeleteTree(void){
    int count = 1;
    try {
        while (p_Root != GLOBAL_NIL){
        cout<<"****"<<count<<"****"<<endl<<endl;
        p_DeleteNode(p_Root);
        p_DumpTree(p_Root, 1);
        cout<<endl;
        count++;
    } 
    } catch(exception &exc) {
        throw MyException("Error during execution of p_DeleteTree. " + string(exc.what()), WARNING);
    }
}