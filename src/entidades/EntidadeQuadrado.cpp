#include "../../include/entidades/EntidadeQuadrado.h"
#include <SFML/Window.hpp>

EntidadeQuadrado::EntidadeQuadrado(float x, float y, float size, int p_num){
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

void EntidadeQuadrado::colidir() {
    sf::Vector2f player_pos = shape.getPosition();
    if(player_pos.x <= 0){
        shape.setPosition(0, player_pos.y);
    }
    else if(player_pos.x >= 800){
        shape.setPosition(800, player_pos.y);
    }
    if(player_pos.y <= 0){
        shape.setPosition(player_pos.x, 0);
    }
    else if(player_pos.y >= 600){
        shape.setPosition(player_pos.x, 600);
    }
}
