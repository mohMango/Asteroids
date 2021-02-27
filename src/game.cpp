#include "game.hpp"

Game::Game() {
  m_acceleration = 0.f;
  m_screenWidth = 600;
  m_screenHeight = 600;
  initWindow();
  createAsteroids();
}

Game::~Game() { delete m_window; }

void Game::renderAsteroids() {
  for (auto &asteroid : m_asteroids) {
    asteroid.render(m_window);
  }
}

void Game::updateAsteroids() {
  for (auto &asteroid : m_asteroids) {
    asteroid.update(m_deltaTime);
  }
}

void Game::createAsteroids() {
  for (int i = 0; i < 5; ++i) {
    Asteroid temp(e_Type::BIG);
    int x = rand() % m_screenWidth;
    int y = rand() % m_screenHeight;
    temp.setPosition(x, y);
    m_asteroids.push_back(temp);
  }
}

void Game::playerMovement() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    m_acceleration += .4f;
    if (m_acceleration > 299.9f) {
      m_acceleration = 300.f;
    }
  } else {
    if (std::abs(m_acceleration) <= 0.5f) {
      m_acceleration = 0.f;
    } else {
      m_acceleration -= .19f;
    }
  }
  m_player.move(m_deltaTime, m_acceleration);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    m_player.rotation(m_deltaTime, 90);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    m_player.rotation(m_deltaTime, -90);
  }
}

void Game::screenWrapper() {
  if (m_player.getPosition().x > m_window->getSize().x) {
    m_player.setPosition({0, m_player.getPosition().y});
  }
  if (m_player.getPosition().x < 0) {
    m_player.setPosition(
        {static_cast<float>(m_window->getSize().x), m_player.getPosition().y});
  }
  if (m_player.getPosition().y > m_window->getSize().y) {
    m_player.setPosition({m_player.getPosition().x, 0});
  }
  if (m_player.getPosition().y < 0) {
    m_player.setPosition(
        {m_player.getPosition().x, static_cast<float>(m_window->getSize().y)});
  }
}

void Game::initWindow() {
  m_window = new sf::RenderWindow(sf::VideoMode(m_screenWidth, m_screenHeight),
                                  "Game");
}

void Game::updateDt() { m_deltaTime = m_dtClock.restart().asSeconds(); }

void Game::updateEvents() {
  while (m_window->pollEvent(m_event)) {
    if (m_event.type == sf::Event::Closed) {
      m_window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      m_window->close();
    }
  }
}

void Game::update() {
  updateEvents();
  updateDt();
  screenWrapper();
  m_player.update(m_deltaTime);
  updateAsteroids();

  m_player.collision(&m_asteroids);
  playerMovement();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    m_player.shot();
  }
}

void Game::render() {
  m_window->clear(sf::Color::Blue);
  renderAsteroids();
  m_player.render(m_window);
  m_window->display();
}

void Game::run() {
  while (m_window->isOpen()) {
    update();
    render();
  }
}
