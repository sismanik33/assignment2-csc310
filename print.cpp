/************************* PRIVATE: p_DumpTree *************************/
void rbTree::p_DumpTree(t_node *node, int indent){
    if( NULL == node ){
        return;
    } else {
        this->p_DumpTree(node->LChild, indent+4);
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
        this->p_DumpTree(node->RChild, indent+4);
    }
}