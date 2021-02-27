#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <vector>

#include "SFML/Graphics.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"

class Player {
private:
  sf::Texture m_texture;
  sf::Sprite m_sprite;

  sf::Vector2f m_dir;

  std::vector<Bullet> m_bullets;
  float m_shotTimer;

public:
  Player();
  ~Player();

  void collision(std::vector<Asteroid> *asteroids);
  void calcDir();
  sf::Vector2f getPosition();
  void setPosition(sf::Vector2f pos);
  float toRadians(float angle);
  void rotation(const float &dt, float rotationSpeed);
  void move(const float &dt, float acceleration);
  void shot();

  void update(float &dt);
  void render(sf::RenderWindow *window);
};

#endif
