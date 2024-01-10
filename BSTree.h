#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
       BSNode<T>* root;
       
    public:
        BSTree(){
            nelem = 0;
            root = nullptr;
        }
        int size() const {
            return nelem;

        }

        T search(T e) const {
            BSNode<T>* nodo = search(root, e);
            return nodo->elem;
        }
        T operator[](T e) const {
            return search(e);
        }
        
        friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
            bst.print_inorden(out, bst.root);
            return out;
        }
        void insert(T e){
           root = insert(root, e);
        }
        void remove(T e) {
            root = remove(root, e);
        }
        ~BSTree() {
            delete_cascade(root);
        }
       
    private:
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                throw std::runtime_error("No esta el elemento :c ");
                return nullptr;
            }
            else if (n->elem > e) {
                return search(n->left, e);
            }
            else if (n->elem < e) {
                return search(n->right, e);
            }
            return n;
        }

        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                nelem++;
                return new BSNode<T>(e);
            }else if (n->elem == e) {
                throw std::runtime_error("El elemento ya se esta dentro del arbol");
            }else if (n->elem < e) {
                n->right = insert(n->right, e);
            }else if (n->elem > e) {
                n->left = insert(n->left, e);}
            return n;
        }

        BSNode<T>* remove(BSNode<T>* n, T e) {
         if (n == nullptr) {
          throw std::runtime_error("No se encuentra en el arbol");
         }else if (n->elem < e) {
             n->right = remove(n->right, e);
         }else if (n->elem > e ) {
             n->left = remove(n->left, e);     
         }else{

              if (n->left != nullptr && n->right != nullptr) {
                n->elem = max(n->left);
                n->left = remove_max(n->left);}
              else{
                 if(n->left != nullptr) {
                     n = n->left;}
                 else{
                    n = n->right;
                 }
                nelem--;}
            }
         return n;}

        void print_inorden(std::ostream& out, BSNode<T>* n)const {

            if (n != nullptr) {
                print_inorden(out, n->left);
                out << " " << n->elem << " ";
                print_inorden(out, n->right);
            }

        }
        void delete_cascade(BSNode<T>* n) {
            if (n == nullptr) {
            }
            else if (n->left != nullptr && n->right != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
            }
            else if (n->left == nullptr && n->right != nullptr) {
                delete_cascade(n->right);
            }
            else if (n->left != nullptr && n->right == nullptr) {
                delete_cascade(n->left);
            }
            nelem--;
            return delete n;
        }
        T max(BSNode<T>* n)const {
            if (n == nullptr) {
                throw std::runtime_error("El elemento no se encuentra");
            }
            else if (n->right != nullptr) {
                return max(n->right);

            }
            return n->elem;
        }

        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                BSNode<T>* aux = n->left;
                delete n;
                nelem--;
                return aux;
            }
            n->right = remove_max(n->right);
            return n;
        }
         
        
        
    
};

#endif
