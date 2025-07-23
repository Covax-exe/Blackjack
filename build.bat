@echo off

echo Compilando Blackjack...
g++ main.cpp Baraja1.cpp Carta1.cpp Croupier1.cpp Gestionador1.cpp Jugador1.cpp Mano1.cpp Participante1.cpp -o blackjack.exe

if exist blackjack.exe (
    echo ✅ Compilación exitosa.
    echo Ejecutando...
    blackjack.exe
)
