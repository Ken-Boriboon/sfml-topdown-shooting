#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Item
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock remainTimer;

	int type;

	//function
	void initVariables();
	void initTexture();
	void initSprite();


public:
	Item(sf::Vector2f pos);
	virtual ~Item();

	const sf::FloatRect getBounds() const;
	const sf::Texture getTexture() const;

	bool itemUpdateDelete();
	int getType();

	void render(sf::RenderTarget* target);
};
#endif //!ITEM_H