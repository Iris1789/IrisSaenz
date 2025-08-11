#pragma once
#include <iostream>
#include <forward_list>
#include <string>
using namespace std;

template <typename T>
class HashTableChaining {
private:
    forward_list<T>* data;  // Arreglo de listas enlazadas
    unsigned int arraySize; // Tamaño de la tabla hash

public:
    HashTableChaining(unsigned int size) {
        data = new forward_list<T>[size];
        arraySize = size;
    }

    ~HashTableChaining() {
        delete[] data;  // Liberar memoria del arreglo
    }

    // Función hash simple: módulo del tamaño
    int HashFunction(T key) {
        return key % arraySize;
    }

    void Add(T element) {
        int index = HashFunction(element);
        data[index].push_front(element);  // Insertar al inicio de la lista
    }

    void Remove(T element) {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];

        // Buscar y eliminar el elemento
        listAtIndex.remove(element);
    }

    bool Contains(T element) {
        int index = HashFunction(element);
        for (auto item : data[index]) {
            if (item == element) {
                return true;
            }
        }
        return false;
    }

    void Print() {
        for (int i = 0; i < arraySize; i++) {
            cout << "Índice " << i << ": ";
            for (auto item : data[i]) {
                cout << item << " -> ";
            }
            cout << "NULL" << endl;
        }
    }
};