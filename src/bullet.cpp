#include "bullet.hpp"

Bullet::Bullet(sf::Vector2f dir, sf::Vector2f startPos)
    : m_dir(dir), m_startPos(startPos) {
  eraseTimer = 0.f;
  m_shape.setPosition(m_startPos);
  m_speed = 820.f;
  m_shape.setRadius(3.f);
  m_shape.setFillColor(sf::Color::Magenta);
}

Bullet::~Bullet() {}

sf::FloatRect Bullet::hitBox() {
  return m_shape.getGlobalBounds();
}

void Bullet::screenWrapper(sf::RenderWindow *window) {
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

void Bullet::update(float &dt) {
  eraseTimer += dt;
  m_shape.move(m_dir * dt * m_speed);
}

void Bullet::render(sf::RenderWindow *window) {
  screenWrapper(window);
  window->draw(m_shape);
}
