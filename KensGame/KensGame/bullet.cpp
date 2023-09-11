#include "bullet.h"

Bullet::Bullet(float pos_x, float pos_y, float dir_x, float dir_y, float speed){
	this->texture.loadFromFile("Textures/bullet.png");
	this->shape.setTexture(texture);

	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->Speed = speed;
}

Bullet::~Bullet(){
}

const sf::FloatRect Bullet::getBounds() const{
	return this->shape.getGlobalBounds();
}

const sf::Vector2f Bullet::getDir() const{
	return this->direction;
}

void Bullet::update(){
	//movement
	this->shape.move(this->Speed * this->direction);
}

void Bullet::render(sf::RenderTarget* target){
	target->draw(this->shape);
}