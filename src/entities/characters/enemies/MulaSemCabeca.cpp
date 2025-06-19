#include "../../../../include/entities/characters/enemies/MulaSemCabeca.h"

MulaSemCabeca::MulaSemCabeca(float x, float y, const float acel, int life, int s) :
    Enemy(x, y, acel, life, s), chargeClock(0.f) {

    if (!texture.loadFromFile("assets/textures/MulaSemCabeca.png")) {
        std::cerr << "Failed to load MulaSemCabeca.png!" << std::endl;
    }

    sprite.setTexture(texture);
    configSprite();
}

MulaSemCabeca::~MulaSemCabeca() {
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void MulaSemCabeca::execute() {
    move();
    draw();
    verifyDeadPlayers();
    updateClocks();
}

void MulaSemCabeca::move() {

    float closer = 100000.f;
    float right = 1.f;


    // Get the closest player direction 
    for(list<Player*>::iterator it = players_list.begin(); it != players_list.end(); it++){
        if(*it){
            // Get direction to player (feet to feet)
            Vector2f direction = ( ((*it)->getPosition() + Vector2f( 0.f, (*it)->getSize().y)) - (position + Vector2f( 0.f, size.y)) );
            float module = sqrt(direction.x*direction.x + direction.y*direction.y);
            if(module < closer){
                // See if closer is in right or left
                right = direction.x;

                closer = module;
            }
        }
    }

    // if it is 700 pixels far, the enemy dont move
    if(abs(right) < 700.f){
        far = false;
    }else{
        far = true;
    }
    
    // after 3 seconds, the enemy change its direction
    if(clock >= MULACHANGEDIRECTION){
        faced_right *= -1;
        clock = 0.f;
    }

    if(!far){
        charge();
    }else{
        velocity = Vector2f(faced_right * aceleration, 0.f);
    }
    
    applyGravity();
    moveCharacter();
}

void MulaSemCabeca::collide(Entity* e) {
    Vector2f ePos = e->getPosition();
    Vector2f eSize = e->getSize();

    float dx = (position.x - ePos.x);
    float dy = (position.y - ePos.y);



    Vector2f intersection = Vector2f( abs(dx) - (size.x + eSize.x), 
                                      abs(dy) - (size.y + eSize.y) );

    if (intersection.x < 0.0f && intersection.y < 0.0f) {

        /* If intersection in x is less then intersection in y */
        /*  means that they are side by side                   */

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
        /* If intersection in y is less then intersection in x*/
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

void MulaSemCabeca::updateClocks(){
    float dt = pGM->getdt();
    
    clock += dt;
    chargeClock += dt;
}

void MulaSemCabeca::charge() {
    if(chargeClock >= CHARGECOOLDOWN) {
        // stay active for 2 seconds (showing that will charge)

        // texture = chargeTexture;
        // sprite.setTexture(texture);
        // configSprite();
        if(chargeClock >= CHARGEPREPARATIONCOOLDOWN){
            setVelocity(Vector2f(faced_right * 100.f, 0.f));
            chargeClock = 0.f;

            // texture = runTexture;
            // sprite.setTexture(texture);
            // configSprite();
        }
    }
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void MulaSemCabeca::attack(Player *p) {
    if(p) {
        p->takeDamage(strength);
    }
}
