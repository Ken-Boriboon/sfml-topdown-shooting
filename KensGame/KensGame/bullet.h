#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bullet
{
private:
	sf::Sprite shape;
	sf::Texture texture;

	sf::Vector2f direction;
	float Speed;

public:
	Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float speed);
	virtual ~Bullet();

	//accessors
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getDir() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif // !BULLET_H
