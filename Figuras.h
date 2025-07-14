#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Figura
{
protected:
    string nombre; // nombre de la figura

public:
    Figura(string name) : nombre(name) {}
    virtual ~Figura() {}

    // M�todos que deben implementar las clases hijas
    virtual float CalcularArea() const = 0;
    virtual float CalcularPerimetro() const = 0;

    // Devuelve el nombre de la figura
    const string& ObtenerNombreDeFigura() const { return nombre; }
};

class Circulo : public Figura
{
private:
    float radio; // radio del c�rculo

public:
    Circulo(float r) : Figura("Circulo"), radio(r) {}

    // Calcula el �rea 
    float CalcularArea() const override { return 3.1416f * radio * radio; }

    // Calcula el per�metro 
    float CalcularPerimetro() const override { return 2 * 3.1416f * radio; }

    ~Circulo() override {}
};

class Cuadrado : public Figura
{
protected:
    float lado; // tama�o del lado

public:
    Cuadrado(float l) : Figura("Cuadrado"), lado(l) {}

    // �rea 
    float CalcularArea() const override { return lado * lado; }

    // Per�metro 
    float CalcularPerimetro() const override { return 4 * lado; }

    ~Cuadrado() override {}
};

class FiguraNLados : public Figura
{
private:
    int lados;     // cantidad de lados
    float longitud; // longitud de cada lado

public:
    FiguraNLados(int n, float l) : Figura("Figura de N lados"), lados(n), longitud(l) {}

    // �rea para pol�gonos
    float CalcularArea() const override
    {
        return (lados * longitud * longitud) / (4 * tan(3.1416f / lados));
    }

    // Per�metro 
    float CalcularPerimetro() const override { return lados * longitud; }

    ~FiguraNLados() override {}
};

class Cubo : public Cuadrado
{
public:
    Cubo(float lado) : Cuadrado(lado) { nombre = "Cubo"; }

    // Volumen 
    float Volumen() const { return lado * lado * lado; }

    // �rea de superficie 
    float Surface() const { return 6 * lado * lado; }

    float CalcularArea() const override { return Surface(); }

    // Per�metro total 
    float CalcularPerimetro() const override { return 12 * lado; }

    ~Cubo() override {}
};

class Linea : public Figura
{
private:
    float* segmentos; // arreglo din�mico con longitudes de segmentos
    int cantidad;     // n�mero de segmentos

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

    ~Linea() override
    {
        delete[] segmentos; // liberar memoria din�mica
    }

    
    float CalcularArea() const override { return 0; }

    // Per�metro es suma de todo
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
