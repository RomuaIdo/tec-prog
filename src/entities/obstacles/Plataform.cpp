#include "../../../include/entities/obstacles/Plataform.h"
#include "../../../include/entities/characters/Enemy.h"
#include "../../../include/entities/characters/Player.h"
#include <SFML/Window.hpp>

Plataform::Plataform() 
    : Obstacle(), width(0.f), height(0.f) {
    
}

Plataform::Plataform(float x, float y, bool harm)
    : Obstacle(x, y, harm){
    if (!texture.loadFromFile("assets/textures/Honey.png")) {
        cerr << "Failed to load Plataform.png!" << std::endl;
    }
    sprite.setTexture(texture);
    configSprite();
}

Plataform::~Plataform() {}

void Plataform::collide(Entity *other) {
    if (Player *player = dynamic_cast<Player *>(other)) {
        obstacleAction(player);
    } else if (Enemy *enemy = dynamic_cast<Enemy *>(other)) {
        obstacleAction(enemy);
    }
}

void Plataform::execute() { draw(); }


void Plataform::obstacleAction(Entity *e) {
    if (e) {
        Character *character = dynamic_cast<Character *>(e);
        if (character) {
            Vector2f velocity = character->getVelocity();
            character->setVelocity(velocity);
        }
    }
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Plataform::setHeight(float h) { height = h; }

void Plataform::setWidth(float w) { width = w; }

float Plataform::getHeight() const { return height; }

float Plataform::getWidth() const { return width; }
