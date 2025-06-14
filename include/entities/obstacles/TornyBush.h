#ifndef TORNY_BUSH_H
#define TORNY_BUSH_H
#include "Obstacle.h"
#include "../characters/Character.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class TornyBush : public Obstacle{

    private:
        /* ------ STATUS ------- */
        int spikes; // Number of spikes in the bush

    public:
        TornyBush(float x, float y, bool harm = true);
        ~TornyBush();

        /* ---- OWN FUNCTIONS ---- */
        void obstacleAction(Entity* e);
        void execute();
        void collide(Entity* e);
        void dealDamage(Character* character);

        /* ----- GETS & SETS ----- */
        void setSpikes(int s);
        int getSpikes() const;


};

#endif
