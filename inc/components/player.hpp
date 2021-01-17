
#ifndef PLAYER__H
#define PLAYER__H

#include <components/component.h>

class Player :public Component
{
private:
	unsigned int lives;
	unsigned int score;

public:
	Player(std::weak_ptr<Entity> entity) :Component(entity) {
		lives = 3;
		score = 0;
		type = PLAYER;
	}
};
#endif // !PLAYER__H
