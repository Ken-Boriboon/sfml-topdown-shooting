#include "Game.h"

//private function
void Game::initWindow(){
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Literally Me",
		sf::Style::Close | sf::Style::Fullscreen);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initSound(){
	this->BGMBuffer.loadFromFile("Sound/BGM.wav");
	this->BGM.setBuffer(this->BGMBuffer);
	this->hitBuffer.loadFromFile("Sound/hitSound.wav");
	this->hitS.setBuffer(this->hitBuffer);
	this->badgeBuffer.loadFromFile("Sound/badgeSound.wav");
	this->badgeS.setBuffer(this->badgeBuffer);
	this->bootBuffer.loadFromFile("Sound/bootSound.wav");
	this->bootS.setBuffer(this->bootBuffer);
	this->hitedBuffer.loadFromFile("Sound/hitedSound.wav");
	this->hitedS.setBuffer(this->hitedBuffer);
	this->lifeBuffer.loadFromFile("Sound/lifeSound.wav");
	this->lifeS.setBuffer(this->lifeBuffer);
	this->nukeBuffer.loadFromFile("Sound/nukedSound.wav");
	this->nukeS.setBuffer(this->nukeBuffer);
	this->shotgunBuffer.loadFromFile("Sound/shotgunSound.wav");
	this->shotgunS.setBuffer(this->shotgunBuffer);
}

void Game::initPlay(){
	this->initWorldAndSystem();
	this->initplayGUI();
	this->initPlayer();
	this->initEnemies();
	this->BGM.play();
}
	
void Game::initWorldAndSystem(){
	this->world = new World();
	this->life = 3;
	this->score = 0;
	this->itemNow = 0;
	this->itemUsing = 0;
	this->pause = false;
}

void Game::initplayGUI(){
	this->scoreText.setFont(this->Westernfont);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setCharacterSize(40);
	this->scoreText.setPosition(1920/2 - 1024/2 - 250, 1080.0/2);

	this->scoreTexture.loadFromFile("Textures/scoreIcon.png");
	this->scoreSpirte.setTexture(scoreTexture);
	this->scoreSpirte.setScale(4, 4);
	this->scoreSpirte.setPosition(1920 / 2 - 1024 / 2 - 260 - this->scoreSpirte.getGlobalBounds().width, 1080.0/2 + 5);

	this->lifeText = this->scoreText;
	this->lifeText.setPosition(1920/2 - 1024 /2 -250, 1080/2 - 50);

	this->lifeTexture.loadFromFile("Textures/lifeIcon.png");
	this->lifeSpirte.setTexture(lifeTexture);
	this->lifeSpirte.setScale(3, 3);
	this->lifeSpirte.setPosition(1920 / 2 - 1024 / 2 - 260 - this->lifeSpirte.getGlobalBounds().width, 1080.0/2 - 45);

	this->itemGUITexture.loadFromFile("Textures/itemgui.png");
	this->itemGUISprite.setTexture(this->itemGUITexture);
	this->itemGUISprite.setScale(6, 6);
	this->itemGUISprite.setPosition(1920 / 2 - 1024 / 2 - 250, 1080 / 2 - 100 - this->itemGUISprite.getGlobalBounds().height);

	this->itemEmptyTexture.loadFromFile("Textures/itemNo.png");
	this->itemSprite.setTexture(this->itemEmptyTexture);
	this->itemSprite.setScale(4, 4);
	sf::FloatRect itemGUI = this->itemGUISprite.getGlobalBounds();
	sf::FloatRect item = this->itemSprite.getGlobalBounds();
	this->itemSprite.setPosition((itemGUI.left + itemGUI.width / 2) - item.width / 2, (itemGUI.top + itemGUI.height / 2) - item.height / 2);

	this->InstructionTexture.loadFromFile("Textures/instruction.png");
	this->Instruction.setTexture(this->InstructionTexture);
	this->Instruction.setScale(4, 4);
	this->Instruction.setPosition(1920/2 + 1024/2 + 50, 1080/2 - this->Instruction.getGlobalBounds().height/2);
}

