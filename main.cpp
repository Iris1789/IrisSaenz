#include <iostream>
#include "SentinelLinkedList.h"
#include "LQueue.h"
#include "LStackr.h"
#include "Figuras.h"

using namespace std;

int main()
{
    // Ejemplo de uso de SentinelLinkedList
    SentinelLinkedList<int> lista;
    lista.PushBack(10);
    lista.PushFront(5);
    cout << "Lista, primer elemento: " << lista.Front() << endl;

    // Ejemplo de uso de LQueue
    LQueue<string> cola;
    cola.Enqueue("Hola");
    cola.Enqueue("Mundo");
    cout << "Cola, frente: " << cola.Front() << endl;
    cout << "Cola, sacar: " << cola.Dequeue() << endl;

    // Ejemplo de uso de LStack
    LStack<char> pila;
    pila.Push('A');
    pila.Push('B');
    cout << "Pila, cima: " << pila.Peak() << endl;
    cout << "Pila, sacar: " << pila.Pop() << endl;

    // Ejemplo de uso de Figuras
    Circulo c(3.0f);
    cout << "Círculo área: " << c.CalcularArea() << ", perímetro: " << c.CalcularPerimetro() << endl;

    Cubo cubo(2.0f);
    cout << "Cubo volumen: " << cubo.Volumen() << ", área superficie: " << cubo.CalcularArea() << endl;

    float segmentos[] = { 1.0f, 2.0f, 3.0f };
    Linea linea(segmentos, 3);
    cout << "Línea perímetro: " << linea.CalcularPerimetro() << endl;

    return 0;
}
