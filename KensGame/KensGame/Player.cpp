#include "Player.h"

void Player::initVariables(){
	this->moving = false;
	this->movementSpeed = 1.5f;

	this->attackCDMax = 15.f;
	this->attackCD = this->attackCDMax;
}

void Player::initTexture(){
	this->textureSheet.loadFromFile("Textures/player.png");
}

void Player::initSprite(){
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 16, 16);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(4.f, 4.f);
}

void Player::initAnimation(){
	this->animationTimer.restart();
}

Player::Player(){
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
}

const sf::Vector2f& Player::getPos() const{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const{
	return this->sprite.getGlobalBounds();
}

void Player::speedMod(float value){
	this->movementSpeed += value;
}

void Player::move(const float dirX, const float dirY){
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::setStartpos(float x, float y){
	this->sprite.setPosition(x, y);
}

const bool Player::attackAble(){//call when shoot
	if (this->attackCD >= this->attackCDMax) { //attackCD become 0 only when you successfully shoot
		this->attackCD = 0.f;
		return true;
	}return false;
}

void Player::updateAnimation() {
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.25f) {
		if (this->moving == true) { this->currentFrame.left += 16.f; 
			if (this->currentFrame.left > 48.f) { this->currentFrame.left = 0; }
		}else { this->currentFrame.left = 0.f; }

		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Player::updateMove(bool moving){
	this->moving = moving;
}

void Player::updateAttack()
{if (this->attackCD < this->attackCDMax) {this->attackCD += 0.5f;}}

void Player::update(){
	this->updateAttack();
	this->updateWindowBoundsCollision();
	this->updateAnimation();
}

void Player::updateWindowBoundsCollision(){
	//1920x1080 window and 1024x1024 game
	float LMost = (1920 / 2) - (1024 / 2);
	float RMost = ((1920 / 2) + (1024 / 2) - 64);
	float TMost = (1080 / 2) - (1024 / 2);
	float BMost = ((1080 / 2) + (1024 / 2) - 64);
	//left
	if (this->sprite.getGlobalBounds().left <= LMost)
	{this->sprite.setPosition(LMost, this->sprite.getGlobalBounds().top);}
	//right
	else if (this->sprite.getGlobalBounds().left >= RMost)
	{this->sprite.setPosition(RMost, this->sprite.getGlobalBounds().top);}
	//top
	if (this->sprite.getGlobalBounds().top <= TMost)
	{this->sprite.setPosition(this->sprite.getGlobalBounds().left, TMost);}
	//bottom
	else if (this->sprite.getGlobalBounds().top >= BMost)
	{this->sprite.setPosition(this->sprite.getGlobalBounds().left, BMost);}
}

void Player::render(sf::RenderTarget* target){
	target->draw(this->sprite);
}