#include "engine.h"
#include "state.h"
#include <unistd.h>
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

FinAction::FinAction (state::UnityArmy& target, bool player):target(target){
	actionId=FIN_ACTION;
	this->player = player;
	oldStatus = target.getStatus();
	oldTileCode = target.getCodeTuile();
}

state::UnityArmy& FinAction::getTarget(){
    UnityArmy& refPersoC = target;
	return refPersoC;
}

void FinAction:: apply (state::State& state){
	//cout<<"finaction"<<endl;
	if (target.getStatus()!=WAITING && target.getStatus()!=DEAD){
		target.setStatus(WAITING);
		cout << "\t\t--- " << target.getName() << " termine son tour. ---" << endl;
	}
	else if(target.getStatus()==WAITING){
		cout << target.getName() << " a déjà terminé son tour d'actions, il ne peut plus effectuer d'actions !" <<endl;
	}
	
	cout << "\n" ;
}

void FinAction::undo (state::State& state){
	//target.setStatut(oldStatut);
	target.setStatus(state::AVAILABLE);
	target.setCodeTuile(oldTileCode);
}
