#ifndef BARAJA1_H
#define BARAJA1_H
#include <vector>
#include <string>
#include "Carta1.h"
class Baraja1 {
private:
    std::vector<Carta1*> cartas; // Contiene las cartas de la baraja
public:
    Baraja1(); // Constructor que inicializa la baraja con 52 cartas
    ~Baraja1(); // Destructor para liberar memoria de las cartas
    void barajar(); // Baraja las cartas de la baraja
    Carta1* repartirCarta(); // Reparte una carta de la baraja
    int getNumeroCartas() const; // Devuelve el número de cartas restantes en la baraja
};
#endif // BARAJA1_H