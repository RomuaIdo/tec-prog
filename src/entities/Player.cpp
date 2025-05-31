#include "../../include/entities/Player.h"
#include "../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>

Player::Player(float x, float y, const float movSpeed, int life, float coef, int s, int p_num, const float v_max): 
    Character(x, y, movSpeed, life, coef, s), player_num(p_num), score(0), vel_max(v_max){

    
    if(p_num == 1){
        if (!texture.loadFromFile("assets/textures/Player1Sprite.png")) {
            std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
        }    
    }
    else {
        if (!texture.loadFromFile("assets/textures/Player2Sprite.png")) {
            std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
        }  
    }
    
    texture.setSmooth(true);
    sprite.setTexture(texture);
    size.x = sprite.getLocalBounds().width;
    size.y = sprite.getLocalBounds().height;
    sprite.setScale(    
        size.x / sprite.getLocalBounds().width,
        size.y / sprite.getLocalBounds().height
    );

}

Player::~Player() {}



void Player::move() {

    if (player_num == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(position.y + size.y >= 600)
                velocity.y += -(movimentSpeed + 1000) * pGM->getdt();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x += -movimentSpeed * pGM->getdt();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x += movimentSpeed * pGM->getdt();
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if(position.y + size.y >= 600)
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
