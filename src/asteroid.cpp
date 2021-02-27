#include "asteroid.hpp"
#include <cstdio>

Asteroid::Asteroid(e_Type type) : type(type) {
  m_shape.setRadius(type);
  m_shape.setPosition(300, 450);
  m_speed = 92;
  m_dir.x = rand() % 3 - 1;
  m_dir.y = rand() % 3 - 1;
  if (m_dir.x == 0 && m_dir.y == 0)
    m_dir.x = 1;
}

Asteroid::~Asteroid() {}

void Asteroid::screenWrapper(sf::RenderWindow *window) {
  if (m_shape.getPosition().x > window->getSize().x) {
    m_shape.setPosition({0, m_shape.getPosition().y});
  }
  if (m_shape.getPosition().x < 0) {
    m_shape.setPosition(
        {static_cast<float>(window->getSize().x), m_shape.getPosition().y});
  }
  if (m_shape.getPosition().y > window->getSize().y) {
    m_shape.setPosition({m_shape.getPosition().x, 0});
  }
  if (m_shape.getPosition().y < 0) {
    m_shape.setPosition(
        {m_shape.getPosition().x, static_cast<float>(window->getSize().y)});
  }
}

void Asteroid::move(float &dt) {
  sf::Vector2f velocity = dt * m_speed * m_dir;
  m_shape.move(velocity);
}

sf::FloatRect Asteroid::hitBox() { return m_shape.getGlobalBounds(); }

sf::Vector2f Asteroid::getPosition() { return m_shape.getPosition(); }

void Asteroid::setPosition(float x, float y) { m_shape.setPosition(x, y); }

void Asteroid::update(float &dt) { move(dt); }

void Asteroid::render(sf::RenderWindow *window) {
  screenWrapper(window);
  window->draw(m_shape);
}
