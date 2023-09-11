#include "Enemy.h"
void Enemy::setStat(int type, float speed, int hpMax, unsigned point){
	this->type = type;
	this->speed = speed;
	this->hpMax = hpMax;
	this->hp = this->hpMax;
	this->point = point;
}

void Enemy::initVariables(){
	//random
	if (this->type == 0) { 
		int RNG1 = rand() % 100 + 1; 
		if (RNG1 <= 30) {this->setStat(1, 0.35f, 1, 10);}
		else if (RNG1 <= 50) {this->setStat(2, 0.6f, 1, 15);}
		else if (RNG1 <= 69) {this->setStat(3, 0.35f, 2, 15);}
		else if (RNG1 <= 89) {this->setStat(4, 0.6f, 2, 20);}
		else if (RNG1 <= 99) {this->setStat(5, 0.2f, 10, 150);}
		else if (RNG1 <= 100) { this->setStat(6, 0.8f, 25, 500); }
	}
}

void Enemy::initTexture(){
	if (this->type == 1){this->textureSheet.loadFromFile("Textures/mon1.png");}
	else if (this->type == 2) { this->textureSheet.loadFromFile("Textures/mon2.png"); }
	else if (this->type == 3) { this->textureSheet.loadFromFile("Textures/mon3.png"); }
	else if (this->type == 4) { this->textureSheet.loadFromFile("Textures/mon4.png"); }
	else if (this->type == 5) { this->textureSheet.loadFromFile("Textures/mon5.png"); }
	else if (this->type == 6) { this->textureSheet.loadFromFile("Textures/boss.png"); }
}

void Enemy::initSprite(){
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 16, 16);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(4.f, 4.f);
	if (this->type == 6) {
		this->sprite.setScale(4.5f, 4.5f);
	}
}

void Enemy::setSpawnPos(){
	int RNG = rand() % 4 + 1;
	if (RNG == 1) { 
		this->sprite.setPosition(
			static_cast<float>(rand() % (64 * 18) + (1920/2 - 64*18/2)),
			static_cast<float>((1080 / 2) - (1024 / 2) - 64)
		);
	}else if (RNG == 2) {
		this->sprite.setPosition(
			static_cast<float>(rand() % (64 * 18) + (1920/2 - 64*18/2)),
			static_cast<float>((1080 / 2) + (1024 / 2))
		);
	}else if (RNG == 3) {
		this->sprite.setPosition(
			static_cast<float>((1920 / 2) - (1024 / 2) -64),
			static_cast<float>(rand() % (64 * 18) + (1080/2 - 64*18/2))
		);
	}else if (RNG == 4) {
		this->sprite.setPosition(
			static_cast<float>((1920 / 2) + (1024 / 2)),
			static_cast<float>(rand() % (64*18) + (1080/2 - 64*18/2))
		);
	}
}

void Enemy::initAnimation(){
	this->animationTimer.restart();
}

void Enemy::update(){
	this->updateAnimation();
}

void Enemy::updateAnimation(){
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.25f){
		this->currentFrame.left += 16.f;
		if (this->currentFrame.left > 16.f) { this->currentFrame.left = 0.f; }

		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Enemy::moveToPlayer(float playerX, float playerY){
	float MonX = this->sprite.getPosition().x;
	float MonY = this->sprite.getPosition().y;
	//free move
	if (MonX < playerX){dirX = 1;}else if (MonX > playerX){dirX = -1;} else{dirX = 0;}
	if (MonY < playerY){dirY = 1;}else if (MonY > playerY){dirY = -1;} else{dirY = 0;}
	this->sprite.move(dirX * speed ,dirY * speed);
}

Enemy::Enemy(int type){
	this->type = type;
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->setSpawnPos();
	this->initAnimation();
}

Enemy::~Enemy(){
}

//accessors
const sf::FloatRect Enemy::getBounds() const{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f& Enemy::getPos() const{
	return this->sprite.getPosition();
}

const int& Enemy::getPoint() const{
	return this->point;
}

const int& Enemy::getHp() const{
	return this->hp;
}

void Enemy::render(sf::RenderTarget* target){
	target->draw(this->sprite);
}

void Enemy::damaged(int damage){
	this->hp -= damage;
}

void Enemy::knockBack(sf::Vector2f Dir){
	switch (this->type) {
	case 5:
		break;
	case 6:
		this->sprite.move(Dir.x * 8, Dir.y * 8);
		break;
	default:
		this->sprite.move(Dir.x * 24, Dir.y * 24);
	}
}

bool Enemy::insideField(){
	if((this->sprite.getPosition().x >= 1080/2 - 1024/2 + 64)  &&
	(this->sprite.getPosition().x <= 1080 / 2 + 1024 / 2 - 64) &&
	(this->sprite.getPosition().y >= 1920 / 2 - 1024 / 2 + 64) &&
	(this->sprite.getPosition().y <= 1920 / 2 + 1024 / 2 - 64))
	{ return true; }
	else { return false; }
}