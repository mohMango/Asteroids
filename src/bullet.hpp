#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Bullet {
private:
  sf::CircleShape m_shape;
  sf::Vector2f m_startPos;
  float m_speed;
  sf::Vector2f m_dir;

  void screenWrapper(sf::RenderWindow *window);

public:
  float eraseTimer;

  Bullet(sf::Vector2f dir, sf::Vector2f startPos);
  ~Bullet();

  sf::FloatRect hitBox();
  void update(float &dt);
  void render(sf::RenderWindow *window);
};

#endif
