#ifndef SACI_H
#define SACI_H
#include <list>
#include "../Enemy.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <math.h>
using namespace sf;
using namespace std;

class Saci : public Enemy {

    protected:
        /* ---- TELEPORT ---- */
        bool isTeleporting;
        float teleportTime;
        float lastPositionTime;
        Vector2f lastPosition;

    public:

        Saci(float x, float y, const float acel = 10.f, int life = 5, float coef = 0.5, int s = 1);
        virtual ~Saci();

        /* ---- OWN FUNCTIONS ---- */
        void execute();
        void move();
        void collide(Entity* e);
        void teleport(Vector2f pos);
        Vector2f getPlayerLastPosition();

        /* ------- PLAYER -------- */

        void attack(Player *p);
};

#endif
