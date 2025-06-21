#ifndef ENTE_H
#define ENTE_H
#include <SFML/Graphics.hpp>
#include "../managers/GraphicsManager.h"
#include <cstdlib>
#include <ctime>
#include <random>

using namespace sf;

class Ente {
    protected:
        /* -- GRAPHIC MANAGER -- */
        static GraphicsManager* pGM;

        /* ------ STATUS ------- */
        Sprite sprite;
        Texture texture;
        Vector2f size;
        
    public:
        Ente();
        virtual ~Ente() = default;
        
        virtual void execute() = 0;

        /* ---- OWN FUNCTIONS ---- */
        virtual void centerOrigin();
        void configSprite();
        virtual void draw();
        virtual Drawable& getDrawable();

        /* ----- GETS & SETS ----- */
        FloatRect getGlobalBounds() const;
        void setTexture(Texture t);
        Vector2f getSize() const;
        void setSize(Vector2f Size);
        Sprite& getSprite();
        virtual Vector2f getPosition() const;
        virtual void setPosition(Vector2f pos);
        static void setGraphicsManager(GraphicsManager* pGM); 
};

#endif
