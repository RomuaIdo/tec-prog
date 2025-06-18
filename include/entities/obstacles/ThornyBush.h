#ifndef THORNY_BUSH_H
#define THORNY_BUSH_H
#include "../characters/Player.h"
#include "../characters/Enemy.h"
#include "Obstacle.h"

class ThornyBush : public Obstacle {

    private:
        /* ------ STATUS ------- */
        float regenClock;
        bool active; 

        /* ------ TEXTURES ----- */
        Texture texture_hide;
        Texture texture_spikes;

    public:
        ThornyBush(float x, float y, bool harm = true);
        ~ThornyBush();

        /* ---- OWN FUNCTIONS ---- */
        void obstacleAction(Entity *e);
        void execute();
        void collide(Entity *e);
        void dealDamage(Player *p);
        void setState();
        void update();

};


#endif
