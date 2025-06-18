#ifndef CHARACTER_H
#define CHARACTER_H
#include "../Entity.h"
#include "../obstacles/Plataform.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Character : public Entity {

    protected:
        /* ------ STATUS ------- */
        const float aceleration;
        int health;
        const int strength;
        float takeDamageClock;

        /* --- COEFFICIENTS ---- */
        Vector2f friction;
        
        /* ------- FLAGS ------- */
        int faced_right;
        bool in_air;

    public:
        Character();
        Character(float x, float y, const float acel, int life = 5, int s = 1);
        virtual ~Character();

        virtual void execute() = 0;
        virtual void move() = 0;
        
        /* ---- OWN FUNCTIONS ---- */
        void moveCharacter();
        void applyFriction(float dt = 1.f/60.f);
        virtual void takeDamage(int damage);
        virtual void updateClocks() = 0;
        
        /* ----- GETS & SETS ----- */
        int getStrength() const;
        bool getInAir() const;
        void setInAir(bool inair);
};

#endif
