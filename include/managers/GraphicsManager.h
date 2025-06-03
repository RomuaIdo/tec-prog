#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

class Ente;

class GraphicsManager {

    private:
        /* ----- VARIABLES ----- */
        static GraphicsManager* instance;
        RenderWindow* pWindow;
        map<string, Texture*> textures;

        /* ------ STATUS ------- */
        Font* font;
        float dt;
        Clock dt_clock;
        static float clock_time;
        
        GraphicsManager();
    public:

        ~GraphicsManager();

        GraphicsManager(const GraphicsManager&) = delete;
        GraphicsManager& operator=(const GraphicsManager&) = delete;

        static GraphicsManager  *getInstance();

        /* ---- OWN FUNCTIONS ---- */
        bool openWindow() const;
        Texture loadTexture(const string& path);
        void draw(Ente* ente);
        void draw(Text* text);
        void clean();
        void show();
        void operator++();
        
        /* ----- GETS & SETS ----- */
        RenderWindow* getWindow() const;
        void setWindow(RenderWindow* window);
        Font* getFont();
        void setClock();
        float getdt() const;
        const Clock getClockdt() const;
        float getClockTime() const;
        void resetClock();
        
};
#endif
