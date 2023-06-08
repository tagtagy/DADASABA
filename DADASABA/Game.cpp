# include "Game.h"

Game::~Game() {
	if (player != nullptr) {
		delete player;
	}
}

Game::Game(const InitData& init)
	: IScene{ init }
{
	player = new Class_player();
}

void Game::update()
{
	
}

void Game::draw() const
{
	
}