void Game::initPlayer(){
	this->player = new Player();
	this->player->setStartpos(1920.0/2 - (64/2), 1080.0/2 - (64/2));
}

void Game::initEnemies(){
		bool bossMa = false;
		this->timeMax = 1.5f;
		this->spawnTimer.restart();
}

void Game::nameTextBar(){
	this->THfont.loadFromFile("Fonts/THSarabunNew.TTF");
	this->nameBar.setSize(sf::Vector2f(1920.f, 30.f));
	this->nameBar.setFillColor(sf::Color::Black);
	this->nameBar.setPosition(sf::Vector2f(this->window->getSize().x / 2 - this->nameBar.getSize().x / 2, 0.f));

	this->nameText.setFont(this->THfont);
	this->nameText.setCharacterSize(40);
	this->nameText.setFillColor(sf::Color::White);
	this->nameText.setString("Borbiboon Yimramai 66010434");
	this->nameText.setPosition(sf::Vector2f(this->window->getSize().x / 2 - this->nameText.getGlobalBounds().width / 2, -15.f));

	this->frameTexture.loadFromFile("Textures/frame.png");
	this->frame.setTexture(this->frameTexture);
}

//Con/Des 
Game::Game(){
	this->initWindow();
	this->initSound();
	this->nameTextBar();
	this->initMenu();
	this->initPause();
	this->initboard();
	this->initgameOver();
}

Game::~Game(){
	delete this->window;
	delete this->world;
	delete this->player;

	for (auto* i : this->bullets){delete i;}
	for (auto* i : this->enemies){delete i;}
	for (auto* i : this->items){delete i;}
}

//run
void Game::run()
{
	while (this->window->isOpen()){
		this->window->clear();
		if (this->menu){
			this->updateMenu();
			this->renderMenu();
		}
		else if (this->gamerOver){
			this->updategameOver();
			this->rendergameOver();
		}
		else if (this->leaderboard){
			this->updateboard();
			this->renderboard();
		}
		else if (this->play){
			this->updatePlay();
			this->renderPlay();
			if (this->pause){
				this->updatePause();
				this->renderPause();
			}
		}

		this->window->draw(this->nameBar);
		this->window->draw(this->nameText);
		this->window->display();
	}
}

//menu
void Game::initMenu(){
	this->Westernfont.loadFromFile("Fonts/Data70.otf");

	this->menuBGTexture.loadFromFile("Textures/menu.png");
	this->menuBG.setTexture(this->menuBGTexture);
	this->menuBG.scale(4.f, 4.f);
	this->menuBG.setPosition(1920 / 2 - 1024 / 2, 1080 / 2 - 1024 / 2);

	this->menuPlayTexture.loadFromFile("Textures/start.png");
	this->menuPlay.setTexture(this->menuPlayTexture);
	this->menuPlay.setPosition(1920/2 - this->menuPlay.getGlobalBounds().width/2, 1080/2 + 50);

	this->menuLeaderboardTexture.loadFromFile("Textures/leaderboard.png");
	this->menuLeaderboard.setTexture(this->menuLeaderboardTexture);
	this->menuLeaderboard.setPosition(1920 / 2 - this->menuLeaderboard.getGlobalBounds().width / 2, 1080 / 2 + 50 + 79 + 20);

	this->menuExitTexture.loadFromFile("Textures/exit.png");
	this->menuExit.setTexture(this->menuExitTexture);
	this->menuExit.setPosition(1920 / 2 - this->menuExit.getGlobalBounds().width / 2, 1080 / 2 + 50 + 158 + 40);
}

