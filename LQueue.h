#pragma once
#include "SentinelLinkedList.h"

template <typename T>
class LQueue
{
private:
    SentinelLinkedList<T> data; // lista para guardar los datos

public:
    LQueue() {}

    int GetCount() { return data.GetCount(); } // devuelve cantidad de elementos
    void Enqueue(T value) { data.PushBack(value); } // mete al final (cola)
    T Dequeue() { return data.PopFront(); } // saca del frente (cola)
    T Front() { return data.Front(); } // mira el primer elemento sin sacarlo
};
