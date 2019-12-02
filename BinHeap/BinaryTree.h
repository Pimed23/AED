#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <iostream>
#include <QDebug>

template <typename Type>
class BinaryTree{
    struct BinaryTreeNode;
    public:
        BinaryTree();
        BinaryTree(std::vector<Type> &items);
        void print(){
            traverse(root);
        }

        ~BinaryTree();

        void generarTxt(std::string& txt )const;
        void arrayTXT(std::string& txt,std::vector<Type> &items )const;
    private:
        struct BinaryTreeNode{
            BinaryTreeNode *left,*right;
            Type info;
        };

        BinaryTreeNode *root;

        void traverse (BinaryTreeNode *& T);
        void makeEmpty( BinaryTreeNode *& T ){
            if( T != nullptr ) {
                makeEmpty( T -> left );
                makeEmpty( T -> right );
                delete T;
            }
            T = nullptr;
        }

        void generarTxt( BinaryTreeNode *T , std::string &txt ) const;
};


template <typename Type>
BinaryTree<Type>::~BinaryTree(){
    makeEmpty(root);
}

template <typename Type>
BinaryTree<Type>::BinaryTree(){
    root = nullptr;
}

template <typename Type>
void BinaryTree<Type>::traverse (BinaryTree<Type>::BinaryTreeNode *& T){
    if( T != nullptr ) {
        //std::cout<<"nodo: "<< T -> info;
        if(T->left != nullptr)
            //std::cout<< " left: "<<T -> left -> info;

        if(T->right != nullptr)
            //std::cout<<" right: "<< T ->right ->info <<"\n";
        traverse( T -> left );
        traverse( T -> right );
    }
}

template <typename Type>
BinaryTree<Type>::BinaryTree(std::vector<Type> &items){
    if( items.size() != 0 ) {
        std::vector<BinaryTree<Type>::BinaryTreeNode*> nodos;
        for(size_t i = 0; i < items.size() ; ++i){
            BinaryTree<Type>::BinaryTreeNode* current = new BinaryTree<Type>::BinaryTreeNode;
            current -> info = items[i];
            nodos.push_back(current);
        }
        for(size_t i = 0; i < items.size(); ++i){
            if(i*2 + 1 < items.size()){
                nodos[i]->left = nodos[i*2 + 1];
                std::cout<< "nodo: "<<nodos[i]->info <<" left: "<< nodos[i]->left->info;
                if(i*2 + 2 < items.size()){
                    nodos[i]->right = nodos[i*2 + 2];
                    std::cout<<" right: "<<nodos[i]->right->info;
                }
                else{
                    nodos[i]->right = nullptr;
                }
                std::cout<<"\n";
            }
            else{
                nodos[i]->left = nullptr;
                nodos[i]->right = nullptr;
            }
        }
        root = nodos[0];
    } else {
        root = nullptr;
    }
}

template < typename Type >
void BinaryTree<Type>::generarTxt( std::string &txt) const {
    generarTxt( root,txt);
}

template < typename Type >
void BinaryTree<Type>::arrayTXT( std::string &txt,std::vector<Type> &items  ) const {
    txt.append("node[shape=record,fontcolor=black, fontsize=14, width=4.75, fixedsize=true];\n");
    txt.append("values[label = \" ");
    if( items.size() != 0 ) {
        size_t i;
        for(i=0;i<items.size()-1;++i)
            txt.append("<f"+std::to_string(i)+"> "+std::to_string(items[i])+" |");
        txt.append("<f"+std::to_string(i)+"> "+std::to_string(items[i])+"\"];\n");
    } else {
        txt.append("\"];\n");
    }
}

template < typename Type >
void BinaryTree<Type>::generarTxt( BinaryTree<Type>::BinaryTreeNode *T, std::string &txt ) const {
    if( T != NULL ){
        if( root->left == nullptr && root->right == nullptr) {
            txt.append("\"");
            txt.append(std::to_string(T->info));
            txt.append("\"");
            txt.append(" -> ");
            txt.append("\"");
            txt.append("NULL");
            txt.append("\"");
            txt.append("\n");
        }
        if( T -> left != NULL ){
            txt.append("\"");
            txt.append( std::to_string( T -> info ));
            txt.append("\"");
            txt.append(" -> ");
            txt.append("\"");
            txt.append( std::to_string( T -> left -> info ));
            txt.append("\"");
            txt.append("\n");
        }
        generarTxt( T -> left, txt );
        if( T -> right != NULL ){
            txt.append("\"");
            txt.append( std::to_string( T -> info ));
            txt.append("\"");
            txt.append(" -> ");
            txt.append("\"");
            txt.append( std::to_string( T -> right -> info ));
            txt.append("\"");
            txt.append("\n");
        }
        generarTxt( T -> right, txt );
    }
}

#endif // BINARYTREE_H
