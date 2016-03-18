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

#include <cmath>

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
        node* left;
        node* right;
        
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
     *  @param root raiz
     *  @param inq  valor del nodo
     *
     *  @return verdadero o falso si el valor se encuentra en el AB
     */
    bool lookup(node *&root, int val) {
        if (root == NULL) return false;
        
        if (root->data == val) return true;
        else if (val < root->data) return lookup(root->left, val);
        else return lookup(root->right, val);
    }
    
    /**
     *  Agrega nuevo nodo al AB
     *
     *  @param root raiz
     *  @param val  valor a insertar
     */
    void add(node *&root, int val) {
        if (root == NULL) root = new node(val);
        else if (val < root->data) add(root->left, val);
        else add(root->right, val);
    }
    
    /**
     *  Elimina un nodo del AB
     *
     *  @param root raiz
     *  @param val  valor del nodo
     */
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
    
    /**
     *  Compara dos enteros
     *
     *  @param a base
     *  @param b valor
     *
     *  @return retorna argumento superior
     */
    int max(int a, int b) { return (a >= b) ? a: b; }
    
    /**
     *  Tamano del AB
     *
     *  @param root raiz
     *
     *  @return tamano total del AB
     */
    int size(node *&root) {
        if (root == NULL) return (0);
        return 1 + (size(root->left) + size(root->right));
    }
    
    /**
     *  Numero de nodos desde la raiz hasta la hoja mas lejana
     *
     *  @param root raiz
     *
     *  @return profundidad(o nivel)
     */
    int depth(node *&root) {
        if (root == NULL) return (0);
        else {
            return 1 + max(depth(root->left), depth(root->right));
        }
    }
    
    /**
     *  Calcula la altura del AB
     *
     *  @param root raiz
     *
     *  @return altura del AB
     */
    int height(node *&root) { return (depth(root) -1); }
    
    /**
     *  Determina si AB balanceado
     *
     *  @param root raiz
     *
     *  @return verdadero si AB es balanceado
     */
    bool balanced(node *&root) {
        if (root == NULL) return 1;
        else if (abs(depth(root->left) - depth(root->right)) <= 1 &&
                 balanced(root->left) &&
                 balanced(root->right))
            return 1;
        else
            return 0;
    }
    
    /**
     *  Imprimir a consola el recorrido de AB
     *
     *  @param root raiz
     *  @param trav tipo de recorrido
     */
    void traversal(node *&root, Traversals trav) {
        switch (trav) {
            case PRE_ORDER:
                /**
                 *  Recorrido pre-orden recorre,
                 *  1. Raiz
                 *  2. Subarboles izquierdos
                 *  3. Subarboles derechos
                 */
                if (root != NULL) {
                    std::cout << root->data << " ";
                    traversal(root->left, PRE_ORDER);
                    traversal(root->right, PRE_ORDER);
                }
                break;
                
            case POST_ORDER:
                /**
                 *  Recorrido pos-orden recorre,
                 *  1. Subarboles izquierdos
                 *  2. Subarboles derechos
                 *  3. Raiz
                 */
                if (root != NULL) {
                    traversal(root->left, POST_ORDER);
                    traversal(root->right, POST_ORDER);
                    std::cout << root->data << " ";
                }
                break;
                
            case IN_ORDER:
                /**
                 *  Recorrido pos-orden recorre,
                 *  1. Subarboles izquierdos
                 *  2. Raiz
                 *  3. Subarboles derechos
                 */
                if (root != NULL) {
                    traversal(root->left, IN_ORDER);
                    std::cout << root->data << " ";
                    traversal(root->right, IN_ORDER);
                }
                break;
                
            default:
                break;
        }
    }
}

int main(int argc, const char * argv[]) {
    ibtree::node* root;
    
    root = NULL; // init
    
// BST
    ibtree::add(root, 8);
    ibtree::add(root, 3);
    ibtree::add(root, 10);
    ibtree::add(root, 1);
    ibtree::add(root, 6);
    ibtree::add(root, 14);
    ibtree::add(root, 4);
    ibtree::add(root, 7);
    ibtree::add(root, 13);
    
// AVL
//    ibtree::add(root, 50);
//    ibtree::add(root, 17);
//    ibtree::add(root, 72);
//    ibtree::add(root, 12);
//    ibtree::add(root, 23);
//    ibtree::add(root, 54);
//    ibtree::add(root, 76);
//    ibtree::add(root, 9);
//    ibtree::add(root, 14);
//    ibtree::add(root, 19);
//    ibtree::add(root, 67);

// BST - Eliminar nodo
//    ibtree::add(root, 5);
//    ibtree::add(root, 2);
//    ibtree::add(root, 12);
//    ibtree::add(root, -4);
//    ibtree::add(root, 3);
//    ibtree::add(root, 9);
//    ibtree::add(root, 21);
//    ibtree::add(root, 19);
//    ibtree::add(root, 25);
//    // Eliminar nodo (12)
//    ibtree::del(root, 12);
    
// BST - Busquedar nodo
    std::cout << "Existe el nodo 12? - " << ibtree::lookup(root, 12) << std::endl;
    std::cout << "Tamano del AB. -" << ibtree::size(root) << std::endl;
    std::cout << "Profundidad, o nivel, del AB. - " << ibtree::depth(root) << std::endl;
    std::cout << "Altura del AB. - " << ibtree::height(root) << std::endl;
    std::cout << "Es un AB balanceado? - " << ibtree::balanced(root) << std::endl;
    
    std::cout << "\n";

    std::cout << "Recorrido \"pre-ordenado\" - "; ibtree::traversal(root, ibtree::PRE_ORDER); std::cout << "\n";
    std::cout << "Recorrido \"en-ordenado\" - "; ibtree::traversal(root, ibtree::IN_ORDER); std::cout << "\n";
    std::cout << "Recorrido \"post-ordenado\" - "; ibtree::traversal(root, ibtree::POST_ORDER);
    
    std::cout << "\n\n";
    
    return 0;
}
