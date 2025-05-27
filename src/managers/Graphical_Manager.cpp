#include "../../include/managers/Graphical_Manager.h"
#include "../../include/entities/Ente.h"


Graphical_Manager *Graphical_Manager::instance = nullptr;

Graphical_Manager *Graphical_Manager::getInstance() {
  if (instance == nullptr) {
    instance = new Graphical_Manager();
  }
  return instance;
}

Graphical_Manager::Graphical_Manager():
  pWindow = nullptr,
  font(NULL)
{
  font = new Font();
  if (!font->loadFromFile("../../assets/fonts/arial.ttf")) {
    std::cerr << "Error when trying to load the font." << std::endl;
  }
}

Graphical_Manager::~Graphical_Manager() {
  map<string, Texture *>::iterator it;
  for (it = textures.begin(); it != textures.end(); it++) {
    delete it->second;
    it->second = nullptr;
  }
  delete font;
}

void Graphical_Manager::setWindow(RenderWindow *window) { pWindow = window; }

Font *Graphical_Manager::getFont() { return font; }

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
