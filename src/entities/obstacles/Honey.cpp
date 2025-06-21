#include "../../../include/entities/obstacles/Honey.h"
#include <SFML/Window.hpp>

Honey::Honey()
    : Obstacle(), viscosity(0.f){

    texture = pGM->loadTexture("assets/textures/Honey.png");

    sprite.setTexture(texture);
    configSprite();
}

Honey::Honey(float x, float y, bool harm):
    Obstacle(x,y,harm), viscosity(HONEYVISCOSITY){
    texture = pGM->loadTexture("assets/textures/Honey.png");

    sprite.setTexture(texture);
    configSprite();
}

Honey::~Honey(){}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Honey::execute(){
    draw();
}

void Honey::obstacleAction(Entity* e){
    if (e) {
        Player* player = dynamic_cast<Player*>(e);
        if (player) {
            player->setVelocity(player->getVelocity() * viscosity);
            // if(dynamic_cast<Player*>(character)){
            //     // static_cast<Player*>(character)->setJumpForce(PLAYERJUMPFORCE * viscosity);
            // }
        }
    }
}

void Honey::collide(Entity* e){
    obstacleAction(e);
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json Honey::toJson() const {
    return {
        {"type", getType()},
        {"position_x", position.x},
        {"position_y", position.y},
        {"viscosity", viscosity}
    };
}

void Honey::fromJson(const json& j) {
    position.x = j.at("position_x");
    position.y = j.at("position_y");
    viscosity = j.at("viscosity");
}

std::string Honey::getType() const {
    return "Honey";
}


/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Honey::setViscosity(float v){
    viscosity = v;
}

float Honey::getViscosity() const {
    return viscosity;
}


