#include "Mano1.h"
#include <vector>
#include <iostream>

Mano1::Mano1() {
    // El vector 'cartas' se inicializa solo.
}
bool Mano1::agregarCarta(const Carta1* carta) {
    // Verificación básica para asegurar que la carta no sea un puntero nulo.
    if (carta == nullptr) {
        return false; // No agregamos cartas nulas.
    }
    // Agregamos el puntero a la carta al final del vector 'cartas'.
    // Usamos 'const_cast' porque 'agregarCarta' recibe 'const Carta1*',
    // pero el vector 'cartas' almacena 'Carta1*' (sin const).
    // Esto es seguro aquí porque Mano1 asume la propiedad de la memoria de la carta.
    cartas.push_back(const_cast<Carta1*>(carta));
    return true; // Indicamos que la carta fue agregada.
}

// --- getValorTotal ---
// Calcula el valor total de la mano, manejando la lógica especial de los Ases (1 u 11).
int Mano1::getValorTotal() const {
    int total = 0; // Acumulador del valor total de la mano.
    int numAses = 0; // Contador de Ases en la mano.

    // Primera pasada: Sumar los valores de todas las cartas y contar los Ases.
    for (const Carta1* carta : cartas) {
        // Si la carta es un As...
        if (carta->getValorEnum() == Carta1::AS) {
            numAses++;
            total += 11; // Inicialmente, el As vale 11.
        } else {
            // Para otras cartas (2-10, J, Q, K), sumamos su valor numérico directo.
            total += carta->getValorNumerico();
        }
    }

    // Segunda pasada: Ajustar el valor de los Ases si la mano se pasa de 21.
    // Mientras el total sea mayor que 21 Y tengamos Ases que aún valen 11...
    while (total > 21 && numAses > 0) {
        total -= 10; // Cambiamos el valor de un As de 11 a 1 (una reducción de 10).
        numAses--;   // Decrementamos el contador de Ases que valen 11.
    }

    return total; // Retornamos el valor final de la mano.
}
void Mano1::mostrarMano() const {
    // Si la mano está vacía, mostramos un mensaje apropiado.
    if (cartas.empty()) {
        std::cout << "Mano vacía." << std::endl;
        return;
    }

    std::cout << "Cartas en mano: ";
    // Usamos un bucle for basado en rango, que es la forma moderna y limpia
    // de iterar sobre todos los elementos de un contenedor como std::vector.
    for (const Carta1* carta : cartas) {
        // En cada iteración, 'carta' será un puntero constante a una Carta1
        // que está en nuestro vector 'cartas'.
        // Como 'carta' es un puntero, usamos el operador '->' para llamar
        // al método 'toString()' de la carta y obtener su representación en texto.
        std::cout << carta->toString() << " ";
    }
    // Después de mostrar todas las cartas, mostramos el valor total de la mano.
    std::cout << "(Valor Total: " << getValorTotal() << ")" << std::endl;
}

bool Mano1::tieneBlackjack() const {
    // Un Blackjack solo puede ocurrir con dos cartas.
    if (cartas.size() == 2) {
        // Si tiene dos cartas y el valor total es exactamente 21.
        if (getValorTotal() == 21) {
            return true; // ¡Es un Blackjack!
        }
    }
    return false; // No es Blackjack.
}
// --- getCarta ---
// Retorna un puntero constante a la carta en el índice especificado.
// Si el índice está fuera de rango, retorna nullptr.
const Carta1* Mano1::getCarta(int indice) const {
    if (indice >= 0 && indice < static_cast<int>(cartas.size())) {
        return cartas[indice];
    }
    return nullptr; // Índice fuera de rango
}

// --- getNumeroCartas ---
// Retorna el número de cartas en la mano.
int Mano1::getNumeroCartas() const {
    return static_cast<int>(cartas.size());
}

// Fin de la implementación de Mano1.cpp