void Game::updateMenu(){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(this->menuPlay.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		{this->menu = false; this->play = true; this->initPlay();}
		else if (this->menuLeaderboard.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		{this->menu = false; this->leaderboard = true; this->sorting();}
		else if (this->menuExit.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		{this->window->close();}
	}
}

void Game::renderMenu(){
	this->window->draw(this->menuBG);
	this->window->draw(this->menuPlay);
	this->window->draw(this->menuLeaderboard);
	this->window->draw(this->menuExit);
}

//pause
void Game::initPause(){
	this->pauseTexture.loadFromFile("Textures/pause.png");
	this->pauseSpirte.setTexture(this->pauseTexture);
	this->pauseSpirte.setPosition(1920 / 2 - this->pauseSpirte.getGlobalBounds().width / 2, 1080 / 2 + 50);

	this->resumeTexture.loadFromFile("Textures/resume.png");
	this->resume.setTexture(this->resumeTexture);
	this->resume.setPosition(1920 / 2 - this->resume.getGlobalBounds().width / 2, 1080 / 2 + 50 + 79 + 20);

	this->pauseBackTexture.loadFromFile("Textures/surrender.png");
	this->pauseBack.setTexture(this->pauseBackTexture);
	this->pauseBack.setPosition(1920 / 2 - this->pauseBack.getGlobalBounds().width / 2, 1080 / 2 + 50 + 158 + 40);
}

void Game::updatePause(){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if (this->resume.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		{this->pause = false;}
		else if (this->pauseBack.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		{this->pause = false; this->surrender = true;}
	}
}

void Game::renderPause(){
	this->window->draw(this->pauseSpirte);
	this->window->draw(this->resume);
	this->window->draw(this->pauseBack);
}

//gameover
void Game::gameEnd(){
	this->BGM.stop();
	this->surrender = false;
	this->enemies.clear();
	this->items.clear();
	this->bullets.clear();
	this->nameShow.setString("");
	this->mark = 0;
	this->ssScore = {};
	this->ssScore << "Score : " << this->score;
	this->gameOverScore = this->nameShow;
	this->gameOverScore.setString(this->ssScore.str());
	this->gameOverScore.setPosition(1920 / 2 - this->gameOverScore.getGlobalBounds().width / 2, 1080 / 2 - 1024 / 2 + 50);
}

void Game::initgameOver(){
	this->gameOverBGTexture.loadFromFile("Textures/gameOverBG.png");
	this->gameOverBG.setTexture(this->gameOverBGTexture);
	this->gameOverBG.scale(4.f, 4.f);
	this->gameOverBG.setPosition(1920 / 2 - 1024 / 2, 1080 / 2 - 1024 / 2);

	this->mainmenuTexture.loadFromFile("Textures/mainmenu.png");
	this->mainmenu.setTexture(this->mainmenuTexture);
	this->mainmenu.setPosition(1920/2 - 1024/2 + 50, 1080/2 + 1024/2 - 50 -this->mainmenu.getGlobalBounds().height);

	this->gameOverExitTexture.loadFromFile("Textures/exit.png");
	this->gameOverExit.setTexture(this->gameOverExitTexture);
	this->gameOverExit.setPosition(1920/2 + 1024/2 - 50 - this->gameOverExit.getGlobalBounds().width, 1080/2 + 1024/2 - 50 - this->gameOverExit.getGlobalBounds().height);

	this->gameOverSaveTexture.loadFromFile("Textures/save.png");
	this->gameOverSave.setTexture(this->gameOverSaveTexture);
	this->gameOverSave.setPosition(1920/2 - this->gameOverSave.getGlobalBounds().width/2, 1080/2 + 300 - this->gameOverSave.getGlobalBounds().height);

	this->nameShow.setFont(this->Westernfont);
	this->nameShow.setCharacterSize(60);
	this->nameShow.setFillColor(sf::Color::White);
	this->nameShow.setPosition(1920/2 - 200, 1080/2);
}

void Game::updategameOver(){
	while (this->window->pollEvent(event)){
		if (this->gamerOver) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (this->mainmenu.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
				{this->gamerOver = false; this->menu = true;}
				else if (this->gameOverExit.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
				{this->window->close();}
				else if (this->gameOverSave.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition()))){	
					std::ofstream saveFile("scores.txt", std::ios::app);
					saveFile << saveName << " " << this->score << "\n";
					saveFile.close(); 
					this->window->close();
				}
			}
			else if (event.type == sf::Event::TextEntered){
				if (event.text.unicode <= 127){
					if (event.text.unicode != '\b'){
						saveName += static_cast<char>(event.text.unicode);}
					else if (event.text.unicode == '\b' && !saveName.empty()) {
						saveName.pop_back();}
				}
			}
		}
	}
	this->nameShow.setString(saveName);

	if (this->mark == 0){
		saveName = "";
		mark++;
	}
}

void Game::rendergameOver(){
	this->window->draw(this->gameOverBG);
	this->window->draw(this->mainmenu);
	this->window->draw(this->gameOverExit);
	this->window->draw(this->gameOverSave);
	this->window->draw(this->nameShow);
	this->window->draw(this->gameOverScore);
}

//leaderboard
//***** fix sorting *****
void Game::sorting(){
	struct playerBoard {
		std::string name;
		int score;
	};

	std::ifstream scoresFile("scores.txt");
	std::vector<playerBoard> playersBoard;
	std::string line;

	while (std::getline(scoresFile, line)) {
		std::istringstream iss(line);
		playerBoard playerBoard;
		iss >> playerBoard.name >> playerBoard.score;
		playersBoard.push_back(playerBoard);
	}
	scoresFile.close();

	std::sort(playersBoard.begin(), playersBoard.end(), [](const playerBoard& a, const playerBoard& b)
		{return a.score > b.score;});
	
	for (int i = 0; i < 10 && i < playersBoard.size(); ++i) {
		ssleaderScore << i + 1 << ". " << playersBoard[i].name << " : " << playersBoard[i].score << "\n";
		this->leadersScore[i].setString(ssleaderScore.str());
		this->leadersScore[i].setFont(this->Westernfont);
		this->leadersScore[i].setCharacterSize(40);
		this->leadersScore[i].setFillColor(sf::Color::White);
		this->leadersScore[i].setPosition(1920/2 - 1024/2 + 300, 1080/2 - 1024/2 + 75*(i+2));
		ssleaderScore = {};
	}
}

void Game::initboard(){
	this->boardBGTexture.loadFromFile("Textures/boardBG.png");
	this->boardBG.setTexture(this->boardBGTexture);
	this->boardBG.scale(4.f, 4.f);
	this->boardBG.setPosition(1920 / 2 - 1024 / 2, 1080 / 2 - 1024 / 2);

	this->backButtonTexture.loadFromFile("Textures/back.png");
	this->backButton.setTexture(this->backButtonTexture);
	this->backButton.setPosition(1920/2 - 1024/2 + 50, 1080/2 + 1024/2 -50 - this->backButton.getGlobalBounds().height);

	this->boardH.setFont(this->Westernfont);
	this->boardH.setCharacterSize(60);
	this->boardH.setFillColor(sf::Color::White);
	this->boardH.setString("Leaderboard");
	this->boardH.setPosition(1920 / 2 - this->boardH.getGlobalBounds().width / 2, 1080 / 2 - 1024 / 2 + 50);
}

void Game::updateboard(){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
		{this->leaderboard = false; this->menu = true;}
	}
}

