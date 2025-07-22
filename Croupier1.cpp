#include "Croupier1.h"
#include <string>
#include <iostream>

Croupier1::Croupier1(const std::string &nombre)
    : Participante1(nombre), mostrandoCartaOculta(true)
{
    // Constructor que inicializa el nombre del croupier
}

bool Croupier1::debePedirCarta() const
{
    if (getMano().getValorTotal() < 17)
    {
        return true; // El croupier pide carta si su mano es menor a 17
    }
    return false; // No pide carta si tiene 17 o más
}

void Croupier1::mostrarMano() const
{
    std::cout << getNombre() << " tiene: ";

    if (getMano().getNumeroCartas() == 0)
    {
        std::cout << "Mano vacía." << std::endl;
        return;
    }

    if (mostrandoCartaOculta)
    {
        // Si la primera carta debe estar oculta
        std::cout << "[CARTA OCULTA] ";
        if (getMano().getNumeroCartas() > 1)
        {
            // Muestra la segunda carta visible (si hay al menos dos cartas)
            // Usamos getCarta(1) para obtener la segunda carta (índice 1)
            std::cout << getMano().getCarta(1)->toString();
        }
        std::cout << std::endl; // Nueva línea después de la mano parcial
    }
    else
    {
        // Si no estamos ocultando la carta, mostramos la mano completa
        // Delegamos al método mostrarMano de la clase base Participante1
        Participante1::mostrarMano(); // Esto llamará a mano.mostrarMano()
    }
}

// Implementación de los nuevos métodos para controlar el estado de la carta oculta
void Croupier1::setMostrandoCartaOculta(bool estado)
{
    mostrandoCartaOculta = estado;
}

bool Croupier1::getMostrandoCartaOculta() const
{
    return mostrandoCartaOculta;
}
void Croupier1::mostrarTodasLasCartas() const
{
    // Llama directamente al método de la Mano1 o al método base de Participante1
    // que se encarga de mostrar todas las cartas.
    // Asumiendo que Mano1::mostrarMano() ya muestra todas las cartas que tiene.
    getMano().mostrarMano();
} // La Mano1 es un miembro de Participante1 y Croupier1 tiene acceso.
