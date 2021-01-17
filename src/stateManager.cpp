#include <stateManager.h>

WindowConfiguration StateManagerApplication::getWindowConfiguration() {
	// Defining an unresizable window of resolution 1280*720
	return { "Clause's Catstrophe ", {1280, 720}, false };
}

void StateManagerApplication::onInitialize()  {
	current_state = new menuState(this);
	ComponentLookUp::setUpMap();
	current_state->onEnter();

}

void StateManagerApplication::goToState() {
	if (next_state != nullptr)
	{
		if (current_state != nullptr) {
			current_state->onExit();
			current_state = next_state;
			next_state = nullptr;
			current_state->onEnter();
		}

	}
}

void StateManagerApplication::onDraw(double deltaTime) {
	//Draw Current state
	if (current_state != nullptr) {
		current_state->onDraw(deltaTime);
		goToState();
	}

}

void StateManagerApplication::onDestroy() {
	delete current_state;
}

void StateManagerApplication::setNextState(GameState* next_state_)
{
	next_state = next_state_;
}
