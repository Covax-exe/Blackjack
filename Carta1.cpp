#include "Carta1.h"
#include <string>
Carta1::Carta1(Palo p, Valor v)
    : palo_enum(p), valor_enum(v) // Constructor que inicializa el palo y el valor de la carta, CON EL TIPO DE VARIBALE QUE DICTA EL ENUM CORRESpondiente
{
}
std::string Carta1::toString() const
{
    std::string paloStr;
    switch (palo_enum)
    {
    case CORAZONES:
        paloStr = "Corazones";
        break;
    case DIAMANTES:
        paloStr = "Diamantes";
        break;
    case TREBOLES:
        paloStr = "Treboles";
        break;
    case PICAS:
        paloStr = "Picas";
        break;
    }
    std::string valorStr;
    switch (valor_enum)
    {
    case DOS:
        valorStr = "2";
        break;
    case TRES:
        valorStr = "3";
        break;
    case CUATRO:
        valorStr = "4";
        break;
    case CINCO:
        valorStr = "5";
        break;
    case SEIS:
        valorStr = "6";
        break;
    case SIETE:
        valorStr = "7";
        break;
    case OCHO:
        valorStr = "8";
        break;
    case NUEVE:
        valorStr = "9";
        break;
    case DIEZ:
        valorStr = "10";
        break;
    case J:
        valorStr = "J";
        break;
    case Q:
        valorStr = "Q";
        break;
    case K:
        valorStr = "K";
        break;
    case AS:
        valorStr = "A";
        break;
    }

    return valorStr + " de " + paloStr; // Retorna la representación en cadena de la carta
}

// metodo para obtener el valor numérico de la carta
int Carta1::getValorNumerico() const
{
    return static_cast<int>(valor_enum);
}
// Getters para los ENUMS internos
Carta1::Palo Carta1::getPaloEnum() const
{
    return palo_enum;
}
Carta1::Valor Carta1::getValorEnum() const
{
    return valor_enum;
}
// Fin de la implementación de Carta1.cpp