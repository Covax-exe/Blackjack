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
    std::vector<Participante1 *> participantes;
    Croupier1 *croupierPrincipal;
    Baraja1 baraja;
    int totalApuestasJuego;

public:
    Gestionador1();
    ~Gestionador1();
    void repartirUnaCarta(Participante1 *participante);
    void iniciarJuego(); // Versión sin reglas explícitas
    void ejecutarTurno();
    void definirGanador();
    void pagarApuestas();
    void mostrarEstadoJuego() const;
    void terminarJuego();
    void repartoInicial();
    void agregarJugador(const std::string &nombre);
    void abrirApuestas();
    Jugador1 *getJugador(int indice);
    int getNumeroJugadores() const;
    int totalApuestasPartida() const;
    void mostrarIndicesJugadores() const;
};
#endif // GESTIONADOR1_H
