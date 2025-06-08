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
        Vector2f velocity;

        /* ------- FLAGS ------- */
        int faced_right;
        bool in_air;

        /* --- COEFFICIENTS ---- */
        Vector2f friction;
        static Vector2f gravity;
        float friction_coef;
        float clock;


    public:

        Character(float x, float y, const float acel,
        int life = 5, float coef = 0.5, int s = 1);
        virtual ~Character();

        virtual void execute() = 0;
        virtual void move() = 0;

        /* ---- OWN FUNCTIONS ---- */
        void moveCharacter();
        void setInAir(bool inair);
        bool isInAir() const;        
        /* ----- GETS & SETS ----- */
        Vector2f getVelocity() const;
        void setVelocity(Vector2f vel);
        
        int getStrength() const;
        
};

#endif
