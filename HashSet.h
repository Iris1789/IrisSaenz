#pragma once
#include "HashTableChaining.h"

template <typename T>
class HashSet : public HashTableChaining<T> {
public:
    // Usamos el mismo constructor de la clase base
    using HashTableChaining<T>::HashTableChaining;

    // Sobreescribimos Add para evitar duplicados
    void Add(T element) {
        if (!this->Contains(element)) {
            HashTableChaining<T>::Add(element);
        }
    }

    // Método adicional para verificar si está vacío
    bool IsEmpty() {
        for (int i = 0; i < this->arraySize; i++) {
            if (!this->data[i].empty()) {
                return false;
            }
        }
        return true;
    }
};