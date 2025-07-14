#pragma once
#include <iostream>
using namespace std;

template <typename T>
class SentinelLinkedList
{
private:
    // Nodo interno para la lista doblemente ligada
    template <typename U>
    class Node
    {
    public:
        Node()
        {
            prev = nullptr; // puntero al nodo anterior (ninguno aún)
            next = nullptr; // puntero al siguiente nodo (ninguno aún)
        }

        Node(U value)
        {
            data = value;   // guardamos el valor que trae el nodo
            prev = nullptr; // sin enlaces todavía
            next = nullptr;
        }

        U data;           // dato que guarda el nodo (de tipo U)
        Node<U>* next;    // puntero al siguiente nodo
        Node<U>* prev;    // puntero al nodo anterior
    };

private:
    Node<T>* NIL; // nodo centinela para simplificar las operaciones (lista circular)
    int count;    // contador de elementos en la lista

public:
    SentinelLinkedList()
    {
        count = 0;
        NIL = new Node<T>(); // creamos el nodo centinela
        NIL->next = NIL;     // inicialmente apunta a sí mismo
        NIL->prev = NIL;
    }

    ~SentinelLinkedList()
    {
        // liberar memoria de todos los nodos excepto el centinela
        Node<T>* current = NIL->next;
        while (current != NIL)
        {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        delete NIL; // liberar el nodo centinela
    }

    // Devuelve la cantidad de elementos en la lista
    int GetCount() { return count; }

    // Agrega un nodo con el valor al final de la lista
    void PushBack(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = NIL;           // siguiente es el centinela
        newNode->prev = NIL->prev;     // anterior es el último nodo actual
        NIL->prev->next = newNode;     // el antiguo último apunta al nuevo
        NIL->prev = newNode;           // el centinela apunta al nuevo como último
        count++;
    }

    // Quita el nodo del final y devuelve su valor
    T PopBack()
    {
        if (count == 0)
        {
            cout << "Advertencia: PopBack en lista vacia" << endl;
            return {}; // devuelve valor por defecto
        }
        Node<T>* lastNode = NIL->prev;      // obtiene el último nodo
        T value = lastNode->data;            // guarda su valor

        lastNode->prev->next = NIL;          // el penúltimo apunta al centinela
        NIL->prev = lastNode->prev;          // centinela apunta al penúltimo

        delete lastNode;                     // elimina el nodo
        count--;
        return value;                       // regresa el valor eliminado
    }

    // Devuelve el valor del primer nodo sin quitarlo
    T Front()
    {
        if (count == 0)
        {
            cout << "Advertencia: Front en lista vacia" << endl;
            return {};
        }
        return NIL->next->data; // valor del primer nodo después del centinela
    }

    //  Agrega un nodo al inicio de la lista
    void PushFront(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = NIL->next;   // el nuevo apunta al que antes era primero
        newNode->prev = NIL;          // el anterior es el centinela

        NIL->next->prev = newNode;   // el antiguo primer nodo apunta atrás al nuevo
        NIL->next = newNode;          // centinela apunta al nuevo como primero

        count++;
    }

    // Quita el nodo del inicio y devuelve su valor
    T PopFront()
    {
        if (count == 0)
        {
            cout << "Advertencia: PopFront en lista vacia" << endl;
            return {};
        }

        Node<T>* firstNode = NIL->next;    // nodo primero actual
        T value = firstNode->data;          // guarda su valor

        NIL->next = firstNode->next;        // centinela apunta al siguiente
        firstNode->next->prev = NIL;        // nuevo primero apunta atrás al centinela

        delete firstNode;                   // elimina nodo viejo
        count--;
        return value;                      // regresa valor quitado
    }
};
