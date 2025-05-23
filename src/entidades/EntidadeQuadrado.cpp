#include "../../include/entidades/EntidadeQuadrado.h"
#include <SFML/Window.hpp>

EntidadeQuadrado::EntidadeQuadrado(float x, float y, float size) {
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

void EntidadeQuadrado::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::R: shape.setFillColor(sf::Color::Red); break;
            case sf::Keyboard::G: shape.setFillColor(sf::Color::Green); break;
            case sf::Keyboard::B: shape.setFillColor(sf::Color::Blue); break;
            default: break;
        }
    }
}

void EntidadeQuadrado::desenhar() {
    pGG->desenhar(shape); // Usa o Gerenciador Gráfico
}

void EntidadeQuadrado::atualizar() {
    // Movimento contínuo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) shape.move(0, -5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) shape.move(0, 5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.move(-5, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.move(5, 0);
}

void EntidadeQuadrado::executar() {
    atualizar();
    desenhar();
}

void EntidadeQuadrado::colidir(Entidade* outra) {
    // Implementação de colisão (opcional)
}
