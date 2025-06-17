#ifndef CHARACTER_H
#define CHARACTER_H
#include "../Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Character : public Entity {

    protected:
        /* ------ STATUS ------- */
        int health;
        const int strength;
        const float aceleration;
        Vector2f speed;
        float clock;
        
        /* --- COEFFICIENTS ---- */
        Vector2f friction;
        float friction_coef;
        
        /* ------- FLAGS ------- */
        int faced_right;
        bool in_air;

    public:
        Character();
        Character(float x, float y, const float acel, int life = 5, float coef = 0.5, int s = 1);
        virtual ~Character();

        virtual void execute() = 0;
        virtual void move() = 0;

        /* ---- OWN FUNCTIONS ---- */
        void moveCharacter();
        void takeDamage(int damage);
        
        /* ----- GETS & SETS ----- */
        Vector2f getSpeed() const;
        void setSpeed(Vector2f vel);
        int getStrength() const;
        bool getInAir() const;
        void setInAir(bool inair);
};

#endif
