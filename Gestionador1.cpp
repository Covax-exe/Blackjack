#include "Gestionador1.h"
#include <vector>
#include <iostream>
#include <string>

// Constructor
Gestionador1::Gestionador1()
    : baraja() // Inicializa el objeto 'baraja' llamando a su constructor por defecto
{
    //  Crear el objeto Croupier1 dinámicamente
    croupierPrincipal = new Croupier1("Croupier de la Casa");
    //  Añadir el puntero al Croupier al vector de participantes (usando polimorfismo)
    participantes.push_back(croupierPrincipal);
    // con esto aseguramos que al inicializar el gestionador, se le asigne una baraja y un cropier para el juego completo.
    std::cout << "Gestor de Blackjack inicializado. Croupier y Baraja listos." << std::endl;
}

Gestionador1::~Gestionador1()
{
    // Itera sobre el vector de participantes y elimina cada objeto apuntado
    for (Participante1 *p : participantes)
    {
        // Como el destructor de Participante1 es virtual,
        // se llamará al destructor correcto (Jugador1 o Croupier1).
        delete p;
    }
    // Después de liberar la memoria de los objetos, limpia el vector de punteros.
    participantes.clear();
    /* 'croupierPrincipal' no se elimina por separado aquí,
     ya que su memoria fue liberada cuando se iteró sobre 'participantes'.
     Es buena práctica apuntarlo a nullptr para evitar punteros colgantes.
     es una buena praactica y sugerido para evitar errores en compilación*/
    croupierPrincipal = nullptr;
    std::cout << "Gestor de Blackjack destruido. Memoria de participantes liberada." << std::endl;
    // destructor hecho a "mano" para verificar la correcta liberación en memoria de los objetos creados.
}

int Gestionador1::agregarJugador(const std::string &nombre)
{
    // crea un nuevo jugador y lo agrega al vector de participantes
    Jugador1 *nuevoJugador = new Jugador1(nombre);
    participantes.push_back(nuevoJugador); // agrega el nuevo jugador al vector de participantes
    std::cout << "Jugador " << nombre << " agregado al juego." << std::endl;
}

Jugador1 *Gestionador1::getJugador(int indice)
{
    // verifica si el indice es válido
    if (indice < 0 || indice >= participantes.size())
    {
        std::cerr << "Error: Índice de jugador inválido." << std::endl; // cerr se usa para que muestr error
        return nullptr;                                                 // retorna nullptr si el indice es invalido
    }
    // devuelve el jugador en la posicion indicada, asegurando que sea del tipo Jugador1
    return dynamic_cast<Jugador1 *>(participantes[indice]);
}

int Gestionador1::getNumeroJugadores() const
{
    return participantes.size(); // retorna el numero de participantes en el juego usando el vector
}

void Gestionador1::terminiarJuego(){
    




    
}
