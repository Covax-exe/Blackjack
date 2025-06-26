#include <SFML/Graphics.hpp>
#include "Carta1.h"
#include "Baraja1.h"
#include "Jugador1.h"
#include "Croupier1.h"
#include "Mano1.h"
#include <vector>
#include <string>
#include <sstream>
#include <map>

// Función para obtener el nombre del archivo de una carta
std::string cartaATextoArchivo(const Carta &carta)
{
    std::string nombre;

    if (carta.getValor() == 1)
        nombre = "A";
    else if (carta.getValor() == 11)
        nombre = "J";
    else if (carta.getValor() == 12)
        nombre = "Q";
    else if (carta.getValor() == 13)
        nombre = "K";
    else
        nombre = std::to_string(carta.getValor());

    switch (carta.getPalo())
    {
    case 'T':
        nombre += "S";
        break; // ♠
    case 'E':
        nombre += "H";
        break; // ♥
    case 'C':
        nombre += "C";
        break; // ♣
    case 'D':
        nombre += "D";
        break; // ♦
    }

    return "cartas/" + nombre + ".png"; // Ruta de la imagen
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 720), "Blackjack");
    window.setFramerateLimit(60);

    // Fuente elegante
    sf::Font casinoFont;
    if (!casinoFont.loadFromFile("Playbill.ttf"))
    {
        return 1;
    }

    // Título del juego
    sf::Text titulo("BLACKJACK", casinoFont, 60);
    titulo.setFillColor(sf::Color::Yellow);
    titulo.setPosition(350, 20);

    // Baraja y jugadores
    Baraja baraja;
    Jugador jugador("Jugador");
    Croupier crupier;
    jugador.recibirCarta(baraja.sacarCarta());
    jugador.recibirCarta(baraja.sacarCarta());
    crupier.recibirCarta(baraja.sacarCarta());

    // Botón PEDIR
    sf::RectangleShape botonPedir({150, 50});
    botonPedir.setPosition(150, 620);
    botonPedir.setFillColor(sf::Color(200, 200, 200));
    sf::Text textoPedir("PEDIR", casinoFont, 30);
    textoPedir.setFillColor(sf::Color::Black);
    textoPedir.setPosition(180, 627);

    // Botón PLANTARSE
    sf::RectangleShape botonPlantarse({150, 50});
    botonPlantarse.setPosition(350, 620);
    botonPlantarse.setFillColor(sf::Color(200, 200, 200));
    sf::Text textoPlantarse("PLANTARSE", casinoFont, 24);
    textoPlantarse.setFillColor(sf::Color::Black);
    textoPlantarse.setPosition(360, 630);

    // Texturas dinámicas para cartas
    std::map<std::string, sf::Texture> cacheTexturas;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Clics en los botones
            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto mouse = sf::Mouse::getPosition(window);
                if (botonPedir.getGlobalBounds().contains(mouse.x, mouse.y))
                {
                    jugador.recibirCarta(baraja.sacarCarta());
                }
                if (botonPlantarse.getGlobalBounds().contains(mouse.x, mouse.y))
                {
                    crupier.jugar(baraja);
                }
            }
        }

        window.clear(sf::Color(0, 120, 0)); // fondo verde casino
        window.draw(titulo);
        window.draw(botonPedir);
        window.draw(textoPedir);
        window.draw(botonPlantarse);
        window.draw(textoPlantarse);

        // Dibujar cartas del jugador
        std::vector<Carta> cartasJugador = jugador.getMano().getCartas();
        for (size_t i = 0; i < cartasJugador.size(); ++i)
        {
            std::string archivo = cartaATextoArchivo(cartasJugador[i]);
            if (!cacheTexturas[archivo].loadFromFile(archivo))
                continue;
            sf::Sprite sprite(cacheTexturas[archivo]);
            sprite.setScale(0.4f, 0.4f);
            sprite.setPosition(100 + i * 80, 400);
            window.draw(sprite);
        }

        // Dibujar cartas del crupier
        std::vector<Carta> cartasCrupier = crupier.getMano().getCartas();
        for (size_t i = 0; i < cartasCrupier.size(); ++i)
        {
            std::string archivo = cartaATextoArchivo(cartasCrupier[i]);
            if (!cacheTexturas[archivo].loadFromFile(archivo))
                continue;
            sf::Sprite sprite(cacheTexturas[archivo]);
            sprite.setScale(0.4f, 0.4f);
            sprite.setPosition(100 + i * 80, 200);
            window.draw(sprite);
        }

        window.display();
    }

    return 0;
}
