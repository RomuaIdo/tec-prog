#include "../../../include/entities/characters/Player.h"
#include <SFML/Window.hpp>

Player::Player(float x, float y, const float acel, int life, float coef, int s, int p_num, const float v_max): 
    Character(x, y, acel, life, coef, s), player_num(p_num), score(0), vel_max(v_max){

    
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

void Player::handleEvent(const sf::Event &event) {
    return;
}


void Player::move() {

    if (player_num == 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(velocity.y == 0)
                velocity.y += -(15);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x += -aceleration * pGM->getdt();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x += aceleration * pGM->getdt();
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if(velocity.y == 0)
                velocity.y += -(15);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x += -aceleration * pGM->getdt();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += aceleration * pGM->getdt();
    }

    const float vel_max = 15.f;

    // See if velocity ultrapassed vel_max
    if (velocity.x > vel_max){
        velocity.x = vel_max;
    }
    if (velocity.x < -vel_max){
        velocity.x = -vel_max;
    }

    // Apply friction
    if(velocity.x > 0){
        friction.x = -20.f * friction_coef;
        if(velocity.x + friction.x * pGM->getdt() < 0) {
           velocity.x = 0;
            friction.x = 0;
        }
    }
    else if(velocity.x < 0){
        friction.x = 20.f * friction_coef;
        if(velocity.x + friction.x * pGM->getdt() > 0) {
            velocity.x = 0;
            friction.x = 0;
        }
    }
    else
        friction.x = 0;
        
    velocity += friction * pGM->getdt();
    moveCharacter();
    
}

void Player::collide(){
    velocity = Vector2f(velocity.x * -0.1f, velocity.y * -0.1f);
}

void Player::execute() {
    move();
    draw();
}

void Player::loseHealth(int damage){
    health -= damage;
}

int Player::getHealth(){
    return health;
}
