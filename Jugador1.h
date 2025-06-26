#ifndef JUGADOR1_H
#define JUGADOR1_H
#include <string>
#include "Participante1.h" // Incluir la clase base Participante1
class Jugador1 : public Participante1
{
private:
    int apuesta; // Apuesta del jugador
public:
    Jugador1(const std::string &nombre, int apuestaInicial = 0); // Constructor con nombre y apuesta inicial
    ~Jugador1() override = default;                              // Destructor virtual para asegurar liberación de recursos,
                                                                 // importante señalar que en participante al ya haber un destructor virtual aca lo que hacemos es eliminarlo pero lo que agg el override para evitar errores en compilacion.
                                                                 // y se le agregó default, esto es que le estás pidiendo al compilador que genere la implementación por defecto para esa función. Es como decirle: "No me compliques, haz lo que harías normalmente si no te dijera nada".

    // Métodos específicos del jugador
    void mostrarMano() const override;
    void realizarApuesta(int cantidad); // Método para que el jugador realice una apuesta
    int getApuesta() const;             // Método para obtener la apuesta actual del jugador
    void setApuesta(int nuevaApuesta);  // Método para establecer una nueva apuesta
};
#endif // JUGADOR1_H
