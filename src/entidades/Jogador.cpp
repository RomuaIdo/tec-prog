#include "../../include/entidades/Jogador.h"
#include <SFML/Window.hpp>

Jogador::Jogador(float x, float y, float size, int p_num, Gerenciador_Grafico* pgg) : Entidade() {
    pGG = pgg;
    player_num = p_num;
    shape.setSize(Vector2f(size, size));
    shape.setPosition(x, y);
    shape.setFillColor(Color::Green);
}

void Jogador::handleEvent(const Event& event) {
    if (event.type == Event::KeyPressed) {
        switch (event.key.code) {
            case Keyboard::R: shape.setFillColor(Color::Red); break;
            case Keyboard::G: shape.setFillColor(Color::Green); break;
            case Keyboard::B: shape.setFillColor(Color::Blue); break;
            default: break;
        }
    }
}

void Jogador::desenhar() {
    pGG->desenhar(this); // Usa o Gerenciador Gráfico
}

Drawable& Jogador::getDrawable() {
    return shape;
}

void Jogador::movePlayer(){
    
    if(player_num == 1){
        if (Keyboard::isKeyPressed(Keyboard::Up)) shape.move(0, -5);
        if (Keyboard::isKeyPressed(Keyboard::Down)) shape.move(0, 5);
        if (Keyboard::isKeyPressed(Keyboard::Left)) shape.move(-5, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right)) shape.move(5, 0);
    }else{
        if (Keyboard::isKeyPressed(Keyboard::W)) shape.move(0, -5);
        if (Keyboard::isKeyPressed(Keyboard::S)) shape.move(0, 5);
        if (Keyboard::isKeyPressed(Keyboard::A)) shape.move(-5, 0);
        if (Keyboard::isKeyPressed(Keyboard::D)) shape.move(5, 0);
    }
}

void Jogador::atualizar() {
    // To implement
    return;
}

void Jogador::executar() {
    atualizar();
    desenhar();
    movePlayer();
    colidir();
}

bool checkCollision(const Sprite& a, const Sprite& b) {
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

void Jogador::colidir(){ return; }

RectangleShape* Jogador::getShape(){ return &shape; }

// Check if sprite is out of window bounds
void Jogador::fixCollisionWithWindow(Shape* sprite, const RenderWindow& window) {
    FloatRect bounds = sprite->getGlobalBounds();
    Vector2u winSize = window.getSize();

    if (bounds.left < 0)
        sprite->setPosition(0, sprite->getPosition().y);
    if (bounds.top < 0)
        sprite->setPosition(sprite->getPosition().x, 0);
    if (bounds.left + bounds.width > winSize.x)
        sprite->setPosition(winSize.x - bounds.width, sprite->getPosition().y);
    if (bounds.top + bounds.height > winSize.y)
        sprite->setPosition(sprite->getPosition().x, winSize.y - bounds.height);
}
