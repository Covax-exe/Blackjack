#include "Gestionador1.h"
#include <vector>
#include <iostream>
#include <string>
#include <limits>  // por std::numeric_limits
#include <cstdlib> // Necesario para la función exit()

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
    es una buena practica y sugerido para evitar errores en compilación*/
    croupierPrincipal = nullptr;
    std::cout << "Gestor de Blackjack destruido. Memoria de participantes liberada." << std::endl;
    // destructor hecho a "mano" para verificar la correcta liberación en memoria de los objetos creados.
}

void Gestionador1::agregarJugador(const std::string &nombre)
{
    // crea un nuevo jugador y lo agrega al vector de participantes
    Jugador1 *nuevoJugador = new Jugador1(nombre);
    participantes.push_back(nuevoJugador); // agrega el nuevo jugador al vector de participantes
    std::cout << "Jugador " << nombre << " agregado al juego." << std::endl;
}

// se eliminó la anterior version de get jugador.

int Gestionador1::getNumeroJugadores() const
{
    return participantes.size(); // retorna el numero de participantes en el juego usando el vector
}

void Gestionador1::terminarJuego()
{
    std::cout << "\n--- FIN DE LA RONDA ---" << std::endl;

    // 1. Mostrar las cartas del crupier (todas reveladas)
    if (croupierPrincipal != nullptr)
    { // Verificación de puntero a nullptr
        std::cout << croupierPrincipal->getNombre() << " revela sus cartas: ";
        croupierPrincipal->mostrarTodasLasCartas();
        std::cout << " (" << croupierPrincipal->getValorMano() << " puntos)" << std::endl;
    }
    else
    {
        std::cerr << "Error: El crupier no está inicializado. No se puede mostrar su mano." << std::endl;
    }

    std::cout << "\n--- Manos Finales de los Jugadores ---" << std::endl;
    for (Participante1 *p : participantes)
    {
        // Comprobamos si el participante actual NO es el crupier.
        if (p != croupierPrincipal)
        { // Si el participante no es el crupier...
            std::cout << p->getNombre() << " tiene: ";
            p->mostrarMano();
            std::cout << " (" << p->getValorMano() << " puntos)";
            std::cout << std::endl; // Nueva línea al final de cada jugador
        }
    }
    std::cout << "---------------------------------------" << std::endl;

    // Mensaje para indicar que el juego ha finalizado y no se continuará.
    std::cout << "Juego finalizado. ¡Gracias por jugar!" << std::endl;

    // El destructor de Gestionador1 SÍ se llamará automáticamente antes de salir.
    // ----------------------------------------------------------------------------------
    // Llama a exit(0) para terminar el programa completamente
    exit(0);
}

// Este método muestra por consola el resultado final de las apuestas
// No se realiza ningún pago real ni modificación de saldo
// Solo se informa quién gana, pierde o empata según el valor de su mano
void Gestionador1::pagarApuestas()
{
    // Imprime el encabezado para la sección de pagos
    std::cout << "\n--- PAGOS DE LA RONDA ---" << std::endl;

    // Obtiene el valor total de la mano del croupier
    int valorCroupier = croupierPrincipal->getValorMano();

    // Verifica si el croupier se pasó de 21 puntos
    bool croupierSePaso = croupierPrincipal->estaPasado();

    // Recorre el vector de todos los participantes en el juego
    for (Participante1 *p : participantes)
    {
        // Intentamos convertir 'p' (Participante1*) a 'Jugador1*' usando dynamic_cast.
        // Esto nos permite distinguir jugadores reales del croupier dentro del vector 'participantes'.
        // Si 'p' es un Jugador1, obtenemos el puntero; si es un Croupier1, obtenemos nullptr y lo ignoramos.

        Jugador1 *jugador = dynamic_cast<Jugador1 *>(p);

        // Verifica que efectivamente sea un jugador y que haya hecho una apuesta (mayor a 0)
        if (jugador && jugador->getApuesta() > 0)
        {
            // Obtiene la cantidad apostada por este jugador
            int apuesta = jugador->getApuesta();

            // Obtiene el valor total de la mano del jugador
            int valorJugador = jugador->getValorMano();

            // Verifica si el jugador se pasó de 21 puntos
            bool jugadorSePaso = jugador->estaPasado();

            // Muestra el nombre del jugador evaluado
            std::cout << "\nJugador " << jugador->getNombre() << ": ";

            // Si el jugador se pasó de 21, pierde automáticamente
            if (jugadorSePaso)
            {
                std::cout << "Pierde su apuesta de " << apuesta << " unidades." << std::endl;
            }

            // Si el jugador tiene blackjack y el croupier no, gana automáticamente
            else if (jugador->tieneBlackjackActivo() && !croupierPrincipal->tieneBlackjackActivo())
            {
                // Se le informa que gana el doble de su apuesta (según la lógica actual del juego)
                std::cout << "¡Blackjack! Gana " << apuesta * 2 << " unidades." << std::endl;
            }

            // Si el croupier se pasó o el jugador tiene mayor puntuación, gana
            else if (croupierSePaso || valorJugador > valorCroupier)
            {
                std::cout << "Gana " << apuesta << " unidades." << std::endl;
            }

            // Si el valor de la mano del jugador es menor al del croupier, pierde
            else if (valorJugador < valorCroupier)
            {
                std::cout << "Pierde su apuesta de " << apuesta << " unidades." << std::endl;
            }

            // Si el jugador y el croupier tienen el mismo puntaje, hay empate
            else
            {
                std::cout << "Empate. Recupera su apuesta de " << apuesta << " unidades." << std::endl;
            }
        }
    }
}

