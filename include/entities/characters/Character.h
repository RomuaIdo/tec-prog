#ifndef CHARACTER_H
#define CHARACTER_H
#include "../Entity.h"
#include "../obstacles/Cloud.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Character : public Entity {

    protected:
        /* ------ STATUS ------- */
        float aceleration;
        int health;
        bool alive;
        int strength;
        float takeDamageClock;
        float damageBlinkClock ;
        bool isBlinking;

        /* --- COEFFICIENTS ---- */
        Vector2f friction;

        /* ------- FLAGS ------- */
        int faced_right;
        bool in_air;

    public:
        Character();
        Character(float x, float y, float acel, int life = 5, int s = 1);
        virtual ~Character();

        virtual void execute() = 0;
        virtual void move() = 0;

        /* -------- SAVE -------- */
        virtual json toJson() const = 0;
        virtual void fromJson(const json& j) = 0;
        virtual std::string getType() const = 0;

        /* ---- OWN FUNCTIONS ---- */
        void moveCharacter();
        void applyFriction(float dt = 1.f / 60.f);
        virtual void takeDamage(int damage, int direction);
        virtual void updateClocks() = 0;
        void updateDamageBlink();

        /* ----- GETS & SETS ----- */
        int getHealth() const;
        int getStrength() const;
        bool getInAir() const;
        void setInAir(bool inair);
        bool getAlive() const;
};

#endif
