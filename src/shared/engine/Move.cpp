#include <string>
#include <iostream>     
#include "Move.h"

using namespace state;
namespace engine{
	Move::Move (state::UnityArmy& target, state::Position& destination, bool player): target(target), destination(destination){
		player=player;
		id=MOVE;
		
	}
    void execute (state::State& s){
		
	}
    /*Json::Value Move::serialize (){
		Json::Value newCmd;
		newCmd["id"] = id;
		newCmd["player"] = (int)player;
		//newCmd["cible"] = cible.indice;
		newCmd["xDestination"] = destination.getX();
		newCmd["yDestination"] = destination.getY();
		
		return newCmd;
	}*/
}
