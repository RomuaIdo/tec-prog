#include "../../include/entidades/Player.h"
#include <SFML/Window.hpp>

Player::Player(float x, float y, Gerenciador_Grafico *pGG, int p_num = 1): 
    Sprite(), movimentSpeed(50.f), grid_size(50.f), shape(),
    velocity(0.f, 0.f), gg(pGG), player_num(p_num), health(10), vel_max(30.f), 
    gravity(0.f,30.f), friction(0.f, 0.f), friction_coef(0.7)

    {

    shape.setSize(sf::Vector2f(grid_size, grid_size));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

Player::~Player() {}

void Player::handleEvent(const sf::Event &event) {
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {
    case sf::Keyboard::R:
      shape.setFillColor(sf::Color::Red);
      break;
    case sf::Keyboard::G:
      shape.setFillColor(sf::Color::Green);
      break;
    case sf::Keyboard::B:
      shape.setFillColor(sf::Color::Blue);
      break;
    default:
      break;
    }
  }
}

void Player::move() {

    if (player_num == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(shape.getPosition().y + shape.getSize().y >= 600)
                velocity.y += -(movimentSpeed + 1000) * gg->getdt();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x += -movimentSpeed * gg->getdt();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x += movimentSpeed * gg->getdt();
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if(shape.getPosition().y + shape.getSize().y >= 600)
                velocity.y += -(movimentSpeed + 1000) * gg->getdt();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x += -movimentSpeed * gg->getdt();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += movimentSpeed * gg->getdt();
    }

    if (velocity.x > vel_max){
        if(velocity.y > vel_max)
            velocity.y = vel_max;
        velocity.x = vel_max;
    }else if( velocity.y > vel_max){
        if(velocity.x > vel_max)
            velocity.x = vel_max;
        velocity.y = vel_max;
    }
    if (velocity.x < -vel_max){
        if(velocity.y < -vel_max)
            velocity.y = -vel_max;
        velocity.x = -vel_max;
    }else if( velocity.y < -vel_max){
        if(velocity.x < -vel_max)
            velocity.x = -vel_max;
        velocity.y = -vel_max;
    }
    velocity += gravity * gg->getdt();

    if(velocity.x > 0)
        friction.x = -gravity.y * friction_coef;
    else if(velocity.x <0)
        friction.x = gravity.y * friction_coef;
    else 
        friction.x = 0;
    velocity += friction * gg->getdt();
    shape.move(velocity);
    
}

void Player::executar() {
    move();
    colidir();
}

sf::RectangleShape Player::getShape() { return shape; }

void Player::colidir(){
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    float window_width = 800.0f;  // example
    float window_height = 600.0f; // example

    // Left wall
    if (pos.x < 0){
        shape.setPosition(0, pos.y);
        velocity.x = 0;
    }    
    // Right wall
    if (pos.x + size.x > window_width){
        shape.setPosition(window_width - size.x, pos.y);
        velocity.x = 0;
    }   
    // Top wall
    if (pos.y < 0){

        shape.setPosition(pos.x, 0);
        velocity.y = 0;
        // Bottom wall
    }if (pos.y + size.y > window_height){
        shape.setPosition(pos.x, window_height - size.y);
        velocity.y = 0;
    }

}


