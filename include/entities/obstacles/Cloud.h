#ifndef PLATAFORM_H
#define PLATAFORM_H
#include "Obstacle.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Cloud : public Obstacle{

    private:
        /* ------ STATUS ------- */
        bool isActive;
        int plataformType; // 0 for cloud1, 1 for cloud2
        float regenClock;

        Vector2f originalPosition;

        
        void setState();
        void move();

    public:
        Cloud();
        Cloud(float x, float y, bool harm = false, int n = 0);
        ~Cloud();
        /* ------ TEXTURES ------ */
        Texture cloud1;
        Texture cloud1active;

        Texture cloud2;
        Texture cloud2active;

        /* ---- OWN FUNCTIONS ---- */
        void collide(Entity* other) override;
        void obstacleAction(Entity* e) override;
        void execute() override;

        /* -------- SAVE -------- */
        json toJson() const override;
        void fromJson(const json& j) override;
        std::string getType() const override;

        /* ----- GETS & SETS ----- */
        bool getIsActive() const;
        void setIsActive(bool active);
};


#endif
