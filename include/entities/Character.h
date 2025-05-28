#ifndef CHARACTER_H
#define CHARACTER_H
#include "Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Character : public Entity{

    protected:
        int health;
        Vector2f friction;
        float friction_coef;
        int strength; 
        const float movimentSpeed;
        Vector2f velocity;
        static Vector2f gravity;

    public:
        Character(const float size, float x, float y, const float movSpeed, int life = 5, float coef = 0.5, int s = 1);
        virtual ~Character();
        virtual void execute() = 0;
        virtual void move() = 0;
        virtual void collide();
        void moveCharacter();


};

#endif