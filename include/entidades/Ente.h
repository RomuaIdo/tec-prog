#ifndef ENTE_H
#define ENTE_H
#include <SFML/Graphics.hpp>
using namespace sf;


class Ente {
protected:
  //static Gerenciador_Grafico* pGG;
  //Sprite sprite;
  //Texture textura;

public:
  Ente();
  ~Ente();
  virtual void desenhar() = 0;
};

#endif
