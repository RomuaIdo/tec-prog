#ifndef GERENCIADOR_GRAFICO_H
#define GERENCIADOR_GRAFICO_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;


class Gerenciador_Grafico {
private:
  RenderWindow* pjanela;
  map<string, Texture*> texturas;
  Font* fonte;

public:
  Gerenciador_Grafico();
  ~Gerenciador_Grafico();


  void setJanela(RenderWindow* janela);
  Texture carregarTextura(const string& caminho);
  
  Font* getFonte();

  void desenhar(Drawable& drawable);
  void limpar();
  void exibir();
};
#endif
