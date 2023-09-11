#include "World.h"

void World::initTexture(){
	this->worldBackgroundtex.loadFromFile("Textures/BackGround.png");
}

void World::initSprite(){
	this->worldBackground.setTexture(this->worldBackgroundtex); //OG 256x256
	this->worldBackground.scale(4.f, 4.f); //Now 1024x1024
	this->worldBackground.setPosition(
		1920 / 2 - this->worldBackground.getGlobalBounds().width / 2, 
		1080 / 2 - this->worldBackground.getGlobalBounds().height / 2);
}

World::World(){
	this->initTexture();
	this->initSprite();
}

const sf::Vector2f& World::getPos() const{
	return this->worldBackground.getPosition();
}

const sf::FloatRect World::getBounds() const{
	return this->worldBackground.getGlobalBounds();
}

void World::render(sf::RenderTarget* target){
	target->draw(this->worldBackground);
}