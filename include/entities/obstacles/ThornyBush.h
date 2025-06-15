#ifndef THORNY_BUSH_H
#define THORNY_BUSH_H
#include "Obstacle.h"
#include "../characters/Player.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class ThornyBush : public Obstacle{

    private:
        /* ------ STATUS ------- */
        int spikes; // Number of spikes in the bush
        float time_between_attacks;
        float own_clock;
        Texture texture_hide;
        Texture texture_spikes;

    public:
        ThornyBush(float x, float y, bool harm = true);
        ~ThornyBush();

        /* ---- OWN FUNCTIONS ---- */
        void obstacleAction(Entity* e);
        void execute();
        void collide(Entity* e);
        void dealDamage(Player* p);
        void setState();
        void update();

        /* ----- GETS & SETS ----- */
        void setSpikes(int s = 2);
        int getSpikes() const;


};

#endif
