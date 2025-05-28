#ifndef ENTE_H
#define ENTE_H
#include <SFML/Graphics.hpp>
#include "../managers/GraphicsManager.h"
using namespace sf;


class Ente {
    protected:
        static GraphicsManager* pGM;
        Sprite sprite;
        Texture texture;

    public:
        Ente();
        virtual ~Ente();
        virtual void draw() = 0;
        virtual Drawable& getDrawable() = 0;
        virtual void execute() = 0;
};

#endif
