#pragma once
#include <forward_list>
#include <iostream>
using namespace std;

template <typename T>
class LStack
{
private:
    forward_list<T> data; // lista simple de STL para la pila
    int count;

public:
    LStack() { count = 0; }

    // Agrega un elemento al inicio (tope de la pila)
    void Push(T value)
    {
        data.push_front(value);
        count++;
    }

    // Quita el elemento del tope y lo devuelve
    T Pop()
    {
        if (count == 0)
        {
            cerr << "Advertencia: Pop en stack vacia" << endl;
            return {};
        }
        T value = data.front();
        data.pop_front();
        count--;
        return value;
    }

    // Devuelve el valor del tope sin quitarlo
    T Peak()
    {
        if (count == 0)
        {
            cerr << "Advertencia: Peak en stack vacia" << endl;
            return {};
        }
        return data.front();
    }

    int Count() { return count; } // devuelve cuantos hay en la pila
};
