#ifndef THORNY_BUSH_H
#define THORNY_BUSH_H
#include "Obstacle.h"
#include "../characters/Character.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class ThornyBush : public Obstacle{

    private:
        /* ------ STATUS ------- */
        int spikes; // Number of spikes in the bush

    public:
        ThornyBush(float x, float y, bool harm = true);
        ~ThornyBush();

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
