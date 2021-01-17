
#ifndef PLAYER__H
#define PLAYER__H

#include <components/component.h>

class Player :public Component
{
private:
	unsigned int lives;
	unsigned int score;

public:
	Player(std::weak_ptr<Entity> entity);
	unsigned int getLives();
    unsigned int getScore();
	void incrementScore(int value);
	void decrementLives();
};
#endif // !PLAYER__H
