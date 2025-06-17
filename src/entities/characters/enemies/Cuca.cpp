#include "../../../../include/entities/characters/enemies/Cuca.h"
#include "../../../../include/managers/CollisionManager.h"

Cuca::Cuca(float x, float y, const float acel, int life, float coef, int s) :
    Enemy(x, y, acel, life, coef, s), makingPotion(0.f) {

    if (!texture.loadFromFile("assets/textures/Cuca.png")) {
            std::cerr << "Failed to load Cuca.png!" << std::endl;
    }
    sprite.setTexture(texture);
    configSprite();
}

Cuca::~Cuca() {
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Cuca::execute() {
    move();
    draw();
    makePotion();
    throwPotion();
}

void Cuca::move() {

    // Change direction after 2 seconds
    if(clock > 2.f){
        faced_right *= -1;
        clock = 0;
    }else{
        clock += pGM->getdt();
    }
    velocity.x = faced_right*(aceleration);
    
    moveCharacter();
}

void Cuca::collide(Entity* e) {
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

/* ------------------------------------------- */
/*              POTIONS FUNCTIONS              */
/* ------------------------------------------- */

void Cuca::makePotion(){
    // Delay to throw potion
    if (makingPotion >= 1.f) {
        Projectile *potion = new Projectile(position.x + (faced_right*(10.f+size.x)), position.y, Vector2f(faced_right*10.f, -10.f));

        if(potion){
            Texture potionTexture;
            if (potionTexture.loadFromFile("assets/textures/Potion.png")) {
                potion->setTexture(potionTexture);
            } else {
                std::cerr << "Failed to load Potion.png!" << std::endl;
                // Optionally, delete potion or handle error
                delete potion;
                makingPotion = 0.f;
                return;
            }

            addPotion(potion);
            CollisionManager::getInstance()->addProjectile(potion);

        }else cout << "Potion not allocated" <<endl;

        makingPotion = 0.f;
    }
    makingPotion += pGM->getdt();
}

void Cuca::throwPotion() {
    list<Projectile *>::iterator it = potions.begin();
    while (it != potions.end()) {
        Projectile *p = *it;
        if (p && p->getActive()) {
            p->execute();
            ++it;
        } else {
            // Remove from CollisionManager before deleting
            CollisionManager::getInstance()->removeProjectile(p);

            // Delete the projectile
            delete p; 
            it = potions.erase(it);
        }
    }
}

void Cuca::addPotion(Projectile* pot){
    potions.push_back(pot);
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Cuca::attack(Player *p) {
    /* If player has health and after 2 seconds, then he can attack */
    if(p->getHealth() > 0 && pGM->getClockTime() >= 2.f){
        p->takeDamage(strength);
        pGM->resetClock();
    }
}
