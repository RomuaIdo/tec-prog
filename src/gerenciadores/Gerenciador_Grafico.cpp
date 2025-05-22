#include "../../include/gerenciadores/Gerenciador_Grafico.h"

Gerenciador_Grafico::Gerenciador_Grafico() {
    pjanela = nullptr;
    fonte = new Font();
    if (!fonte->openFromFile("../../assets/fonts/arial.ttf")) {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
    }
}


Gerenciador_Grafico::~Gerenciador_Grafico() {
  map<string, Texture*>::iterator it;
  for(it = texturas.begin(); it != texturas.end(); it++){
    delete it->second;
    it->second = nullptr;
  }
  delete fonte;
}

void Gerenciador_Grafico::setJanela(RenderWindow* janela){
  pjanela = janela;
}

Font* Gerenciador_Grafico::getFonte(){
  return fonte;
}
