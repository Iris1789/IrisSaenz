#include <iostream>
#include "BinarySearchTree.h"
#include "HashSet.h"

using namespace std;

int main() {
    cout << "=== PRUEBA DE BINARY SEARCH TREE ===" << endl;
    BinarySearchTree<int> bst;

    bst.Add(50);
    bst.Add(30);
    bst.Add(70);
    bst.Add(20);
    bst.Add(40);

    cout << "Buscar 40: " << (bst.Search(40) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscar 100: " << (bst.Search(100) ? "Encontrado" : "No encontrado") << endl;

    bst.PostOrderIterative();

    cout << "Eliminar 30: " << (bst.Remove(30) ? "�xito" : "Fall�") << endl;
    bst.PostOrderIterative();

    bst.Clear();
    cout << "�rbol despu�s de limpiar: ";
    bst.PostOrderIterative();

    cout << "\n=== PRUEBA DE HASHSET ===" << endl;
    HashSet<int> hashSet(10);

    hashSet.Add(5);
    hashSet.Add(15);  // Colisi�n si tama�o es 10
    hashSet.Add(25);
    hashSet.Add(5);   // Duplicado

    hashSet.Print();

    cout << "Contiene 15: " << (hashSet.Contains(15) ? "S�" : "No") << endl;

    hashSet.Remove(15);
    cout << "Despu�s de eliminar 15: ";
    hashSet.Print();

    return 0;
}