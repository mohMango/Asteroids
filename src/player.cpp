#include "player.hpp"

Player::Player() {
  calcDir();

  m_shotTimer = 0.f;

  m_texture.loadFromFile("res/player.png");
  m_sprite.setTexture(m_texture);
  m_sprite.setOrigin(
      sf::Vector2f(m_texture.getSize().x / 2, m_texture.getSize().y / 2));
  m_sprite.setPosition(300, 300);
}

Player::~Player() {}

void Player::collision(std::vector<Asteroid> *asteroids) {
  for (int i = 0; i < asteroids->size(); ++i) {
    if (m_sprite.getGlobalBounds().intersects(asteroids->at(i).hitBox())) {
      printf("die\n");
    }
    for (int j = 0; j  < m_bullets.size(); ++j) {
      if (m_bullets.at(j).hitBox().intersects(asteroids->at(i).hitBox())) {
        if (asteroids->at(i).type != e_Type::SMALL) {
          sf::Vector2f tempPos = asteroids->at(i).getPosition();
          if (asteroids->at(i).type == e_Type::BIG) {
            Asteroid temp(e_Type::MEDIUM);
            temp.setPosition(tempPos.x, tempPos.y);
            asteroids->push_back(temp);
          } else {
            Asteroid temp(e_Type::SMALL);
            temp.setPosition(tempPos.x, tempPos.y);
            asteroids->push_back(temp);
          }
        }
        m_bullets.erase(m_bullets.begin() + j);
        asteroids->erase(asteroids->begin() + i);
      }
    }
  }
}

void Player::calcDir() {
  m_dir.x = std::sin(toRadians(m_sprite.getRotation()));
  m_dir.y = -std::cos(toRadians(m_sprite.getRotation()));
}

void Player::setPosition(sf::Vector2f pos) { m_sprite.setPosition(pos); }

sf::Vector2f Player::getPosition() { return m_sprite.getPosition(); }

float Player::toRadians(float angle) {
  float pi = 3.1415926536;
  return (pi / 180) * angle;
}

void Player::rotation(const float &dt, float rotationSpeed) {
  m_sprite.rotate(rotationSpeed * dt);
}

void Player::move(const float &dt, float acceleration) {
  calcDir();
  sf::Vector2f speed = m_dir * acceleration * dt;
  m_sprite.move(speed);
}

void Player::shot() {
  if (m_shotTimer >= .3f) {
    Bullet bullet(m_dir, m_sprite.getPosition());
    m_bullets.push_back(bullet);
    m_shotTimer = 0.f;
  }
}
void Player::update(float &dt) {
  m_shotTimer += dt;
  for (auto &bullet : m_bullets) {
    bullet.update(dt);
    if (bullet.eraseTimer > 0.6f) {
      m_bullets.erase(m_bullets.begin() + 1);
    }
  }
}

void Player::render(sf::RenderWindow *window) {
  window->draw(m_sprite);
  for (auto &bullet : m_bullets) {
    bullet.render(window);
  }
}
