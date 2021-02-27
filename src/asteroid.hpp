#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum e_Type { BIG = 30, MEDIUM = 20, SMALL = 13 };

class Asteroid {
private:
  sf::CircleShape m_shape;
  sf::Vector2f m_dir;
  int m_speed;

  void move(float &dt);
  void screenWrapper(sf::RenderWindow *window);
  
public:
  e_Type type;

  Asteroid(e_Type type);
  ~Asteroid();

  sf::FloatRect hitBox();
  sf::Vector2f getPosition();
  void setPosition(float x, float y);
  void update(float &dt);
  void render(sf::RenderWindow *window);
};

#endif
