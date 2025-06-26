#include "Jugador1.h"
#include <iostream>
#include <string>

Jugador1::Jugador1(const std::string& nombre, int apuestaInicial)
    : Participante1(nombre), apuesta(apuestaInicial) {
    // Constructor que inicializa el nombre del jugador y su apuesta inicial
}

//Destructor virtual para asegurar liberación de recursos, default.

void Jugador1::mostrarMano() const {
    // Muestra la mano del jugador
    Participante1::mostrarMano(); // Llama al método de la clase base para mostrar la mano
}

void Jugador1::realizarApuesta(int cantidad) {
    // Método para que el jugador realice una apuesta
    setApuesta(cantidad); // Establece la apuesta del jugador
}

int Jugador1::getApuesta() const {
    // Método para obtener la apuesta actual del jugador
    return apuesta; // Retorna la apuesta actual
}

void Jugador1::setApuesta(int nuevaApuesta) {
    // Método para establecer una nueva apuesta
    if (nuevaApuesta < 0) {
        std::cerr << "Error: La apuesta no puede ser negativa." << std::endl;
        return;
    }
    apuesta = nuevaApuesta; // Actualiza la apuesta del jugador
}
// Fin de la implementación de Jugador1.cpp
// Nota: No es necesario implementar un destructor aquí, ya que el destructor de Participante1 es virtual y se encargará de liberar la memoria de Mano1.