void Game::renderboard(){
	this->window->draw(this->boardBG);
	this->window->draw(this->backButton);
	this->window->draw(this->boardH);
	for (int i = 0; i < 10; ++i){this->window->draw(this->leadersScore[i]);}
}

//play
void Game::updatePlay() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		if (!this->holdESC) { this->holdESC = true; this->pause = !this->pause; }
	}
	else { this->holdESC = false; }

	if (this->life > 0 && this->pause == false) {
		if (this->surrender) { this->pause = true; }
		this->updateMoveInput();
		this->combatInput();
		this->player->update();
		this->updatebullets();
		this->updateEnemies();
		this->updateCombat();
		this->updateItems();
		this->updateItemBuff();
		this->updateGUI();
	}
	else if (this->life == 0 || this->surrender) {this->play = false; this->gamerOver = true; this->gameEnd();}
}

void Game::updateGUI(){
	std::stringstream sspoint;
	sspoint << "Points: " << this->score;
	this->scoreText.setString(sspoint.str());

	std::stringstream sslife;
	sslife << "Life: " << this->life;
	this->lifeText.setString(sslife.str());
}

void Game::updateMoveInput(){
	this->player->updateMove(false);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { this->player->move(-1.f, 0.f); this->player->updateMove(true);}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){this->player->move(1.f, 0.f); this->player->updateMove(true);}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){this->player->move(0.f, -1.f); this->player->updateMove(true);}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){this->player->move(0.f, 1.f); this->player->updateMove(true);}
}