// solicita a cada jugador que ingrese su apuesta, validando que sea un numero positivo
void Gestionador1::abrirApuestas()
{
    for (Participante1 *p : participantes)
    {
        Jugador1 *jugador = dynamic_cast<Jugador1 *>(p);
        if (jugador)
        {
            char respuesta;
            while (true)
            {
                std::cout << "Jugador " << jugador->getNombre() << ", ¿deseas apostar esta ronda? (s/n): ";
                std::cin >> respuesta;

                if (std::cin.fail())
                {
                    std::cin.clear();                                                   // Limpia el error
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta entrada invalida
                    std::cout << "Entrada inválida. Intenta nuevamente.\n";
                    continue;
                }

                respuesta = std::tolower(respuesta); // Acepta mayusculas o minusculas

                if (respuesta == 's')
                {
                    jugador->setApuesta(1);                          // Apuesta simbolica
                    jugador->setEstado(EstadoParticipante::JUGANDO); // activa
                    std::cout << "Has apostado esta ronda.\n";
                    break;
                }
                else if (respuesta == 'n')
                {
                    jugador->setApuesta(0);                           // No apostó
                    jugador->setEstado(EstadoParticipante::PLANTADO); // se retira
                    std::cout << "No apostaste esta ronda.\n";
                    break;
                }
                else
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Por favor responde solo con 's' o 'n'.\n";
                }
            }
        }
    }
}
/*---------------------------------------------------------------------------------------------------------------------*/

