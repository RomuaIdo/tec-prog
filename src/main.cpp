#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
class Bola {
private:
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Color color;
  float radius;
  bool isPlayer;
  unsigned int playerNum;
  static unsigned int NumPlayers;

public:
  Bola(float x, float y, float r, bool player = false)
      : position(x, y), radius(r), isPlayer(player), playerNum(NumPlayers) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);
    color = sf::Color(dist(gen), dist(gen), dist(gen));

    if (!isPlayer) {
      std::uniform_real_distribution<float> vel(-2.0f, 2.0f);
      velocity = sf::Vector2f(vel(gen), vel(gen));
    }
  }

  void setPosition(const sf::Vector2f &pos) { position = pos; }
  sf::Vector2f getPosition() const { return position; }
  void update(const sf::Vector2u &windowSize, float cr) {
    // Atualiza posição considerando o raio
    position += velocity;

    // Colisão com as bordas (corrigido para considerar o raio)
    float windowWidth = windowSize.x;
    float windowHeight = windowSize.y;

    if (position.x < 0) {
      position.x = 0;
      velocity.x *= -cr;
    } else if (position.x + 2 * radius > windowWidth) {
      position.x = windowWidth - 2 * radius;
      velocity.x *= -cr;
    }

    if (position.y < 0) {
      position.y = 0;
      velocity.y *= -cr;
    } else if (position.y + 2 * radius > windowHeight) {
      position.y = windowHeight - 2 * radius;
      velocity.y *= -cr;
    }
  }

  void handleInput() {
    if (isPlayer && playerNum == 1) {
      float speed = 5.0f;
      velocity = sf::Vector2f(0, 0);

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        velocity.y = -speed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        velocity.y = speed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        velocity.x = -speed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity.x = speed;
    } else if (isPlayer && playerNum == 2) {
      float speed = 5.0f;
      velocity = sf::Vector2f(0, 0);

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        velocity.y = -speed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        velocity.y = speed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        velocity.x = -speed;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        velocity.x = speed;
    }
  }

  sf::Vector2f getCenter() const {
    return position + sf::Vector2f(radius, radius);
  }

  float getRadius() const { return radius; }
  sf::Vector2f getVelocity() const { return velocity; }
  void setVelocity(sf::Vector2f newVel) { velocity = newVel; }

  void draw(sf::RenderWindow &window) const {
    sf::CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setPosition(position);
    window.draw(shape);
  }
  void incrementPlayerNum() { playerNum = NumPlayers++; }
  bool IsPlayer() { return isPlayer; }
};

// Corrigir a função resolveCollision
void resolveCollision(Bola &a, Bola &b, float cr) {

  sf::Vector2f normal = b.getCenter() - a.getCenter();
  float distance = std::hypot(normal.x, normal.y);
  float sumRadii = a.getRadius() + b.getRadius();
  // Caso especial: colisão entre dois jogadores

  if (distance == 0 || distance > sumRadii)
    return;

  if (a.IsPlayer() && b.IsPlayer()) {
    if (distance == 0)
      return;           // Impede divisão por zero
    normal /= distance; // Normaliza o vetor

    float penetration = sumRadii - distance;
    sf::Vector2f correction = normal * penetration * 0.5f;

    a.setPosition(a.getPosition() - correction);
    b.setPosition(b.getPosition() + correction);

    // Reflete as velocidades
    float velAlongNormalA =
        a.getVelocity().x * normal.x + a.getVelocity().y * normal.y;
    a.setVelocity(a.getVelocity() - (1 + cr) * velAlongNormalA * normal);

    float velAlongNormalB =
        b.getVelocity().x * normal.x + b.getVelocity().y * normal.y;
    b.setVelocity(b.getVelocity() - (1 + cr) * velAlongNormalB * normal);

    return;
  }

  normal /= distance;
  sf::Vector2f relativeVel = b.getVelocity() - a.getVelocity();
  float velAlongNormal = relativeVel.x * normal.x + relativeVel.y * normal.y;

  if (velAlongNormal > 0)
    return;

  float mass1 = a.getRadius() * a.getRadius();
  float mass2 = b.getRadius() * b.getRadius();

  float j = -(1 + cr) * velAlongNormal;
  j /= (1 / mass1 + 1 / mass2);

  sf::Vector2f impulse = j * normal;

  a.setVelocity(a.getVelocity() - impulse / mass1);
  b.setVelocity(b.getVelocity() + impulse / mass2);

  // Correção posicional (modificado)
  float penetration = sumRadii - distance;
  const float percent = 0.5f;
  sf::Vector2f correction = normal * penetration * percent;

  // Modificar diretamente a posição das bolas
  a.setPosition(a.getPosition() + correction * (mass2 / (mass1 + mass2)));
  b.setPosition(b.getPosition() - correction * (mass1 / (mass1 + mass2)));
}

unsigned int Bola::NumPlayers = 1;

int main() {
  float cr;
  std::cout << "Digite o coeficiente de restituição (0.0-1.0): ";
  std::cin >> cr;

  int tipoRaio;
  std::cout << "Escolha o tipo de raio (1 - Aleatório, 2 - Fixo): ";
  std::cin >> tipoRaio;

  float raioMin = 0, raioMax = 0, raioFixo = 0;
  std::mt19937 gen(std::random_device{}());

  if (tipoRaio == 1) {
    std::cout << "Digite o raio mínimo (0-20): ";
    std::cin >> raioMin;
    std::cout << "Digite o raio máximo (0-20): ";
    std::cin >> raioMax;
  } else {
    std::cout << "Digite o raio fixo (0-20): ";
    std::cin >> raioFixo;
  }

  sf::RenderWindow window(sf::VideoMode({800, 600}), "Bolas Colidíveis CR");
  std::vector<Bola> bolas;
  // std::vector<Bola> players;
  //  Cria jogador 1
  float raioJogador =
      tipoRaio == 1
          ? std::uniform_real_distribution<float>(raioMin, raioMax)(gen)
          : raioFixo;

  bolas.emplace_back(400 - raioJogador, 300 - raioJogador, raioJogador, true);
  // Cria jogador 2
  bolas[0].incrementPlayerNum();
  float raioJogador2 =
      tipoRaio == 1
          ? std::uniform_real_distribution<float>(raioMin, raioMax)(gen)
          : raioFixo;
  bolas.emplace_back(200 - raioJogador2, 500 - raioJogador2, raioJogador2,
                     true);
  // Cria outras bolas
  std::uniform_real_distribution<float> posDist(0.0f, 700.0f);
  for (int i = 0; i < 10; ++i) {
    float raio =
        tipoRaio == 1
            ? std::uniform_real_distribution<float>(raioMin, raioMax)(gen)
            : raioFixo;

    float x = std::clamp(posDist(gen), raio, 800.0f - 2 * raio);
    float y = std::clamp(posDist(gen), raio, 600.0f - 2 * raio);

    bolas.emplace_back(x, y, raio);
  }

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    for (auto &bola : bolas) {
      bola.handleInput();
      bola.update(window.getSize(), cr);
    }

    // Verifica colisões entre bolas
    for (size_t i = 0; i < bolas.size(); ++i) {
      for (size_t j = i + 1; j < bolas.size(); ++j) {
        resolveCollision(bolas[i], bolas[j], cr);
      }
    }

    window.clear();
    for (const auto &bola : bolas) {
      bola.draw(window);
    }
    window.display();
    sf::sleep(sf::milliseconds(16));
  }

  return 0;
}
