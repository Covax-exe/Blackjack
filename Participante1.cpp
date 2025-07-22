#include "Participante1.h"
#include <iostream>
#include <string>
Participante1::Participante1(const std::string& n) : nombre(n) 
{
    // Constructor que inicializa el nombre del participante
}

// --- Destructor Virtual ---
// "= default" en el .h ya le dice al compilador que genere un destructor por defecto.
// Aquí solo lo declaramos (o lo omitimos si ya usamos = default en el .h y no hace nada más).

void Participante1::recibirCarta(Carta1* carta) {
    // El participante recibe la carta y se la pasa a su mano
    if (carta != nullptr) {
        mano.agregarCarta(carta);
    } else {
        std::cerr << "Error: Carta nula recibida por " << nombre << std::endl;
    }
} 

void Participante1::mostrarMano() const {
    // El participante le pide a su mano que se muestre
    mano.mostrarMano();
}

int Participante1::getValorMano() const {
    // El participante le pide el valor a su mano
    return mano.getValorTotal();
}
std::string Participante1::getNombre() const {
    // El participante retorna su nombre
    return nombre;
}
bool Participante1::tieneBlackjack() const {
    // El participante le pregunta a su mano si tiene Blackjack
    return mano.tieneBlackjack();
}


void Participante1::setEstado(EstadoParticipante nuevoEstado) {
    estadoActual = nuevoEstado;
}

// --- getEstado ---
// Retorna el estado actual del participante.
EstadoParticipante Participante1::getEstado() const {
    return estadoActual;
}

// --- estaJugando ---
// Retorna true si el participante todavía está activo en la ronda.
bool Participante1::estaJugando() const {
    return estadoActual == EstadoParticipante::JUGANDO;
}

// --- estaPlantado ---
// Retorna true si el participante se ha plantado.
bool Participante1::estaPlantado() const {
    return estadoActual == EstadoParticipante::PLANTADO;
}

// --- estaPasado ---
// Retorna true si el participante se ha pasado de 21.
bool Participante1::estaPasado() const {
    return estadoActual == EstadoParticipante::PASADO;
}

// --- tieneBlackjackActivo ---
// Retorna true si el participante tiene un Blackjack y ese es su estado final de la mano.
bool Participante1::tieneBlackjackActivo() const {
    return estadoActual == EstadoParticipante::BLACKJACK;
}

// --- limpiarMano ---
// Resetea la mano y el estado del participante para una nueva ronda.
void Participante1::limpiarMano() {
    mano = Mano1(); // Vacía la mano (llama al destructor de la mano anterior)
    estadoActual = EstadoParticipante::JUGANDO; // Resetea el estado a 'JUGANDO' para la nueva ronda
}

