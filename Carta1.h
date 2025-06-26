#ifndef CARTA1_H
#define CARTA1_H
#include <string>

class Carta1 {
    public:
    enum Palo { CORAZONES, DIAMANTES, TREBOLES, PICAS }; //C++ le asigna automáticamente valores enteros a los enums, comenzando desde 0.
    enum Valor { DOS = 2, TRES = 3, CUATRO = 4, CINCO = 5,SEIS = 6, SIETE = 7, OCHO = 8, NUEVE = 9, DIEZ = 10,J = 10, Q = 10, K = 10, AS = 11 }; // Valor numérico directo
    // Constructor
    Carta1(Palo p, Valor v);
    std::string toString() const; // Genera la cadena de texto de la carta
    int getValorNumerico() const;
    // Getters para los ENUMS internos
    Palo getPaloEnum() const;
    Valor getValorEnum() const;
    private:// <-- Sección privada después de declararse los enums de palo y valor, para evitar errores en compilación.
    Palo palo_enum;
    Valor valor_enum; //declaracion de variables miembros para almacenar el palo y el valor de la carta.
};
#endif // CARTA1_H