//***** fix fring *****
void Game::combatInput(){
	float middleX = this->player->getPos().x +16;
	float middleY = this->player->getPos().y + 16;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->player->attackAble()){
		this->bullets.push_back(new Bullet(middleX, middleY, 0.f, -1.f, 3.7f));
		if(this->itemUsing == 3 || this->itemUsing == 4){
			this->bullets.push_back(new Bullet(middleX, middleY, 0.1f, -1.f, 3.7f));
			this->bullets.push_back(new Bullet(middleX, middleY, -0.1f, -1.f, 3.7f));
			if (this->itemUsing == 4) {
				this->bullets.push_back(new Bullet(middleX, middleY, 0.2f, -1.f, 3.7f));
				this->bullets.push_back(new Bullet(middleX, middleY, -0.2f, -1.f, 3.7f));
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->player->attackAble()){
		this->bullets.push_back(new Bullet(this->player->getPos().x + 16, this->player->getPos().y + 16, -1.f, 0.f, 3.7f));
		if (this->itemUsing == 3 || this->itemUsing == 4) {
			this->bullets.push_back(new Bullet(middleX, middleY, -1.f, -0.1f, 3.7f));
			this->bullets.push_back(new Bullet(middleX, middleY, -1.f, 0.1f, 3.7f));
			if (this->itemUsing == 4) {
				this->bullets.push_back(new Bullet(middleX, middleY, -1.f, -0.2f, 3.7f));
				this->bullets.push_back(new Bullet(middleX, middleY, -1.f, 0.2f, 3.7f));
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->player->attackAble()){
		this->bullets.push_back(new Bullet(this->player->getPos().x + 16, this->player->getPos().y + 16, 1.f, 0.f, 3.7f));
		if (this->itemUsing == 3 || this->itemUsing == 4) {
			this->bullets.push_back(new Bullet(middleX, middleY, 1.f, -0.1f, 3.7f));
			this->bullets.push_back(new Bullet(middleX, middleY, 1.f, 0.1f, 3.7f));
			if (this->itemUsing == 4) {
				this->bullets.push_back(new Bullet(middleX, middleY, 1.f, -0.2f, 3.7f));
				this->bullets.push_back(new Bullet(middleX, middleY, 1.f, 0.2f, 3.7f));
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->player->attackAble()){
		this->bullets.push_back(new Bullet(this->player->getPos().x + 16, this->player->getPos().y + 16, 0.f, 1.f, 3.7f));
		if (this->itemUsing == 3 || this->itemUsing == 4) {
			this->bullets.push_back(new Bullet(middleX, middleY, 0.1f, 1.f, 3.7f));
			this->bullets.push_back(new Bullet(middleX, middleY, -0.1f, 1.f, 3.7f));
			if (this->itemUsing == 4) {
				this->bullets.push_back(new Bullet(middleX, middleY, 0.2f, 1.f, 3.7f));
				this->bullets.push_back(new Bullet(middleX, middleY, -0.2f, 1.f, 3.7f));
			}
		}
	}
	//item
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->itemNow > 0) {
		this->buffByItem();
		this->itemSprite.setTexture(this->itemEmptyTexture);
		this->itemDuration.restart();
	}
}

void Game::buffByItem(){
	if (this->itemNow == 2) {
		this->player->speedMod(1.f);
		this->bootS.play();
	}else if (this->itemNow == 3){
		this->shotgunS.play();
	}else if (this->itemNow == 4){
		this->badgeS.play();
	}else if (this->itemNow == 5){
		nukeAll();
		this->nukeS.play();
	}
	this->itemUsing = this->itemNow;
	this->itemNow = 0;
}

void Game::updateItemBuff(){
	if (this->itemUsing == 2 && this->itemDuration.getElapsedTime().asSeconds() >= 5.f){this->player->speedMod(-1.f); this->itemUsing = 0;}
	else if (this->itemUsing == 3 && this->itemDuration.getElapsedTime().asSeconds() >= 6.f){this->itemUsing = 0;}
	else if (this->itemUsing == 4 && this->itemDuration.getElapsedTime().asSeconds() >= 8.f){this->itemUsing = 0;}
	else if (this->itemUsing == 5 && this->itemDuration.getElapsedTime().asSeconds() >= 0.f){this->itemUsing = 0;}
}

void Game::updateEnemies(){	
	//spawning
	if (this->spawnTimer.getElapsedTime().asSeconds() >= timeMax){
		int scale = this->score / 1000;
		for (int c = 1; c <= 2 + scale; c++) { this->enemies.push_back(new Enemy(0)); this->spawnTimer.restart();}
	}
	//move
	for (auto* enemy : this->enemies){
		enemy->update();
		enemy->moveToPlayer(this->player->getPos().x, this->player->getPos().y);
	}
}

void Game::nukeAll(){	
	unsigned counter = 0;
	for (auto* enemy : this->enemies){
		if (enemy->getPoint() != 400){
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter; //erase the enemy make the array's size reduced by 1
		}++counter;
	}
}

void Game::updateCombat(){
	//fired
	for (int i = 0; i < this->enemies.size(); i++){
		bool bullet_delete = false;
		for (size_t k = 0; k < this->bullets.size() && !bullet_delete; k++){
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())){
				this->enemies[i]->knockBack(this->bullets[k]->getDir());
				this->enemies[i]->damaged(1);
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				if (this->enemies[i]->getHp() <= 0){
					this->score += this->enemies[i]->getPoint();
					if (this->enemies[i]->insideField()){
						int RNG = rand() % 10;
						if (RNG <= 2) {this->items.push_back(new Item(this->enemies[i]->getPos()));}
					}
					this->hitS.play();
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);
				}
				bullet_delete = true;
			}
		}
	}

	//collision with player
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool nuked = false;
		if (!nuked && this->enemies[i]->getBounds().intersects(this->player->getBounds()))
		{
			nukeAll();
			this->hitedS.play();
			this->life -= 1;
			nuked = true;
		}
	}

}

