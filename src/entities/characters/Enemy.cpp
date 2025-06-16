#include "../../../include/entities/characters/Enemy.h"
#include "../../../include/entities/characters/Player.h"
#include <SFML/Window.hpp>


Enemy::Enemy()
    : Character(), players_list() {

  if (!texture.loadFromFile("assets/textures/EnemySprite.png")) {
    std::cerr << "Failed to load EnemySprite.png!" << std::endl;
  }
  texture.setSmooth(true);
  sprite.setTexture(texture);
  centerOrigin();
  size.x = sprite.getLocalBounds().width;
  size.y = sprite.getLocalBounds().height;
  sprite.setScale(size.x / sprite.getLocalBounds().width,
                  size.y / sprite.getLocalBounds().height);

  players_list.clear();
}

Enemy::Enemy(float x, float y, const float acel, int life, float coef, int s)
    : Character(x, y, acel, life, coef, s), players_list() {

  if (!texture.loadFromFile("assets/textures/EnemySprite.png")) {
    std::cerr << "Failed to load EnemySprite.png!" << std::endl;
  }
  texture.setSmooth(true);
  sprite.setTexture(texture);
  centerOrigin();
  size.x = sprite.getLocalBounds().width;
  size.y = sprite.getLocalBounds().height;
  sprite.setScale(size.x / sprite.getLocalBounds().width,
                  size.y / sprite.getLocalBounds().height);

  players_list.clear();
}

Enemy::~Enemy() { players_list.clear(); }



/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */



/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Enemy::removePlayer(Player *p){
    list<Player *>::iterator it;
    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it == p){
            players_list.erase(it);
            return;
        }
  }
}

void Enemy::addPlayer(Player *p){
    players_list.push_back(p);
}


