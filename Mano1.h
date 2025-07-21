#ifndef MANO1_H
#define MANO1_H
#include <vector>
#include "Carta1.h"
class Mano1
{
private:
    std::vector<const Carta1 *> cartas; // Contiene las cartas de la mano
public:
    Mano1();
    ~Mano1() = default;
    bool agregarCarta(const Carta1 *carta); // Agrega una carta a la mano
    int getValorTotal() const;              // Calcula el valor total de la mano
    void mostrarMano() const;               // Muestra las cartas de la mano
    bool tieneBlackjack() const;            // Verifica si la mano tiene Blackjack

    const Carta1 *getCarta(size_t index) const
    {
        if (index < cartas.size())
        {
            return cartas.at(index);
        }
        return nullptr;
    }

    // Método para saber cuántas cartas hay
    size_t getNumeroCartas() const
    {
        return cartas.size();
    }
};
#endif // MANO1_H
// Fin del archivo Mano1.h
