#include <iostream>
#include <string>
#include "Gestionador1.h"

int main()
{
    Gestionador1 gestor;
    int opcion = 0;

    std::cout << "==============================" << std::endl;
    std::cout << "        BLACKJACK C++         " << std::endl;
    std::cout << "==============================" << std::endl;

    // Agregar jugadores antes de empezar el juego
    int numJugadores;
    std::cout << "¿Cuántos jugadores deseas agregar? ";
    std::cin >> numJugadores;
    std::cin.ignore();

    for (int i = 0; i < numJugadores; ++i)
    {
        std::string nombre;
        std::cout << "Nombre del jugador " << (i + 1) << ": ";
        std::getline(std::cin, nombre);
        gestor.agregarJugador(nombre);
    }

    do
    {
        std::cout << "\n===== MENÚ PRINCIPAL =====\n";
        std::cout << "1. Iniciar ronda\n";
        std::cout << "2. Mostrar estado actual del juego\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion)
        {
        case 1:
            gestor.abrirApuestas();
            gestor.iniciarJuego();
            gestor.mostrarEstadoJuego();
            gestor.ejecutarTurno();
            gestor.definirGanador();
            gestor.pagarApuestas();
            gestor.terminarJuego(); // Limpiar estado para nueva ronda
            break;

        case 2:
            gestor.mostrarEstadoJuego();
            break;

        case 3:
            std::cout << "Gracias por jugar Blackjack. ¡Hasta la próxima!\n";
            break;

        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 3);

    return 0;
}
