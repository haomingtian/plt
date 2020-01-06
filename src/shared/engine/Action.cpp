#include "engine.h"

using namespace engine;

ActionID Action::getActionID(){
	return actionId;
}

bool Action::getPlayer() {
	return player;
}

void Action:: apply (state::State& state){
	
}

void Action::undo (state::State& state){
	
}
