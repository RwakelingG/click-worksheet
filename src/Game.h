
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseButtonPressed(sf::Event event);
  void mouseButtonReleased(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void dragSprite(std::shared_ptr<sf::Sprite> sprite);
  void stampOffsets();
  void moveStamps();
  void toggleMenu();
  void loadTextures();
  void returnPassport();
  void newAnimal();
  

 private:
  sf::RenderWindow& window;

  std::shared_ptr<sf::Sprite> sp_dragged = nullptr;

  sf::Vector2f drag_offset;

  std::unique_ptr<sf::Sprite> up_character;
  std::shared_ptr<sf::Sprite> sp_passport;

  std::vector<std::unique_ptr<sf::Texture>> up_animals;
  std::vector<std::unique_ptr<sf::Texture>> up_passports;
  
  sf::Sprite accept;
  sf::Texture accept_texture;
  sf::Vector2f accept_offset;

  sf::Sprite reject;
  sf::Texture reject_texture;
  sf::Vector2f reject_offset;

  sf::Sprite accept_button;
  sf::Texture accept_button_texture;
  sf::Sprite reject_button;
  sf::Texture reject_button_texture;

  sf::Sprite background;
  sf::Texture background_texture;

  bool passport_accepted = false;
  bool passport_rejected = false;

  bool menu_open = false;

  bool character_visible = true;
  bool passport_visible = true;

  bool should_accept = false;

  int lives;
};

#endif // PLATFORMER_GAME_H
