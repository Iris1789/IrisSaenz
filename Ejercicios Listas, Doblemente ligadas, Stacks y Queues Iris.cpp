

#include <iostream>
#include <cmath>
#include <forward_list> // Lista ligada simple de STL (para la pila)
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


// PUNTO 2

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


// PUNTO 3


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

// PUNTO 4

class Figura
{
protected:
    string nombre; // nombre de la figura

public:
    Figura(string name) : nombre(name) {}
    virtual ~Figura() {}

    // Métodos que deben implementar las clases hijas
    virtual float CalcularArea() const = 0;
    virtual float CalcularPerimetro() const = 0;

    // Devuelve el nombre de la figura
    const string& ObtenerNombreDeFigura() const { return nombre; }
};

class Circulo : public Figura
{
private:
    float radio; // radio del círculo

public:
    Circulo(float r) : Figura("Circulo"), radio(r) {}

    // Calcula el área (pi*r^2)
    float CalcularArea() const override { return 3.1416f * radio * radio; }

    // Calcula el perímetro (2*pi*r)
    float CalcularPerimetro() const override { return 2 * 3.1416f * radio; }
};

class Cuadrado : public Figura
{
protected:
    float lado; // tamaño del lado

public:
    Cuadrado(float l) : Figura("Cuadrado"), lado(l) {}

    // Área = lado^2
    float CalcularArea() const override { return lado * lado; }

    // Perímetro = 4*lado
    float CalcularPerimetro() const override { return 4 * lado; }
};

class FiguraNLados : public Figura
{
private:
    int lados;     // cantidad de lados
    float longitud; // longitud de cada lado

public:
    FiguraNLados(int n, float l) : Figura("Figura de N lados"), lados(n), longitud(l) {}

    // Área para polígonos regulares usando fórmula
    float CalcularArea() const override
    {
        return (lados * longitud * longitud) / (4 * tan(3.1416f / lados));
    }

    // Perímetro = número de lados * longitud
    float CalcularPerimetro() const override { return lados * longitud; }
};

class Cubo : public Cuadrado
{
public:
    Cubo(float lado) : Cuadrado(lado) { nombre = "Cubo"; }

    // Volumen = lado^3
    float Volumen() const { return lado * lado * lado; }

    // Área de superficie = 6 * lado^2
    float Surface() const { return 6 * lado * lado; }

    float CalcularArea() const override { return Surface(); }

    // Perímetro total = suma de las aristas (12 aristas)
    float CalcularPerimetro() const override { return 12 * lado; }
};

class Linea : public Figura
{
private:
    float* segmentos; // arreglo dinámico con longitudes de segmentos
    int cantidad;     // número de segmentos

public:
    Linea(float* arr, int tam) : Figura("Linea")
    {
        cantidad = tam;
        segmentos = new float[cantidad]; // pedir memoria para los segmentos
        for (int i = 0; i < cantidad; i++)
        {
            segmentos[i] = arr[i]; // copiar valores
        }
    }

    ~Linea()
    {
        delete[] segmentos; // liberar memoria dinámica
    }

    // Área es 0 porque es una línea, no tiene área
    float CalcularArea() const override { return 0; }

    // Perímetro es suma de todos los segmentos
    float CalcularPerimetro() const override
    {
        float suma = 0;
        for (int i = 0; i < cantidad; i++)
        {
            suma += segmentos[i];
        }
        return suma;
    }
};
