#ifndef CROUPIER1_H 
#define CROUPIER1_H
#include <string>
#include "Participante1.h" // Incluir la clase base Participante1
class Croupier1 : public Participante1 {
    private:
    bool mostrandoCartaOculta; // Indica si se está mostrando la primera carta oculta del croupier
    public:
    Croupier1(const std::string& nombre); // Constructor con nombre por defecto
    ~Croupier1() override = default; // Destructor virtual para asegurar liberación de recursos, 
                                     //importante señalar que en participante al ya haber un destructor virtual aca lo que hacemos es eliminarlo pero lo agg el override para evitar errores en compilacion.

    bool debePedirCarta() const; // Método para determinar si el croupier debe pedir carta
    void mostrarMano() const override; // Mostrar la mano del croupier, con opción de ocultar la primera carta

    // Métodos para controlar el estado de la visualización de la carta oculta
    void setMostrandoCartaOculta(bool estado);
    bool getMostrandoCartaOculta() const;

};
#endif // CROUPIER1_H   