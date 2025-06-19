#include "../../../../include/entities/characters/enemies/Saci.h"

Saci::Saci(float x, float y, const float acel, int life, int s) :
    Enemy(x, y, acel, life, s), jumpClock(0.f), lastPositionClock(0.f), 
    teleportClock(0.f), lastPosition(Vector2f(x,y)){


    if (!texture.loadFromFile("assets/textures/Saci.png")) {
            std::cerr << "Failed to load Saci.png!" << std::endl;
    }

    evilness = SACIEVILNESS;
    sprite.setTexture(texture);
    configSprite();
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
    verifyDeadPlayers();
    updateClocks();
}

void Saci::move() {

    float closer = 100000.f;
    float right = 1.f;

    for(list<Player*>::iterator it = players_list.begin(); it != players_list.end(); it++){
        if(*it){

            // Get direction to player (feet to feet)
            Vector2f direction = ( ((*it)->getPosition() + Vector2f( 0.f, (*it)->getSize().y)) - (position + Vector2f( 0.f, size.y)) );

            float module = sqrt(direction.x*direction.x + direction.y*direction.y);

            if(module < closer){

                // See if closer is in right or left
                right = direction.x;

                closer = module;

                if(lastPositionClock >= 1.f){
                    lastPosition = Vector2f((*it)->getPosition().x, pGM->getWindow()->getSize().y - size.y);
                    lastPositionClock = 0.f;
                }
            }
        }
    }

    // if it is 600 pixels far, the enemy dont move
    if(abs(right) < SACIFAR){
        far = false;
    }else{
        far = true;
    }
 
    faced_right = (int) (right/abs(right));

    if(!far){
        if(!getInAir() && jumpClock >= JUMPCOOLDOWN) {
            setInAir(true);
            velocity = (Vector2f( faced_right * aceleration, -SACIJUMPFORCE ));
            jumpClock = 0.f;
        }
    }
    
    // Stop after jumping
    if(!getInAir()){
        velocity = Vector2f(0.f, 0.f);
    }

    applyGravity();
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

        float push = 0.f;
        if (std::abs(intersection.x) < std::abs(intersection.y)) {
            /* To push the character the amount he is inside */    
            if(dynamic_cast<Plataform*>(e)){
                push = abs(intersection.x);
            }                   
            else 
                push = abs(intersection.x / 2.f);

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
            if(dynamic_cast<Plataform*>(e)){
                push = abs(intersection.y);
            }                   
            else 
                push = abs(intersection.y / 2.f);

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

void Saci::updateClocks(){
    float dt = pGM->getdt();
    jumpClock += dt;
    lastPositionClock += dt;
    teleportClock += dt;
}

/* ------------------------------------------- */
/*              TELEPORT FUNCTIONS             */
/* ------------------------------------------- */

Vector2f Saci::getPlayerLastPosition(){
    return lastPosition;
}

void Saci::teleport(Vector2f pos) {
    if(!far && teleportClock >= TELEPORTCOOLDOWN) {
        cout << "Saci is teleporting" <<endl;
        teleportClock = 0;
        setPosition(pos);
    }
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Saci::attack(Player *p) {
    if(p){
        p->takeDamage(strength);
    }
}
