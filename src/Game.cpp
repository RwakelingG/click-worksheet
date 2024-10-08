
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
	delete [] animals;
	delete [] passports;
	delete character;
	delete passport;
}

bool Game::init()
{
	character = new sf::Sprite;
	passport = new sf::Sprite;

	loadTextures();

	background.setTexture(background_texture);

	character->setTexture(animals[0]);
	character->setScale(1.8,1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	accept.setTexture(accept_texture);
	reject.setTexture(reject_texture);

	accept_button.setTexture(accept_button_texture);
	reject_button.setTexture(reject_button_texture);

	passport->setTexture(passports[0]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);

	stampOffsets();

	lives = 5;

	newAnimal();

	return true;
}

void Game::update(float dt)
{
	dragSprite(dragged);
	
	
	moveStamps();

	
}

void Game::render()
{
	window.draw(background);
	

	window.draw(*character);

	window.draw(*passport);

	if (passport_accepted)
	{
		window.draw(accept);
	}
	if (passport_rejected)
	{
		window.draw(reject);
	}



	if (menu_open)
	{
		window.draw(accept_button);
		window.draw(reject_button);
	}
}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::mouseButtonPressed(sf::Event event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);


		if (!menu_open)
		{
			sf::Vector2f passport_positionf = passport->getPosition();
			if (passport->getGlobalBounds().contains(clickf))
			{
				dragged = passport;
				drag_offset = clickf - passport_positionf;
			}
		}
		else
		{
			if (accept_button.getGlobalBounds().contains(clickf))
			{
				passport_accepted = true;
				passport_rejected = false;
				menu_open = false;
				return;
			}
			else if (reject_button.getGlobalBounds().contains(clickf))
			{
				passport_accepted = false;
				passport_rejected = true;
				menu_open = false;
				return;
			}
		}
		
	}
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		toggleMenu();
	}
}

void Game::mouseButtonReleased(sf::Event event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (dragged != nullptr)
		{
			sf::Vector2f passport_position = dragged->getPosition();

			if (passport_position.x < window.getSize().x / 5
				&& passport_position.y < window.getSize().y / 5)
			{
				returnPassport();
			}

			dragged = nullptr;
		}
	}
	if (event.mouseButton.button == sf::Mouse::Right)
	{
		
	}
}

void Game::keyPressed(sf::Event event)
{

}

void Game::keyReleased(sf::Event event)
{

}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition(drag_position.x, drag_position.y);
	}	
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->setTexture(passports[passport_index]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);

}

void Game::stampOffsets()
{
	float accept_x = passport->getGlobalBounds().width / 2 - accept.getGlobalBounds().width / 2;
	float accept_y = passport->getGlobalBounds().height / 4 - accept.getGlobalBounds().height / 2;
	accept_offset.x = accept_x;
	accept_offset.y = accept_y;

	float reject_x = passport->getGlobalBounds().width / 2 - reject.getGlobalBounds().width / 2;
	float reject_y = passport->getGlobalBounds().height / 4 - reject.getGlobalBounds().height / 2;
	reject_offset.x = reject_x;
	reject_offset.y = reject_y;
}

void Game::moveStamps()
{
	sf::Vector2f passport_position = passport->getPosition();
	
	accept.setPosition(passport_position + accept_offset);
	reject.setPosition(passport_position + reject_offset);
}

void Game::toggleMenu()
{
	if (!menu_open)
	{
		menu_open = true;

		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		float reject_y = reject_button.getGlobalBounds().height + 5;

		accept_button.setPosition(mouse_positionf.x + 5, mouse_positionf.y);
		reject_button.setPosition(mouse_positionf.x + 5, mouse_positionf.y + reject_y);
	}
	else
	{
		menu_open = false;
	}
}

void Game::returnPassport()
{
	if (passport_accepted || passport_rejected)
	{
		if ((should_accept && passport_rejected) || (!should_accept && passport_accepted))
		{
			lives -= 1;
			std::cout << "Wrong!\n";
		}
		else
		{
			std::cout << "Right!\n";
		}

		newAnimal();
	}
}

void Game::loadTextures()
{
	if (!background_texture.loadFromFile("../Data/WhackaMole Worksheet/background.png"))
	{
		std::cout << "Background texture did not load\n";
	}

	if (!animals[0].loadFromFile("../Data/Images/Critter Crossing Customs/penguin.png"))
	{
		std::cout << "Penguin texture did not load\n";
	}

	if (!animals[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant.png"))
	{
		std::cout << "Elephant texture did not load\n";
	}

	if (!animals[2].loadFromFile("../Data/Images/Critter Crossing Customs/moose.png"))
	{
		std::cout << "Elephant texture did not load\n";
	}

	if (!passports[0].loadFromFile("../Data/Images/Critter Crossing Customs/penguin passport.png"))
	{
		std::cout << "Penguin passport texture did not load\n";
	}

	if (!passports[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant passport.png"))
	{
		std::cout << "Elephant passport texture did not load\n";
	}

	if (!passports[2].loadFromFile("../Data/Images/Critter Crossing Customs/moose passport.png"))
	{
		std::cout << "Moose passport texture did not load\n";
	}

	if (!accept_texture.loadFromFile("../Data/Images/Critter Crossing Customs/accept.png"))
	{
		std::cout << "Accept texture did not load\n";
	}

	if (!reject_texture.loadFromFile("../Data/Images/Critter Crossing Customs/reject.png"))
	{
		std::cout << "Reject texture did not load\n";
	}

	if (!accept_button_texture.loadFromFile("../Data/Images/Critter Crossing Customs/accept button.png"))
	{
		std::cout << "Accept texture did not load\n";
	}

	if (!reject_button_texture.loadFromFile("../Data/Images/Critter Crossing Customs/reject button.png"))
	{
		std::cout << "Reject texture did not load\n";
	}
}