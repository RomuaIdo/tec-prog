#include "../../include/entities/Projectile.h"
#include <SFML/Window.hpp>

Projectile::Projectile(float x, float y, float vel):
    Entity(x,y), velocity(vel){
    if (!texture.loadFromFile("assets/textures/Player1.png")) {
        std::cerr << "Failed to load Player1.png!" << std::endl;
    }    

    texture.setSmooth(true);
    sprite.setTexture(texture);
    size.x = sprite.getLocalBounds().width;
    size.y = sprite.getLocalBounds().height;
    sprite.setScale(    
    size.x / sprite.getLocalBounds().width,
    size.y / sprite.getLocalBounds().height
    );
    active = true;
}

Projectile::~Projectile(){ 
    active = false; 
}

void Projectile::changeActive(){
    active = !active;
}

void Projectile::collide(){
    if(position.x < 0.f || position.x + size.x > 800.f){
        changeActive();
    }
}

void Projectile::draw() {
    if(active){
        pGM->draw(this);
    }
}

Drawable& Projectile::getDrawable() {
    sprite.setPosition(position);
    return sprite;
}

void Projectile::move(){
    position.x += velocity;
}

void Projectile::execute(){
    draw();
    move();
}