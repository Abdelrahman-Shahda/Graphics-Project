#include <components/player.hpp>

Player::Player(std::weak_ptr<Entity> entity) :Component(entity) {
	lives = 3;
	score = 0;
	type = PLAYER;
}

unsigned int Player::getLives()
{
	return lives;
}

unsigned int Player::getScore()
{
	return score;
}

void Player::incrementScore(int value)
{
	score += value;
}

void Player::decrementLives()
{
	lives--;
}