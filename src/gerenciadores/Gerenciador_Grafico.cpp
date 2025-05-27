#include "../../include/gerenciadores/Gerenciador_Grafico.h"
#include "../../include/entidades/Ente.h"


Gerenciador_Grafico *Gerenciador_Grafico::instancia = nullptr;

Gerenciador_Grafico *Gerenciador_Grafico::getInstancia() {
  if (instancia == nullptr) {
    instancia = new Gerenciador_Grafico();
  }
  return instancia;
}

Gerenciador_Grafico::Gerenciador_Grafico() {
  pjanela = nullptr;
  fonte = new Font();
  if (!fonte->loadFromFile("../../assets/fonts/arial.ttf")) {
    std::cerr << "Erro ao carregar a fonte." << std::endl;
  }
}

Gerenciador_Grafico::~Gerenciador_Grafico() {
  map<string, Texture *>::iterator it;
  for (it = texturas.begin(); it != texturas.end(); it++) {
    delete it->second;
    it->second = nullptr;
  }
  delete fonte;
}

void Gerenciador_Grafico::setJanela(RenderWindow *janela) { pjanela = janela; }

Font *Gerenciador_Grafico::getFonte() { return fonte; }

void Gerenciador_Grafico::desenhar(Ente* ente) {
  if (pjanela != nullptr) {
    pjanela->draw(ente->getDrawable());
  } else{
    std::cerr << "Janela não inicializada." << std::endl;
  } 
}

void Gerenciador_Grafico::limpar() {
  if (pjanela != nullptr) {
    pjanela->clear();
  } else {
    std::cerr << "Janela não inicializada." << std::endl;
  }
}

void Gerenciador_Grafico::exibir() {
  if (pjanela != nullptr) {
    pjanela->display();
  } else {
    std::cerr << "Janela não inicializada." << std::endl;
  }
}


bool Gerenciador_Grafico::janelaAberta() const {
  return pjanela != nullptr && pjanela->isOpen();
}


RenderWindow *Gerenciador_Grafico::getJanela() const {
  return pjanela;
}
