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
    std::cout << "¡Bienvenido! El juego de Blackjack está listo. Baraja mezclada y crupier preparado." << std::endl;
}

// Destructor
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
    std::cout << "Cierre del juego completado. Recursos liberados correctamente." << std::endl;
    // destructor hecho a "mano" para verificar la correcta liberación en memoria de los objetos creados.
}

/*----------------------------------------------------------------------------------------------------------------*/
void Gestionador1::repartirCarta(Participante1 *p)
{
    if (p == nullptr)
    {
        std::cerr << "Error: No se puede repartir carta. Participante no válido." << std::endl;
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
        std::cerr << "La baraja está vacía. No se pudo repartir carta." << std::endl;
    }
}

/*----------------------------------------------------------------------------------------------------------------*/
// Este método inicializa la ronda: limpia las manos anteriores,
// cartas en la baraja y reparte las 2 cartas iniciales a jugadores activos y al croupier.
void Gestionador1::iniciarJuego()
{
    std::cout << "\n Repartiendo cartas iniciales a los jugadores...\n";

    // Limpiar manos y reiniciar estados
    // Antes de empezar, aseguramos que las manos estén vacías
    // y todos los participantes marcados como 'JUGANDO' (excepto los retirados).
    for (Participante1 *p : participantes)
    {
        p->limpiarMano();
        p->setEstado(EstadoParticipante::JUGANDO);
    }


    // Validar si la baraja tiene suficientes cartas
    // advertir si quedan pocas cartas
    if (baraja.getNumeroCartas() < participantes.size() * 2) {
        std::cout << "Atención: Quedan pocas cartas en el mazo. Considera barajar pronto.\n";
    }


    // Repartir 2 cartas a cada jugador activo
    for (Participante1 *p : participantes)
    {
        Jugador1 *jugador = dynamic_cast<Jugador1 *>(p);
        // Solo damos cartas a jugadores reales que hayan apostado (>0)
        if (jugador && jugador->getApuesta() > 0)
        {
            repartirCarta(jugador);
            repartirCarta(jugador);
        }
    }

    // Repartir 2 cartas al croupier
    // Además, activamos la bandera para ocultar su primera carta.
    croupierPrincipal->setMostrandoCartaOculta(true);
    repartirCarta(croupierPrincipal);
    repartirCarta(croupierPrincipal);

    std::cout << "Cartas iniciales repartidas. ¡Comienza la ronda!\n";
}