void Gestionador1::ejecutarTurno()
{
    std::cout << "\n--- Inicio de la Fase de Turnos ---" << std::endl;

    // --- FASE 1: Turnos de los Jugadores --- //
    std::cout << "\n--- Turno de los Jugadores ---" << std::endl;

    // Iteramos sobre todos los participantes para encontrar a los jugadores.
    for (Participante1 *p : participantes)
    {
        if (Jugador1 *jugador = dynamic_cast<Jugador1 *>(p))
        {
            if (jugador->getEstado() == EstadoParticipante::JUGANDO)
            {
                std::cout << "\nEs el turno de " << jugador->getNombre() << "." << std::endl;
                mostrarEstadoJuego(); // Muestra el estado actual del juego (crupier aún con carta oculta)

                while (jugador->getEstado() == EstadoParticipante::JUGANDO && jugador->getValorMano() < 21)
                {
                    std::cout << jugador->getNombre() << ", tu mano actual: ";
                    jugador->mostrarMano(); // Muestra las cartas del jugador
                    std::cout << " (" << jugador->getValorMano() << " puntos)." << std::endl;

                    char decision;
                    std::cout << "Digite en minuscula la opcion encerrada en parentesis (solo la letra)";
                    std::cout << "¿Quieres (P)edir carta o (X)plantarte? ";
                    std::cin >> decision;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    decision = std::tolower(decision); // Convertir la entrada a minúscula

                    if (decision == 'p')
                    {
                        repartirCarta(jugador); // Le damos una carta al jugador
                        std::cout << jugador->getNombre() << " pide una carta." << std::endl;

                        // Evaluar la mano después de pedir la carta
                        if (jugador->getValorMano() > 21)
                        {
                            std::cout << jugador->getNombre() << " se ha pasado con " << jugador->getValorMano() << " puntos. ¡Pierde!" << std::endl;
                            jugador->setEstado(EstadoParticipante::PASADO); // Marcar como pasado
                        }
                        else if (jugador->getValorMano() == 21)
                        {
                            std::cout << jugador->getNombre() << " tiene 21 puntos." << std::endl;
                            // Automáticamente se planta si tiene 21
                            jugador->setEstado(EstadoParticipante::PLANTADO);
                        }
                    }
                    else if (decision == 'x')
                    {
                        std::cout << jugador->getNombre() << " se planta con " << jugador->getValorMano() << " puntos." << std::endl;
                        jugador->setEstado(EstadoParticipante::PLANTADO);
                    }
                    else
                    {
                        std::cout << "Decisión inválida. Por favor, ingresa 'P' para pedir o 'X' para plantarte." << std::endl;
                    }
                    mostrarEstadoJuego();
                } // Fin del bucle 'while' para el jugador actual

                // Mensaje final para el jugador, si no se dió al salir del while
                if (jugador->getEstado() == EstadoParticipante::JUGANDO)
                {
                    jugador->setEstado(EstadoParticipante::PLANTADO); // Asegurarse de que el estado final sea plantado
                }
                std::cout << jugador->getNombre() << " ha terminado su turno." << std::endl;
            }
            else
            {
                std::cout << jugador->getNombre() << " no juega este turno (estado: "
                          << static_cast<int>(jugador->getEstado()) << ")." << std::endl;
            }
        }
    }
    std::cout << "\n--- Turno de los Jugadores Finalizado ---" << std::endl;

    // --- FASE 2: Turno del Crupier --- //
    std::cout << "\n--- Turno del Crupier ---" << std::endl;
    if (croupierPrincipal != nullptr)
    {
        croupierPrincipal->setMostrandoCartaOculta(false);
        std::cout << "El crupier revela su carta oculta." << std::endl;
        mostrarEstadoJuego();
        while (croupierPrincipal->getValorMano() < 17 && croupierPrincipal->getValorMano() <= 21)
        {
            std::cout << "El crupier tiene " << croupierPrincipal->getValorMano() << " puntos y pide carta." << std::endl;
            repartirCarta(croupierPrincipal);
            mostrarEstadoJuego();
        }

        // Evaluar la mano final del crupier
        if (croupierPrincipal->getValorMano() > 21)
        {
            std::cout << "El crupier se ha pasado con " << croupierPrincipal->getValorMano() << " puntos. ¡Todos los jugadores restantes ganan!" << std::endl;
            croupierPrincipal->setEstado(EstadoParticipante::PASADO);
        }
        else
        {
            std::cout << "El crupier se planta con " << croupierPrincipal->getValorMano() << " puntos." << std::endl;
            croupierPrincipal->setEstado(EstadoParticipante::PLANTADO);
        }
    }
    else
    {
        std::cerr << "Error: No se encontró un objeto crupier para ejecutar su turno." << std::endl;
    }
    std::cout << "\n--- Turno del Crupier Finalizado ---" << std::endl;

    std::cout << "\n--- Todos los turnos han sido ejecutados ---" << std::endl;
}
/*----------------------------------------------------------------------------------------------------------------------*/

