#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "asteroid.hpp"
#include "player.hpp"
#include <vector>
#include <cmath>

class Game {
private:
  sf::RenderWindow *m_window;
  sf::Event m_event;

  sf::Clock m_dtClock;
  float m_deltaTime;

  sf::Texture m_texture;
  Player m_player;
  float m_acceleration;
  int m_screenWidth;
  int m_screenHeight;

  std::vector<Asteroid>  m_asteroids;

  void renderAsteroids();
  void updateAsteroids();
  void createAsteroids();
  void playerMovement();
  void screenWrapper();
  void initWindow();
  void updateDt();
  void updateEvents();

public:
  Game();
  ~Game();

  void update();
  void render();
  void run();
};

#endif