/*-------------------------------------------------------------------------------------------------------------------*/
void Gestionador1::ejecutarTurno() 
{
    std::cout << "\n========================================\n";
    std::cout << "          COMIENZA UNA NUEVA RONDA        \n";
    std::cout << "========================================\n";

    reiniciarRonda(); 

    std::cout << "\n Fase de apuestas: ¡Hora de decidir si juegas esta ronda!\n";
    abrirApuestas(); 

    bool hayJugadoresActivos = false;
    for (Participante1* p : participantes) {
        if (Jugador1* jugador = dynamic_cast<Jugador1*>(p)) {
            if (jugador->getApuesta() > 0) {
                hayJugadoresActivos = true;
                break;
            }
        }
    }

    if (!hayJugadoresActivos && getNumeroJugadores() > 1) { 
        std::cout << "Nadie apostó en esta ronda. La ronda ha sido cancelada.\n";
        return; 
    } else if (getNumeroJugadores() <= 1) { // Solo el crupier
        std::cout << "No hay jugadores disponibles. Ronda finalizada automáticamente.\n";
        return; 
    }

    std::cout << "\n--- Repartiendo cartas iniciales ---\n";
    repartoInicial(); 

    std::cout << "--- Cartas iniciales listas. ¡Veamos qué tiene cada quien! ---" << std::endl;
    mostrarEstadoJuego(); 


    std::cout << "\n--- Turnos de los jugadores: ¡A jugar! ---" << std::endl;

    for (Participante1 *p : participantes)
    {
        if (Jugador1 *jugador = dynamic_cast<Jugador1 *>(p))
        {
            
            if (jugador->getEstado() == EstadoParticipante::JUGANDO && jugador->getApuesta() > 0)
            {
                std::cout << "\nEs el turno de " << jugador->getNombre() << "." << std::endl;
            
                while (jugador->getEstado() == EstadoParticipante::JUGANDO && jugador->getValorMano() < 21)
                {
                    std::cout << jugador->getNombre() << ", tu mano actual: ";
                    jugador->mostrarMano();
                    std::cout << " (" << jugador->getValorMano() << " puntos)." << std::endl;

                    char decision;
                    std::cout << "Llego la hora de la verdad...";
                    std::cout << "Digite en minúscula (solo la letra) 'p' para pedir carta o 'x' para plantarte: ";
                    std::cin >> decision;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                    decision = std::tolower(decision); 

                    if (decision == 'p')
                    {
                        repartirCarta(jugador);
                        std::cout << jugador->getNombre() << " pide una carta." << std::endl;

                        if (jugador->getValorMano() > 21)
                        {
                            std::cout << jugador->getNombre() << " se ha pasado con " << jugador->getValorMano() << " puntos. ¡Pierde!" << std::endl;
                            jugador->setEstado(EstadoParticipante::PASADO); 
                        }
                        else if (jugador->getValorMano() == 21)
                        {
                            std::cout << jugador->getNombre() << " tiene 21 puntos." << std::endl;
                            
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
                        std::cout << "Opción no válida. Escribe 'p' para pedir o 'x' para plantarte." << std::endl;
                    }
                    mostrarEstadoJuego(); 
                } 

                if (jugador->getEstado() == EstadoParticipante::JUGANDO) 
                {
                    jugador->setEstado(EstadoParticipante::PLANTADO); 
                }
                std::cout << jugador->getNombre() << " ha terminado su turno." << std::endl;
            }
            else
            {
                
                std::cout << jugador->getNombre() << " no participa en esta ronda (estado: "
                          << static_cast<int>(jugador->getEstado()) << " o apuesta 0)." << std::endl;
            }
        }
    }
    std::cout << "\n--- Turno de los Jugadores Finalizado ---" << std::endl;
   
    std::cout << "\n--- Turno del crupier: veamos qué hace la casa... ---" << std::endl;
    if (croupierPrincipal != nullptr)
    {
        croupierPrincipal->setMostrandoCartaOculta(false); 
        std::cout << "El crupier revela su carta oculta..." << std::endl;
        mostrarEstadoJuego(); 

        while (croupierPrincipal->getValorMano() < 17 && croupierPrincipal->getValorMano() <= 21)
        {
            std::cout << "El crupier tiene " << croupierPrincipal->getValorMano() << " puntos. Decide pedir una carta." << std::endl;
            repartirCarta(croupierPrincipal);
            mostrarEstadoJuego();
        }

        if (croupierPrincipal->getValorMano() > 21)
        {
            std::cout << "El crupier se ha pasado con " << croupierPrincipal->getValorMano() << " puntos. ¡Los jugadores restantes ganan esta ronda!" << std::endl;
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
    std::cout << "\n--- El crupier ha terminado su turno. ---" << std::endl;

    std::cout << "\n--- Todos los turnos han finalizado. Veamos los resultados... ---" << std::endl;
    
    definirGanador(); 
    pagarApuestas();  
    terminarJuego(); 

    std::cout << "\n========================================\n";
    std::cout << "           UwU FIN DE LA RONDA UwU          \n";
    std::cout << "========================================\n";
}


/*-------------------------------------------------------------------------------------------------------------------*/
//cuidado con los comentarios de IA!!!!
void Gestionador1::definirGanador()
{
    std::cout << "\n--- RESULTADOS DE LA RONDA ---\n";

    // Obtener datos del croupier
    int valorCroupier = croupierPrincipal->getValorMano();
    bool croupierSePaso = croupierPrincipal->estaPasado();

    // Analizar a cada jugador en el vector de participantes
    for (Participante1 *p : participantes)
    {
        Jugador1 *jugador = dynamic_cast<Jugador1 *>(p);

        // Solo evaluamos jugadores reales que hayan hecho una apuesta
        if (jugador && jugador->getApuesta() > 0)
        {
            int valorJugador = jugador->getValorMano();
            bool jugadorSePaso = jugador->estaPasado();

            std::cout << "\nJugador " << jugador->getNombre()
                      << " tiene " << valorJugador << " puntos. ";

            //  Caso 1: El jugador se pasó de 21 → pierde automáticamente
            if (jugadorSePaso)
            {
                std::cout << "Se pasó de 21. Pierde esta ronda.\n";
                jugador->setEstado(EstadoParticipante::PASADO);
            }
            //  Caso 2: Jugador tiene Blackjack y el croupier no → gana automáticamente
            else if (jugador->tieneBlackjackActivo() && !croupierPrincipal->tieneBlackjackActivo())
            {
                std::cout << "¡Blackjack! Gana automáticamente.\n";
                jugador->setEstado(EstadoParticipante::BLACKJACK);
            }
            //  Caso 3: El croupier se pasó → gana el jugador
            else if (croupierSePaso)
            {
                std::cout << "El croupier se pasó. ¡Gana el jugador!\n";
            }
            // Caso 4: Jugador tiene más puntos que el croupier → gana
            else if (valorJugador > valorCroupier)
            {
                std::cout << "Tiene más puntos que el croupier. ¡Gana!\n";
            }
            //  Caso 5: Jugador tiene menos puntos que el croupier → pierde
            else if (valorJugador < valorCroupier)
            {
                std::cout << "Tiene menos puntos que el croupier. Pierde.\n";
                jugador->setEstado(EstadoParticipante::PASADO);
            }
            //  Caso 6: Empate → recupera su apuesta
            else
            {
                std::cout << "Empate con el crupier. Recupera su apuesta.\n";
                // Aqui no se cambia de estado, no es necesario.
            }
        }
    }

    std::cout << "\n Eso fue todo por esta ronda. ¡Buena suerte en la siguiente!" << std::endl;
std::cout <<   "---------------------------------------------------------------\n";
}

/*-------------------------------------------------------------------------------------------------------------------*/
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
                std::cout << "¡Blackjack! Gana " << apuesta * 2 << " unidades. ¡Bien jugado!" << std::endl;
            }

            // Si el croupier se pasó o el jugador tiene mayor puntuación, gana
            else if (croupierSePaso || valorJugador > valorCroupier)
            {
                std::cout << "Gana " << apuesta << " unidades. ¡Bien jugado!" << std::endl;
            }

            // Si el valor de la mano del jugador es menor al del croupier, pierde
            else if (valorJugador < valorCroupier)
            {
                std::cout << "Pierde su apuesta de " << apuesta << " unidades.¡Vuelve a intentarlo!" << std::endl;
            }

            // Si el jugador y el croupier tienen el mismo puntaje, hay empate
            else
            {
                std::cout << "Empate. Recupera su apuesta de " << apuesta << " unidades. ¡Vuelve pronto!" << std::endl;
            }
        }
    }
}

