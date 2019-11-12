#include <string>
#include <iostream> 
#include "Attack.h"
namespace engine{
	Attack::Attack (state::UnityArmy& attacker, state::UnityArmy& target, bool player):attacker(attacker),target(target){
		//attacker=attacker;
		//target=target;
		player=player;
		id= ATTAQUE;
	}
	void Attack::execute (state::State& s){
		//A remplir ultérieurement
	}
	Json::Value Attack::serialize (){
	Json::Value newCmd;
	newCmd["id"] = id;
	newCmd["player"] = (int)player;
	//newCmd["attacker"] = attacker.indice;
	//newCmd["target"] = target.indice;
	
	return newCmd;
	}
}
