#ifndef ENTE_H
#define ENTE_H
#include <SFML/Graphics.hpp>
#include "../managers/GraphicsManager.h"
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
        virtual ~Ente();
        
        virtual void execute() = 0;

        /* ---- OWN FUNCTIONS ---- */
        virtual void draw();
        virtual Drawable& getDrawable();

        /* ----- GETS & SETS ----- */
        Vector2f getSize() const;
        virtual Vector2f getPosition() const;
        virtual void setPosition(Vector2f pos);
        static void setGraphicsManager(GraphicsManager* pGM); 
};

#endif
