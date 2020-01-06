#include "engine.h"
#include "state.h"

#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

EndAction::EndAction(state::UnityArmy& target, bool newPlayer):target(target){
	id = TURNOVER;
	player = newPlayer;
}

void EndAction::execute(state::State& state){
	if (target.getStatus()!=WAITING && target.getStatus()!=DEAD){
		target.setStatus(WAITING);
		cout << "\t\t--- " << target.getName() << " termine son tour. ---" << endl;
	}
	else if(target.getStatus()==WAITING){
		cout << target.getName() << " a déjà terminé son tour d'actions, il ne peut plus effectuer d'actions !" <<endl;
	}
	
	cout << "\n" ;
}