void Game::updatebullets() {
	unsigned counter = 0;
	for (auto* bullet : this->bullets){
		bullet->update();
		if (bullet->getBounds().top <= (1080/2) - (1024/2)									||
			bullet->getBounds().top + bullet->getBounds().height >= (1080 / 2) + (1024 / 2)	||
			bullet->getBounds().left <= (1920 / 2) - (1024 / 2)								||
			bullet->getBounds().left + bullet->getBounds().width >= (1920 / 2) + (1024 / 2)){
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}++counter;
	}
}

void Game::updateItems(){
	unsigned counter = 0;
	for (auto* item : this->items){
		if (item->itemUpdateDelete()){
			delete this->items.at(counter);
			this->items.erase(this->items.begin() + counter);
			--counter;
		}else if (item->getBounds().intersects(this->player->getBounds())){
			int type = item->getType();
			if (type == 1) { this->life += 1; this->lifeS.play();}
			else {
				this->itemSpriteTexture = item->getTexture();
				this->itemNow = type;
				this->itemSprite.setTexture(this->itemSpriteTexture);
			}
			delete this->items.at(counter);
			this->items.erase(this->items.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void Game::renderPlay(){
	this->world->render(this->window);
	this->player->render(this->window);
	for (auto* bullet : this->bullets){bullet->render(this->window);}
	for (auto* enemy : this->enemies){enemy->render(this->window);}
	for (auto* item : this->items){item->render(this->window);}
	this->window->draw(this->frame);
	this->renderGUI();
}

void Game::renderGUI(){
	this->window->draw(this->scoreText);
	this->window->draw(this->lifeText);
	this->window->draw(this->itemGUISprite);
	this->window->draw(this->itemSprite);
	this->window->draw(this->lifeSpirte);
	this->window->draw(this->scoreSpirte);
	this->window->draw(this->Instruction);
}