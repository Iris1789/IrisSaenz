#pragma once
#include <iostream>
#include <stack>  // Para recorridos iterativos
#include <queue>  // Para posibles recorridos 
#include <stdexcept>  // Para manejo de excepciones
using namespace std;

template <typename T>
class BinarySearchTree {
private:
    // Clase interna para los nodos del árbol
    template <typename U>
    class TreeNode {
    public:
        U data;               // Valor almacenado en el nodo
        TreeNode<U>* parent;  // Puntero al nodo padre
        TreeNode<U>* leftChild;   // Puntero al hijo izquierdo
        TreeNode<U>* rightChild;  // Puntero al hijo derecho

        // crea un nodo con un valor, sin hijos y sin padre
        TreeNode(U val) : data(val), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
    };

    TreeNode<T>* root;  // Puntero
    int count;          // Contador de nodos en el árbol

public:
    // Crea un árbol vacío
    BinarySearchTree() : root(nullptr), count(0) {}

    // Limpia toda la memoria usada por el árbol
    ~BinarySearchTree() {
        Clear();
    }

    // Añade un nuevo valor al árbol 
    void Add(T value) {
        // Si el árbol está vacío crea la raíz
        if (root == nullptr) {
            root = new TreeNode<T>(value);
            count++;
            return;
        }

        TreeNode<T>* currentNode = root;
        while (true) {
            // Si el valor es menor va a la izquierda
            if (value < currentNode->data) {
                if (currentNode->leftChild == nullptr) {
                    currentNode->leftChild = new TreeNode<T>(value);
                    currentNode->leftChild->parent = currentNode;
                    count++;
                    return;
                }
                currentNode = currentNode->leftChild;
            }
            // Si el valor es mayor va a la derecha
            else if (value > currentNode->data) {
                if (currentNode->rightChild == nullptr) {
                    currentNode->rightChild = new TreeNode<T>(value);
                    currentNode->rightChild->parent = currentNode;
                    count++;
                    return;
                }
                currentNode = currentNode->rightChild;
            }
            // Si el valor ya existe no hace nada
            else {
                return;
            }
        }
    }

    // Busca un valor en el árbol 
    bool Search(T value) {
        TreeNode<T>* currentNode = root;

        // Recorre el árbol desde la raíz
        while (currentNode != nullptr) {
            // Si encuentra el valor es true
            if (value == currentNode->data) {
                return true;
            }
            // Si el valor es menor, busca en el izquierdo
            else if (value < currentNode->data) {
                currentNode = currentNode->leftChild;
            }
            // Si el valor es mayor, busca en el derecho
            else {
                currentNode = currentNode->rightChild;
            }
        }
        // El valor no está en el árbol
        return false;
    }

    // Elimina un nodo con el valor especificado
    bool Remove(T value) {
        TreeNode<T>* currentNode = root;
        TreeNode<T>* parentNode = nullptr;

        // Primero busca el nodo a eliminar
        while (currentNode != nullptr && currentNode->data != value) {
            parentNode = currentNode;
            if (value < currentNode->data) {
                currentNode = currentNode->leftChild;
            }
            else {
                currentNode = currentNode->rightChild;
            }
        }

        // Si no encuentra el nodo es false
        if (currentNode == nullptr) {
            return false;
        }

        // Nodo sin hijos 
        if (currentNode->leftChild == nullptr && currentNode->rightChild == nullptr) {
            if (parentNode == nullptr) {
                root = nullptr;  //El único nodo del árbol
            }
            else if (parentNode->leftChild == currentNode) {
                parentNode->leftChild = nullptr;
            }
            else {
                parentNode->rightChild = nullptr;
            }
            delete currentNode;
        }
        // Nodo con un solo hijo
        else if (currentNode->leftChild == nullptr || currentNode->rightChild == nullptr) {
            TreeNode<T>* child = (currentNode->leftChild != nullptr) ? currentNode->leftChild : currentNode->rightChild;

            if (parentNode == nullptr) {
                root = child;  // Elimina la raíz
            }
            else if (parentNode->leftChild == currentNode) {
                parentNode->leftChild = child;
            }
            else {
                parentNode->rightChild = child;
            }
            child->parent = parentNode;
            delete currentNode;
        }
        // Nodo con dos hijos
        else {
            // Encuentra el sucesor inmediato 
            TreeNode<T>* successor = currentNode->rightChild;
            while (successor->leftChild != nullptr) {
                successor = successor->leftChild;
            }

            // Copia el valor del sucesor al nodo actual
            T successorValue = successor->data;
            // Elimina el sucesor 
            Remove(successorValue);
            // Reemplaza el valor del nodo actual
            currentNode->data = successorValue;
        }

        count--;
        return true;
    }

    // Elimina todos los nodos del árbol
    void Clear() {
        DeleteTreeRecursive(root);
        root = nullptr;
        count = 0;
    }

    // Recorrido usando dos pilas
    void PostOrderIterative() {
        // Si el árbol está vacío, no se hace nada
        if (root == nullptr) return;

        // Crea dos pilas para el procesamiento
        stack<TreeNode<T>*> s1, s2;

        // Empujamos la raíz a la primera pila
        s1.push(root);

        // Mientras haya nodos en la primera pila
        while (!s1.empty()) {
            // Sacamos un nodo 
            TreeNode<T>* node = s1.top();
            s1.pop();
            // se mueve o empuja 
            s2.push(node);

            // Empujamos los hijos izquierdo y derecho 
            if (node->leftChild) s1.push(node->leftChild);
            if (node->rightChild) s1.push(node->rightChild);
        }

        // Imprimimos los nodos en orden
        cout << "Recorrido Post-Orden: ";
        while (!s2.empty()) {
            TreeNode<T>* node = s2.top();
            s2.pop();
            cout << node->data << " ";
        }
        cout << endl;
    }

private:
    // Función para eliminar el árbol
    void DeleteTreeRecursive(TreeNode<T>* node) {
        // Si el nodo existe
        if (node != nullptr) {
            // Primero elimina los hijos 
            DeleteTreeRecursive(node->leftChild);
            DeleteTreeRecursive(node->rightChild);
            // Luego elimina el nodo actual
            delete node;
        }
    }
};