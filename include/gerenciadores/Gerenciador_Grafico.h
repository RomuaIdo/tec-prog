#ifndef GERENCIADOR_GRAFICO_H
#define GERENCIADOR_GRAFICO_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

class Ente;


class Gerenciador_Grafico {
private:
  static Gerenciador_Grafico* instancia;
  RenderWindow* pjanela;
  map<string, Texture*> texturas;
  Font* fonte;
  Gerenciador_Grafico();
public:

  ~Gerenciador_Grafico();

  Gerenciador_Grafico(const Gerenciador_Grafico&) = delete;
  Gerenciador_Grafico& operator=(const Gerenciador_Grafico&) = delete;

  static Gerenciador_Grafico* getInstancia();

  bool janelaAberta() const;
  RenderWindow* getJanela() const;
  void setJanela(RenderWindow* janela);
  Texture carregarTextura(const string& caminho);
  
  Font* getFonte();

  void desenhar(Ente* ente);
  void limpar();
  void exibir();
};
#endif
