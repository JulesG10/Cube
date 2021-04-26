#pragma once
#include<SFML/Graphics.hpp>

class Mouse
{
public:
	Mouse();
	~Mouse();
	bool Update(sf::RenderWindow&);
	void Draw(sf::RenderWindow& window);
private:
	sf::Vector2f m_pos = sf::Vector2f(50, 50);
};

