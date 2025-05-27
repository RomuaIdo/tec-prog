#include "../gerenciadores/Gerenciador_Grafico.h"
#include "../entidades/Jogador.h"


class Jogo {
private:
    Gerenciador_Grafico* gerenciadorGrafico;
    Jogador* jogador1;
    Jogador* jogador2;

public:
  Jogo();
  ~Jogo();
  void executar();
};
