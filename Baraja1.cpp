#include "Baraja1.h"
#include "Carta1.h"
#include <vector>
#include <string>
#include <algorithm> // Para usar std::random_shuffle o std::shuffle
#include <random> // Para generar números aleatorios
#include <chrono>   // Para obtener una semilla basada en el tiempo actual
#include <iostream> // Para imprimir mensajes en la consola


//static_cast<TipoDeseado>(expresion_a_convertir);

Baraja1::Baraja1() {
    // Itera por cada palo y valor para crear las 52 cartas únicas.
    // 'static_cast' convierte los 'int' del bucle de vuelta a los tipos 'enum' de Carta1
    // que el constructor de Carta1 espera.
    // Inicializa la baraja con 52 cartas
    for (int palo = Carta1::CORAZONES; palo <= Carta1::PICAS; ++palo) {
        for (int valor = Carta1::DOS; valor <= Carta1::AS; ++valor) {
            cartas.push_back(new Carta1(static_cast<Carta1::Palo>(palo), static_cast<Carta1::Valor>(valor)));
        }
    }
    barajar(); // Baraja las cartas al inicializar la baraja
}
Baraja1::~Baraja1() {
    // Destructor para liberar memoria de las cartas, recorre el vector de cartas y elimina cada puntero.
    for (Carta1* carta : cartas) {
        delete carta; // Libera la memoria de cada carta
    }
    cartas.clear(); // Limpia el vector de cartas
}

/*ahora, para desordenar un vector, o en este caso "Barajar" el vector que contiene los punteros a las cartas, 
se puede usar la función std::shuffle de la siguiente manera:*/

// Implementación del método barajar()
void Baraja1::barajar() {
    // 1. Obtener una semilla (seed) para el generador de números aleatorios
    //    Usamos el tiempo actual del sistema con alta resolución.
    //    Esto asegura que cada vez que barajes, obtengas una secuencia de cartas diferente.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //  ^ unsigned: Un tipo entero sin signo para la semilla.
    //  ^ std::chrono::system_clock::now(): Obtiene el punto de tiempo actual del reloj del sistema.
    //  ^ .time_since_epoch(): Calcula la duración desde el inicio de la "era" del reloj (ej. 1/1/1970).
    //  ^ .count(): Convierte esa duración en un número entero (ej. el número de nanosegundos desde el epoch).

    // 2. Crear una instancia del generador de números aleatorios, sembrándolo
    //    con el valor que acabamos de obtener.
    std::default_random_engine rng(seed);
    //  ^ std::default_random_engine: El tipo de generador de números aleatorios.
    //  ^ rng: El nombre de nuestra instancia del generador (Random Number Generator).
    //  ^ (seed): Inicializa el generador con nuestra semilla basada en el tiempo.

    // 3. Usar std::shuffle para desordenar el vector 'cartas'
    //    std::shuffle(primer_elemento, elemento_despues_del_ultimo, generador_aleatorio);
    std::shuffle(cartas.begin(), cartas.end(), rng);
    //  ^ cartas.begin(): Un iterador que apunta al primer elemento del vector 'cartas'.
    //  ^ cartas.end(): Un iterador que apunta a la posición justo después del último elemento del vector 'cartas'.
    //                  Esto define el rango de elementos que se van a barajar.
    //  ^ rng: La instancia de nuestro generador de números aleatorios que std::shuffle utilizará para decidir cómo mezclar.
    /*Nota: std::shuffle es una funcion de algoritmo de la STL (Standard Template Library) que mezcla los elementos de un rango dado utilizando un generador de números aleatorios
    por lo que sirve para aplicar en otros contextos donde se usen contenedores o de las librerias de STL.*/
}
Carta1* Baraja1::repartirCarta() {
    if (cartas.empty()) {
        std::cout << "No hay cartas disponibles para repartir :( ." << std::endl;
        return nullptr; // Si no hay cartas, retorna nullptr
    }
    
    // Obtiene el puntero a la primera carta del vector (la "carta superior" del mazo)
    Carta1* carta = cartas.front(); 
    
    // Elimina esa carta del vector. Esto asegura que no se repita.
    cartas.erase(cartas.begin()); 
    
    // Imprime la carta repartida. Esto ahora se ejecutará.
    std::cout << "Carta repartida con exito!: " << (*carta).toString() << std::endl; 
    
    // Retorna el puntero a la carta repartida.
    return carta; 
}


int Baraja1::getNumeroCartas() const {
    return cartas.size(); // Retorna el número de cartas restantes en la baraja
}

























