#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "characters/Character.h"
#include "characters/Enemy.h"
#include "characters/Player.h"

using namespace sf;

class Projectile : public Entity{

    private:
        /* ------ STATUS ------- */
        Entity* owner; // Pointer to the owner of the projectile

        /* ------ FLAGS ------- */
        bool active;
    
    public:
        /* --- CONSTRUCTORS --- */
        Projectile();
        Projectile(float x, float y, Vector2f vel, Entity* creator);
        ~Projectile();

        /* ------ STATUS ------- */
        Texture potion;
        Texture Rock;

        /* -------- SAVE -------- */
        virtual json toJson() const;
        virtual void fromJson(const json& j);
        std::string getType() const;

        /* --- OWN FUNCTIONS --- */
        void collide(Entity* other);
        void execute();
        void move();
        bool getActive();
        void setActive(bool Active = false);
        void setOwner(Entity* owner);
};  

#endif
