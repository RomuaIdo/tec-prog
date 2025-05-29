#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H
#include <SFML/Graphics.hpp>
#include "CollisionManager.h"
#include <map>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

class Ente;


class GraphicsManager {
    private:
        static GraphicsManager* instance;
        static CollisionManager* pCM;
        RenderWindow* pWindow;
        map<string, Texture*> textures;
        Font* font;
        float dt;
        Clock dt_clock;
        static float clock_time;
        GraphicsManager();
    public:

        ~GraphicsManager();

        GraphicsManager(const GraphicsManager&) = delete;
        GraphicsManager& operator=(const GraphicsManager&) = delete;

        static GraphicsManager* getInstance();

        bool openWindow() const;
        RenderWindow* getWindow() const;
        void setWindow(RenderWindow* window);
        Texture loadTexture(const string& path);

        Font* getFont();

        void setClock();
        void draw(Ente* ente);
        void clean();
        void show();

        void operator++();
        float getdt() const;
        const Clock getClockdt() const;
        float getClockTime() const;
        void resetClock();
};
#endif
