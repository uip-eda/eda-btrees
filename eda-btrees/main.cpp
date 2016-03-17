/**
 The MIT License (MIT)
 Copyright (c) 2016, Universidad Interamericana de Panama
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 -- The Authors
 
 Zahir Gudiño
 Luis Martinez
 Adriel Velásquez
 Mauricio Zuñiga
 Aldemar Perea
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

/**
 *  Arbol Binario (AB) de Tipo de Datos Enteros
 */
namespace ibtree {
    enum Traversals { PRE_ORDER, POST_ORDER, IN_ORDER };
    /**
     *  Nodo
     */
    struct node {
        int data;
        node* left; // ptr izq
        node* right; // ptr der
        // Constructores
        node(int d): data(d), left(NULL), right(NULL) {}
        node(void): data(NULL), left(NULL), right(NULL) {}
    };
    
    /**
     *  Recorre el AB por el nodo con el valor mas minimo
     *
     *  @param parent nodo padre
     *
     *  @return retorna el nodo u hoja con el valor mas minimo en el AB
     */
    struct node *min_v(node *&parent) {
        struct node *current = parent;
        
        if (current->left == NULL)
            return current;
        else
            return min_v(current->left);
    }
    
    /**
     *  Recorre el AB por si el valor incognito esta existe
     *
     *  @param root raiz del AB
     *  @param inq  incognita a buscar en AB
     *
     *  @return verdadero o falso si el valor se encuentra en el AB
     */
    bool lookup(node *&root, int inq) {
        if (root == NULL) return false;
        
        if (root->data == inq) return true;
        else if (inq < root->data) return lookup(root->left, inq);
        else return lookup(root->right, inq);
    }
    
    void add(node *&root, int val) {
        if (root == NULL) root = new node(val);
        else if (val < root->data) add(root->left, val);
        else add(root->right, val);
    }
    
    void del(node *&root, int val) {
        if (root == NULL) return;
        else if (val < root->data) return del(root->left, val);
        else if (val > root->data) return del(root->right, val);
        else {
            if (root->left == NULL && root->right == NULL) root = NULL;
            else {
                struct node *swap = min_v(root->right);
                root->data = swap->data;
                
                del(root->right, swap->data);
            }
        }
    }
    
    void clio(node *&root, Traversals trav) {
        switch (trav) {
            case PRE_ORDER:
                if (root != NULL) {
                    std::cout << root->data << " ";
                    clio(root->left, PRE_ORDER);
                    clio(root->right, PRE_ORDER);
                }
                break;
                
            default:
                break;
        }
    }
}

int main(int argc, const char * argv[]) {
    ibtree::node* root;
    
    root = NULL;
    // Agregar nodos/hojas
    ibtree::add(root, 8);
    ibtree::add(root, 3);
    ibtree::add(root, 2);
    ibtree::add(root, 5);
    ibtree::add(root, 4);
    ibtree::add(root, 9);
    ibtree::add(root, 12);
    ibtree::add(root, 11);
    ibtree::add(root, 0);
    ibtree::add(root, 22);
    ibtree::add(root, 25);
    ibtree::add(root, 10);
    ibtree::add(root, 13);
    // Eliminar nodo/hoja
    ibtree::del(root, 12);
    
    ibtree::lookup(root, 12);
    
    // Imprimir el nodo con valor minimo en todo el AB
    std::cout << "Valor minimo: " << ibtree::min_v(root)->data << std::endl;
    std::cout << "Recorrido pre-ordenado: "; ibtree::clio(root, ibtree::PRE_ORDER);
    
    
    std::cout << "\n\n";
    
    //    ibtree::cout_inorder(root);
    //    ibtree::inordcol(root)
    
    
    
    return 0;
}
