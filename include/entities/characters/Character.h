#ifndef CHARACTER_H
#define CHARACTER_H
#include "entities/Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Character : public Entity {

    protected:
        int health;
        float friction_coef;
        Vector2f friction;

        int strength;
        const float movimentSpeed;
        Vector2f velocity;
        static Vector2f gravity;

    public:
        Character(float x, float y, const float movSpeed,
        int life = 5, float coef = 0.5, int s = 1);
        virtual ~Character();
        virtual void execute() = 0;
        virtual void move() = 0;
        virtual void collide();
        void moveCharacter();
        Vector2f getVelocity() const;
        void setVelocity(Vector2f vel);
};

#endif
