#ifndef PLATAFORM_H
#define PLATAFORM_H
#include "Obstacle.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Plataform : public Obstacle{

    private:
        /* ------ STATUS ------- */
        float width;
        float height;

    public:
        Plataform();
        Plataform(float x, float y, bool harm = false);
        ~Plataform();
        /* ---- OWN FUNCTIONS ---- */
        void collide(Entity* other) override;
        void obstacleAction(Player* player) override;
        void obstacleAction(Enemy* enemy) override;
        void execute() override;

        /* ----- GETS & SETS ----- */
        void setWidth(float w);
        float getWidth() const;
        void setHeight(float h);
        float getHeight() const;

};


#endif
