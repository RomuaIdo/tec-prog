#ifndef ENTE_H
#define ENTE_H
#include <SFML/Graphics.hpp>
#include "../gerenciadores/Gerenciador_Grafico.h"
using namespace sf;


class Ente {
protected:
  static Gerenciador_Grafico* pGG;
  Sprite sprite;
  Texture textura;

public:
  Ente();
  virtual ~Ente();
  virtual void desenhar() = 0;
};

#endif