void Gestionador1::mostrarIndicesJugadores() const
{
    std::cout << "\n--- Jugadores Disponibles ---" << std::endl;
    int jugadorContador = 0;
    for (Participante1 *p : participantes)
    {
        if (p == nullptr)
        {
            continue;
        }
        if (p != this->croupierPrincipal)
        {
            if (Jugador1 *jugador = dynamic_cast<Jugador1 *>(p))
            {
                std::cout << "  [" << jugadorContador << "] " << jugador->getNombre() << std::endl;
                jugadorContador++;
            }
        }
    }
    if (jugadorContador == 0)
    {
        std::cout << "No hay jugadores en el juego (aparte del crupier)." << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}
/*-----------------------------------------------------------------------------------------------------------------------------*/

// Muestra el estado actual del juego (croupier y jugadores)
void Gestionador1::mostrarEstadoJuego() const
{
    // imprime un encabezado para separar visualmente la sección de estado del juego
    std::cout << "\n====== ESTADO ACTUAL DEL JUEGO ======" << std::endl;

    // imprime el nombre del croupier
    std::cout << "\n"
              << croupierPrincipal->getNombre() << ": ";

    // muestra las cartas del croupier (si tiene carta oculta se encarga su función)
    croupierPrincipal->mostrarMano();

    // imprime el valor total actual de la mano del croupier
    std::cout << " (" << croupierPrincipal->getValorMano() << " puntos)" << std::endl;

    // itera sobre todos los participantes del juego (croupier y jugadores)
    for (Participante1 *p : participantes)
    {
        // verifica que el puntero no sea nulo y que no sea el croupier
        if (p != nullptr && p != croupierPrincipal)
        {
            // intenta convertir el participante actual a un Jugador1
            Jugador1 *jugador = dynamic_cast<Jugador1 *>(p);
            // si es un jugador y no otro tipo de participante
            if (jugador != nullptr)
            {
                // muestra el nombre del jugador
                std::cout << jugador->getNombre() << ": ";

                // muestra las cartas del jugador
                jugador->mostrarMano();

                // muestra el valor total de la mano del jugador
                std::cout << " (" << jugador->getValorMano() << " puntos)" << std::endl;
            }
        }
    }

    // imprime una linea de cierre para separar visualmente la sección
    std::cout << "=====================================" << std::endl;
}
/*-----------------------------------------------------------------------------------------------------------------------------*/

Jugador1 *Gestionador1::getJugador(int indice)
{
    // Validar el índice de entrada
    if (indice < 0)
    {
        std::cerr << "Error: El índice del jugador no puede ser negativo." << std::endl;
        return nullptr;
    }
    int jugadorContador = 0;

    for (Participante1 *p : participantes)
    {
        if (p == nullptr)
        {
            continue;
        }

        if (p == this->croupierPrincipal)
        {
            continue;
        }

        if (Jugador1 *jugador = dynamic_cast<Jugador1 *>(p))
        {
            if (jugadorContador == indice)
            {
                return jugador;
            }
            jugadorContador++; // Si no es el jugador buscado, pero es un jugador, incrementamos el contador
        }
    }
    std::cerr << "Error: Índice de jugador fuera de rango o jugador no encontrado para el índice " << indice << "." << std::endl;
    return nullptr;
}
/*----------------------------------------------------------------------------------------------------------------*/
void Gestionador1::repartirCarta(Participante1 *p)
{
    if (p == nullptr)
    {
        std::cerr << "Error: Intentando repartir carta a un participante nulo." << std::endl;
        return;
    }
    // 1. Obtener la carta de la baraja:
    Carta1 *cartaObtenidaDeBaraja = baraja.repartirCarta();

    if (cartaObtenidaDeBaraja != nullptr)
    {
        // 2. Entregar la carta al participante:
        p->recibirCarta(cartaObtenidaDeBaraja);
    }
    else
    {
        std::cerr << "Advertencia: No quedan cartas en la baraja para repartir." << std::endl;
    }
}
/*-------------------------------------------------------------------------------------------------------------------*/
void Gestionador1::repartoInicial()
{
    std::cout << "\n--- Iniciando el Reparto Inicial de Cartas ---" << std::endl;

    std::cout << "Repartiendo la primera carta a cada participante..." << std::endl;
    for (Participante1 *p : participantes)
    {
        if (p != nullptr)
        {
            repartirCarta(p);
        }
    }
    std::cout << "Repartiendo la segunda carta a cada participante..." << std::endl;
    for (Participante1 *p : participantes)
    {
        if (p != nullptr)
        {
            repartirCarta(p);
        }
    }
    if (croupierPrincipal != nullptr)
    {
        croupierPrincipal->setMostrandoCartaOculta(true);
    }
    std::cout << "--- Reparto Inicial Completado ---" << std::endl;
}
/*-------------------------------------------------------------------------------------------------------------------*/
// Este método reparte dos cartas iniciales a todos los jugadores activos
// y al croupier, para iniciar la ronda del juego.
void Gestionador1::iniciarJuego()
{
    std::cout << "\nRepartiendo cartas iniciales...\n";

    // 🔹 Repartir 2 cartas a cada jugador que haya apostado
    for (Participante1* p : participantes)
    {
        Jugador1* jugador = dynamic_cast<Jugador1*>(p);
        if (jugador && jugador->getApuesta() > 0)
        {
            repartirCartas(jugador);
            repartirCartas(jugador);
        }
    }

    // 🔹 Repartir 2 cartas al croupier
    repartirCartas(croupierPrincipal);
    repartirCartas(croupierPrincipal);

    std::cout << "Cartas iniciales repartidas.\n";
}
/*-------------------------------------------------------------------------------------------------------------------*/

