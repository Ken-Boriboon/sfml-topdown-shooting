#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	//Animation
	sf::IntRect currentFrame;

	int type;
	int dirX, dirY;
	float speed;
	int hp;
	int hpMax;
	unsigned point;

	//function
	void initVariables();
	void initTexture();
	void initSprite();
	void setSpawnPos();
	void initAnimation();
	void setStat(int type, float speed, int hpMax, unsigned point);

public:
	Enemy(int type);
	virtual ~Enemy();

	//accessors
	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPos() const;
	const int& getPoint() const;
	const int& getHp() const;

	//functions
	void update();
	void updateAnimation();
	void moveToPlayer(float playerX, float playerY);
	void render(sf::RenderTarget* target);
	void damaged(int damage);
	void knockBack(sf::Vector2f);
	bool insideField();
};
#endif //!ENEMY_H