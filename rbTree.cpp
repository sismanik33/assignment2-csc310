#include <iomanip>
#include <rbTree.h>
#include <myException.h>



/**************************** PUBLIC: Constructor ****************************/
rbTree::rbTree(){
    GLOBAL_NIL->value = NULL;
    GLOBAL_NIL->lChild = NULL;
    GLOBAL_NIL->rChild = NULL;
    GLOBAL_NIL->color = BLACK;
    p_Root = GLOBAL_NIL;
}

/**************************** PUBLIC: Destructor ****************************/
rbTree::~rbTree(){

}

/**************************** PUBLIC: insertNode ****************************/
void rbTree::insertNode(int valueToInsert){
    t_NODE nodeToInsert = NULL;
    
    try {
        t_NODE nodeToInsert = p_CreateNode(valueToInsert); 
    } catch(MyException &exc) {
        std::cerr << exc.what() << '\n';
    }

    try {
        p_InsertNode(nodeToInsert);
    } catch(MyException &exc) {
        std::cerr << exc.what() << '\n';
    }
    
}


/**************************** PRIVATE: p_CreateNode ****************************/
t_NODE rbTree::p_CreateNode(int nodeValue){

    //if value already in tree or <= 0 do not create
    if (nodeValue <= 0)
        throw MyException("Node values must be greater than 0", WARNING);

    t_NODE newNode = NULL;

    try {
        t_NODE newNode = new NODE;
        newNode->value = nodeValue;
        newNode->lChild = GLOBAL_NIL;
        newNode->rChild = GLOBAL_NIL;
        newNode->color = RED;
    } catch(bad_alloc &exc) {
        cerr<<"bad_alloc has occurred!\n";
        string exceptionStr = string("p_CreateNode: ") + exc.what();
        throw MyException(exceptionStr, SYSTEM_FAILURE);
    } catch(exception &exc){
        string exceptionStr = string("General failure (p_CreateNode): ") + exc.what();
        throw MyException(exceptionStr, SYSTEM_FAILURE);
    }
     
    return newNode;
    
}

/**************************** PRIVATE: p_InsertNode ****************************/
void rbTree::p_InsertNode(t_NODE nodeToInsert){
    t_NODE walker = nullptr;
    t_NODE walkerParent = nullptr;

    if (p_Root == NULL){
        try {
            nodeToInsert->parent = NULL;
            nodeToInsert->color = BLACK;
            p_Root = nodeToInsert;
            return; 
        } catch(exception &exc) {
            throw MyException("Error inserting node (p_InsertNode)", ERROR);
        }
    } else {
        walker = p_Root;
        
        while(walker != GLOBAL_NIL){
            walkerParent = walker;
            if (nodeToInsert->value < walker->value){
                walker = walker->lChild;
            } else {
                walker = walker->rChild;
            }
        }

        nodeToInsert->parent = walkerParent;
    }

    
    
    

}


/************************* PRIVATE: p_DumpTree *************************/
void rbTree::p_DumpTree(t_NODE node, int indent){
    if( NULL == node ){
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