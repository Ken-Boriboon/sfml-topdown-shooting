#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
	
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	//Animation
	sf::IntRect currentFrame;

	float movementSpeed;
	float attackCD;
	float attackCDMax;

	//private functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();

public:
	Player();
	bool moving;
	//accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	//modifier
	void speedMod(float value);

	//function
	void move(const float dirX, const float dirY);
	void setStartpos(float x, float y);
	const bool attackAble();

	void updateAnimation();
	void updateMove(bool moving);
	void updateAttack();
	void update();
	void updateWindowBoundsCollision();
	void render(sf::RenderTarget* target);

};