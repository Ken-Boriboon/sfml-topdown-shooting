#include "Item.h"

void Item::initVariables(){
	int RNG = rand() % 100 + 1;
	if (RNG <= 5) { this->type = 1; }
	else if (RNG <= 35) { this->type = 2; }
	else if (RNG <= 85) { this->type = 3; }
	else if (RNG <= 95) { this->type = 4; }
	else if (RNG <= 100) { this->type = 5; }
}

void Item::initTexture(){
	if (this->type == 1) {this->textureSheet.loadFromFile("Textures/itemlife.png");}
	else if (this->type == 2) { this->textureSheet.loadFromFile("Textures/itemBoot.png"); }
	else if (this->type == 3) { this->textureSheet.loadFromFile("Textures/itemShotgun.png"); }
	else if (this->type == 4) { this->textureSheet.loadFromFile("Textures/itemBadge.png"); }
	else if (this->type == 5) { this->textureSheet.loadFromFile("Textures/itemNuke.png"); }
}

void Item::initSprite(){
	this->sprite.setTexture(this->textureSheet);
	this->sprite.setScale(3.f, 3.f);
}

Item::Item(sf::Vector2f pos){
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->sprite.setPosition(pos.x, pos.y);
	this->remainTimer.restart();
}

Item::~Item(){
}

const sf::FloatRect Item::getBounds() const{
	return this->sprite.getGlobalBounds();
}

const sf::Texture Item::getTexture() const{
	return this->textureSheet;
}

bool Item::itemUpdateDelete(){
	if (this->remainTimer.getElapsedTime().asSeconds() >= 3.f) { return true; }
	else { return false; }
}

int Item::getType(){
	return this->type;
}

void Item::render(sf::RenderTarget* target){
	target->draw(this->sprite);
}