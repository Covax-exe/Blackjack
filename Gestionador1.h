#ifndef GESTIONADOR1_H
#define GESTIONADOR1_H
#include <vector>
#include <string>
#include "Baraja1.h"
#include "Croupier1.h"
#include "Jugador1.h"
#include "Carta1.h"
#include "Participante1.h"
// Jugador1* nuevoJugador = new Jugador1(nombre); // Asume que Jugador1 tiene un constructor con string nombre
class Gestionador1
{
private:
    std::vector<Jugador1 *> jugadores;
    Croupier1 *croupier;
    Baraja1 baraja;

public:
    Gestionador1();
    ~Gestionador1();
    void iniciarJuego(); // Versión sin reglas explícitas
    void ejecutarTurno();
    void definirGanador();
    void pagarApuestas();
    void mostrarEstadoJuego() const;
    void reiniciarJuego();
    void repartirCartas(Participante1 *participante);
    void agregarJugador(const std::string &nombre);
    void abrirApuestas();
    Jugador1 *getJugador(int indice);
    int getNumeroJugadores() const;
};
#endif // GESTIONADOR1_H
