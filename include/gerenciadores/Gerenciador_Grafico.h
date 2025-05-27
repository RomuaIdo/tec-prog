#ifndef GRAPHICAL_MANAGER_H
#define GRAPHICAL_MANAGER_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

class Ente;


class Graphical_Manager {
private:
  static Graphical_Manager* instance
  RenderWindow* pWindow;
  map<string, Texture*> textures;
  Font* font;
  Graphical_Manager();
public:

  ~Graphical_Manager();

  Graphical_Manager(const Graphical_Manager&) = delete;
  Graphical_Manager& operator=(const Graphical_Manager&) = delete;

  static Graphical_Manager* getInstance();

  bool openWindow() const;
  RenderWindow* getWindow() const;
  void setWindow(RenderWindow* window);
  Texture loadTexture(const string& path);
  
  Font* getFonte();

  void draw(Ente* ente);
  void clean();
  void show();
};
#endif
