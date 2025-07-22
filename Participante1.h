#ifndef PARTICIPANTE1_H
#define PARTICIPANTE1_H

#include <string>
#include "Mano1.h" // Incluir Mano1.h para que Participante1 conozca la clase Mano1
#include "Carta1.h" // También necesario si los métodos del participante interactúan con cartas

enum class EstadoParticipante {
    JUGANDO,     // El participante está activo y puede tomar decisiones
    PLANTADO,    // El participante ha decidido no pedir más cartas
    PASADO,      // El valor de la mano del participante ha excedido 21
    BLACKJACK,// El participante tiene un Blackjack (21 con dos cartas)
    RETIRADO, //El participante se retira y se le devuelve el 30% de la apuesta hecha.
    // Puedes añadir RETIRADO/SURRENDERED si implementas esa opción
    // RETIRADO,
};


class Participante1 {
private:
    std::string nombre;
    Mano1 mano; // <<--- Cada participante TIENE UNA Mano1
    EstadoParticipante estadoActual;

public:
    Participante1(const std::string& n);
    // Destructor virtual para manejo polimórfico de memoria
    virtual ~Participante1() = default;

    // Métodos virtuales para el comportamiento polimórfico
    virtual void recibirCarta(Carta1* carta); // El participante recibe la carta y se la pasa a su mano
    virtual void mostrarMano() const; // El participante le pide a su mano que se muestre
    virtual int getValorMano() const; // El participante le pide el valor a su mano
    virtual std::string getNombre() const;
    virtual bool tieneBlackjack() const; // El participante le pregunta a su mano si tiene Blackjack

    // Otros métodos específicos de participante si los tienes
    void limpiarMano(); // Un método para resetear la mano (vaciarla)

    // <--- Nuevos métodos para gestionar el estado
    void setEstado(EstadoParticipante nuevoEstado);
    EstadoParticipante getEstado() const;

    // Métodos de conveniencia para verificar el estado
    bool estaJugando() const;
    bool estaPlantado() const;
    bool estaPasado() const;
    bool tieneBlackjackActivo() const; // Diferente de 'tieneBlackjack()' de Mano1, este es un estado.
    // Métodos para acceder a información de la mano (solo lectura segura)
    const Mano1& getMano() const;            // Permite acceder a la mano en modo lectura (sin modificar)
    int getNumeroCartas() const;             // Devuelve el número de cartas en la mano
    const Carta1* getCarta(int indice) const; // Devuelve una carta específica por índice

};

#endif // PARTICIPANTE1_H

/*Las funciones polimórficas, o métodos virtuales, permiten que diferentes clases (como Jugador1 y Croupier1 que son tipos de Participante1)
respondan de forma distinta al mismo mensaje (una llamada a función).
Cuando marcamos un método como virtual en la clase base (Participante1), 
le indicamos al compilador que la implementación a usar se debe decidir en el momento en que el programa se ejecuta, 
no al compilar. Esto depende del tipo real del objeto.*/
