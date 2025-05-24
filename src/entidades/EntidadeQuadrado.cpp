#include "../../include/entidades/EntidadeQuadrado.h"
#include <SFML/Window.hpp>

EntidadeQuadrado::EntidadeQuadrado(float x, float y, float size, int p_num):
Sprite(){
    player_num = p_num;
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

void EntidadeQuadrado::movePlayer(){
    
    if(player_num == 1){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) shape.move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) shape.move(0, 5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.move(5, 0);
    }else{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) shape.move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) shape.move(0, 5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) shape.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shape.move(5, 0);
    }
}

void EntidadeQuadrado::atualizar() {
    // To implement
    return;
}

void EntidadeQuadrado::executar() {
    atualizar();
    desenhar();
    movePlayer();
    colidir();
}

bool checkCollision(const sf::Sprite& a, const sf::Sprite& b) {
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

void EntidadeQuadrado::colidir(){ return; }

sf::RectangleShape* EntidadeQuadrado::getShape(){ return &shape; }

// Check if sprite is out of window bounds
void EntidadeQuadrado::fixCollisionWithWindow(sf::Shape* sprite, const sf::RenderWindow& window) {
    sf::FloatRect bounds = sprite->getGlobalBounds();
    sf::Vector2u winSize = window.getSize();

    if (bounds.left < 0)
        sprite->setPosition(0, sprite->getPosition().y);
    if (bounds.top < 0)
        sprite->setPosition(sprite->getPosition().x, 0);
    if (bounds.left + bounds.width > winSize.x)
        sprite->setPosition(winSize.x - bounds.width, sprite->getPosition().y);
    if (bounds.top + bounds.height > winSize.y)
        sprite->setPosition(sprite->getPosition().x, winSize.y - bounds.height);
}
