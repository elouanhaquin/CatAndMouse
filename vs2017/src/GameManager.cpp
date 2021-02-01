#include "GameManager.h"



GameManager::GameManager()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Cat And Mouse");
	player = new Player();
	enemy = new Enemy();
	mousePos = sf::Mouse::getPosition(*window);
	font = new sf::Font();
	score = new sf::Text();

	fps = 60;
}


GameManager::~GameManager()
{
	delete window;
	delete player;
	delete enemy;
}

void GameManager::start()
{
	window->setFramerateLimit(fps);
	window->setMouseCursorVisible(false);
	
	if (!font->loadFromFile("SCOREBOARD.ttf"))
	{
		std::cout << "ERROR WITH FONT INITIALIZATION" << std::endl;
	}
	score->setFont(*font);
	score->setCharacterSize(50);
	score->setFillColor(sf::Color::White);
	score->setPosition(475,10);
}

void GameManager::loop()
{

	sf::Clock clock; 
	
	
	while (window->isOpen())
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << enemy->getDistanceTraveled();

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed || enemy->mouseIsCatched() || enemy->getRectangleShape().getGlobalBounds().intersects(player->getRectangleShape().getGlobalBounds()))
				window->close();	
		}
		if(clock.getElapsedTime().asSeconds() > 3)
		{
			enemy->increaseDifficulty();
			clock.restart();
		}
		
		score->setString(ss.str() + " METERS");
		moveEntities();
		renderFrame();
	}
}

void GameManager::end()
{
}

void GameManager::renderFrame()
{
	window->clear();
	window->draw(player->getRectangleShape());
	window->draw(enemy->getRectangleShape());
	window->draw(*score);
	window->display();
}

void GameManager::moveEntities()
{
	mousePos = sf::Mouse::getPosition(*window);
	player->move(mousePos);
	enemy->move(sf::Vector2f(mousePos.X() - 25, mousePos.Y() - 25));
}