/*-------------------------------------------------------------------------------------------------------------------*/
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
    std::cout << "----------------------------" << std::endl;
}

/*-------------------------------------------------------------------------------------------------------------------*/
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
    char decisionSalir;
    // Bucle para preguntar hasta que se ingrese 's' o 'S'
    do
    {
        std::cout << "¿Deseas salir del juego? Presione 's' para salir del juego, o cualquier otra tecla para volver al menú: ";
        std::cin >> decisionSalir;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada

        decisionSalir = std::tolower(decisionSalir); // Convertir a minúscula

        if (decisionSalir == 's')
        {
            std::cout << "Saliendo del programa. ¡Gracias por jugar!\n";
            exit(0); // Termina el programa
        }
        else
        {
            std::cout << "Volviendo al menú principal.\n";
            // Si no es 's', el bucle termina y la función retorna,
            // permitiendo al bucle principal del programa (en main) continuar.
            break; // Salir del bucle do-while
        }
    } while (true); // Este bucle solo se romperá con 's' (exit) o con cualquier otra tecla (break)
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
void Gestionador1::agregarJugador(const std::string &nombre)
{
    // crea un nuevo jugador y lo agrega al vector de participantes
    Jugador1 *nuevoJugador = new Jugador1(nombre);
    participantes.push_back(nuevoJugador); // agrega el nuevo jugador al vector de participantes
    std::cout << "Jugador " << nombre << " agregado al juego." << std::endl;
}

/*-------------------------------------------------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------------------------------------*/
int Gestionador1::getNumeroJugadores() const
{
    return participantes.size(); // retorna el numero de participantes en el juego usando el vector
}

/*-----------------------------------------------------------------------------------------------------------------------------*/
// Este método calcula y devuelve el total de todas las apuestas activas,
// sumando las apuestas hechas por cada jugador en la ronda actual. filtra solo apuestas positivas para evitar errores.
int Gestionador1::totalApuestasPartida() const
{
    int total = 0;

    // Recorrer todos los participantes del juego
    for (Participante1 *p : participantes)
    {
        //  Intentamos convertir el participante a Jugador1 para ignorar al croupier
        Jugador1 *jugador = dynamic_cast<Jugador1 *>(p);

        if (jugador)
        {
            // Guardamos la apuesta en una variable local
            int apuesta = jugador->getApuesta();

            // Sumamos solo si la apuesta es positiva (>0)
            if (apuesta > 0)
            {
                total += apuesta;
            }
        }
    }

    // Devolver el total acumulado
    return total;
}

/*-----------------------------------------------------------------------------------------------------------------------------*/

void Gestionador1::reiniciarRonda() {
    std::cout << "\n--- Reiniciando la ronda para todos los participantes y baraja ---\n";
    for (Participante1* p : participantes) {
        if (p != nullptr) {
            p->limpiarMano();
            p->setEstado(EstadoParticipante::JUGANDO); 

            if (Jugador1* jugador = dynamic_cast<Jugador1*>(p)) {
                jugador->setApuesta(0); 
            }
        }
    }
    if (croupierPrincipal != nullptr) {
        croupierPrincipal->setMostrandoCartaOculta(true); 
    }
}

/*--------------------------------------------------------------------------------------------------------------------------*/


