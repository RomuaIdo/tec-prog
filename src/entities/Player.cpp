#include "../../include/entities/Player.h"
#include "../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>

Player::Player(const float size, float x, float y, const float movSpeed, int life, float coef, int s, int p_num, const float v_max): 
    Character(size, x, y, movSpeed, life, coef, s), player_num(p_num), score(0), vel_max(v_max){

    if (!texture.loadFromFile("../../sprites/PlayerSprite.png", sf::IntRect({x, y}, {50, 80}))) {
        std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
    }    
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(    
    shape.getSize().x / sprite.getLocalBounds().width,
    shape.getSize().y / sprite.getLocalBounds().height
    );
    // if(p_num == 1)
    //     shape.setFillColor(sf::Color::Green);
    // else 
    //     shape.setFillColor(sf::Color::Blue);
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
                velocity.y += -(movimentSpeed + 1000) * pGM->getdt();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x += -movimentSpeed * pGM->getdt();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x += movimentSpeed * pGM->getdt();
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if(shape.getPosition().y + shape.getSize().y >= 600)
                velocity.y += -(movimentSpeed + 1000) * pGM->getdt();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x += -movimentSpeed * pGM->getdt();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += movimentSpeed * pGM->getdt();
    }

    moveCharacter();
    
}

void Player::execute() {
    move();
    collide();
    draw();
}

void Player::loseHealth(int damage){
    health -= damage;
}

int Player::getHealth(){
    return health;
}
