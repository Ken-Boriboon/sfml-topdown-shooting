#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class World
{
private:
	sf::Texture worldBackgroundtex;
	sf::Sprite worldBackground;

	void initTexture();
	void initSprite();

public:
	World();

	//accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	void render(sf::RenderTarget* target);
};

