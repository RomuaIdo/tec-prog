#include "../../../../include/entities/characters/enemies/Saci.h"

Saci::Saci(float x, float y, const float acel, int life, float coef, int s) :
    Enemy(x, y, acel, life, coef, s), far(false), teleportTime(0.f),
    lastPosition(Vector2f(x,y)){

    if (!texture.loadFromFile("assets/textures/Saci.png")) {
            std::cerr << "Failed to load Saci.png!" << std::endl;
    }
    sprite.setTexture(texture);
    configSprite();

    teleportTime = 5.f; // Set teleport time to 5 seconds
    lastPositionTime = 0.f;
}

Saci::~Saci() {
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Saci::execute() {
    move();
    draw();
    teleport(getPlayerLastPosition());
}

void Saci::move() {
    float closer = sqrt(pGM->getWindow()->getSize().x * pGM->getWindow()->getSize().x + 
    pGM->getWindow()->getSize().y * pGM->getWindow()->getSize().y);
    Vector2f closer_direction = Vector2f(0.f,0.f);

    for(list<Player*>::iterator it = players_list.begin(); it != players_list.end(); it++){
        if(*it){
            // Get direction to player (feet to feet)
            Vector2f direction = ( ((*it)->getPosition() + (*it)->getSize()) - (position + size) );
            float module = sqrt(direction.x*direction.x + direction.y*direction.y);

            if(module < closer){
                closer = module;
                closer_direction = direction;
                if(lastPositionTime >= 2.f){
                    lastPosition = (*it)->getPosition();
                    lastPositionTime = 0.f;
                }
            }else{
                lastPosition = position;
            }
            lastPositionTime += pGM->getdt();
        }
    }
    if(abs(closer_direction.x) < 300.f){
        far = false;
    }else{
        far = true;
    }

    if(closer_direction.x < 0){
        faced_right = -1;
    }else{
        faced_right = 1;
    }
    if(!far){
        velocity.x = faced_right*(aceleration - 5);
        // para reaproveitar o lastPositionTime e pular a cada 2 seg
        if(!getInAir() && lastPositionTime >= 2.f) {
            velocity.y = -aceleration;
            setInAir(true);
        }
    }else{
        velocity.x = 0.f;
    }
    moveCharacter();
}

void Saci::collide(Entity* e) {
    Vector2f ePos = e->getPosition();
    Vector2f eSize = e->getSize();

    float dx = (position.x - ePos.x);
    float dy = (position.y - ePos.y);

    Vector2f intersection = Vector2f( abs(dx) - (size.x + eSize.x), 
                                      abs(dy) - (size.y + eSize.y) );

    if (intersection.x < 0.0f && intersection.y < 0.0f) {

        /* If intersection in x is less then intersection in y */
        /*  means that they are side by side                 */

        if (std::abs(intersection.x) < std::abs(intersection.y)) {
            
            /* To push the character the amount he is inside */                       
            float push = abs(intersection.x / 2.f);

            if (dx > 0) {
                position.x += push;
                setVelocity({0.f + push, getVelocity().y});
            }
            else{
                position.x -= push;
                setVelocity({0.f - push, getVelocity().y});
            } 
        /* If intersection in y is less then intersection in x */
        /*  means that character collided in y with obstacle */
        } else {

            /* To push the character the amount he is inside */ 
            float push = abs(intersection.y / 2.f);

            /* c is below o */
            if (dy > 0) {

                position.y += push;

            /* c is on top of o */
            } else {

                /* c can jump */
                setInAir(false);
                position.y -= push;
                
                setVelocity({ getVelocity().x, 0.f });
            }
        }
        setPosition(position);
        // If the entity is a Player, attack it
        if(dynamic_cast<Player*>(e)) {
            Player *p = static_cast<Player*>(e);
            if(p) {
                attack(p);
            }
        }
    }
}

Vector2f Saci::getPlayerLastPosition(){
    return lastPosition;
}

void Saci::teleport(Vector2f pos) {
    if(!far && clock >= teleportTime) {
        cout << "Saci is teleporting" <<endl;
        clock = 0;
        setPosition(pos);
    }else{
        clock += pGM->getdt();
    }
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Saci::attack(Player *p) {
    /* If player has health and after 2 seconds, then he can attack */
    if(p->getHealth() > 0 && pGM->getClockTime() >= 2.f){
        p->takeDamage(strength);
        pGM->resetClock();
    }
}
