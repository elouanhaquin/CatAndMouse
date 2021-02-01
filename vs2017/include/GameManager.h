#pragma once
#include <Player.h>
#include <enemy.h>
#include <ctime>
#include <sstream>
#include <iomanip>

class GameManager
{
private:
	sf::RenderWindow* window;
	sf::Font* font;
	sf::Text* score;
	Enemy* enemy;
	Player* player;
	Vector2D<int> mousePos;
	int fps;

public:
	GameManager();
	~GameManager();

	void start();
	void loop();
	void end();

	void renderFrame();
	void moveEntities();

};

