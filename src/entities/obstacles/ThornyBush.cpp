#include "../../../include/entities/obstacles/ThornyBush.h"
#include <SFML/Window.hpp>

ThornyBush::ThornyBush(float x, float y, bool harm):
    Obstacle(x, y, harm), regenClock(0.0f), active(false) {

    if (!texture_hide.loadFromFile("assets/textures/ThornyBushHide.png")) {
        std::cerr << "Failed to load ThornyBushHide.png!" << std::endl;
    }
    if (!texture_spikes.loadFromFile("assets/textures/ThornyBushSpikes.png")) {
        std::cerr << "Failed to load ThornyBushSpikes.png!" << std::endl;
    }

    texture = texture_hide;
    sprite.setTexture(texture_hide); // Start hidden
    configSprite();
}

ThornyBush::~ThornyBush(){}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void ThornyBush::execute(){
    update();
    draw();
}

void ThornyBush::update() {

    // If the bush is active, and has passed its cooldown,
    // it will hide again
    if (active && regenClock >= THORNYBUSHCOOLDOWN) {
        active = false; // Deactivate after dealing damage
        regenClock = 0.0f; 
        setState(); // Update the texture to show Hide
    }

    regenClock += pGM->getdt();
}

void ThornyBush::obstacleAction(Entity* e){
    if(Player* p = dynamic_cast<Player*>(e)){
        if(!active) {
            active = true; // Activate the spikes when a character collides
            dealDamage(p);
            setState(); // Update the texture to show Spikes
        }
    }
}

void ThornyBush::setState() {
    if (active) {
        sprite.setTexture(texture_spikes);
    } else {
        sprite.setTexture(texture_hide);
    }

    configSprite();
    sprite.setPosition(position);
}

void ThornyBush::collide(Entity* e){
    obstacleAction(e);
    setState();
}

void ThornyBush::dealDamage(Player* p){
    if (p) {
        p->takeDamage(THORNYBUSHSPIKES);
    }
}
