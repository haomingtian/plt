#include <string>
#include <iostream>     
#include "Move_Action.h"

using namespace state;
using namespace std;
namespace engine{
	Move_Action::Move_Action (state::UnityArmy& target, state::Position& destination, bool player):target(target){
		id=MOVE_ACTION;
		new_pos=destination;
		old_pos=target.getPosition();
		old_stat=target.getStatistics();
		old_field_move=target.getMoveField();
		this->player=player;
	}
    void Move_Action::apply (state::State& s){
		
		}
    void Move_Action::undo (state::State& s){
		target.setStatus(state::AVAILABLE);
		target.getPosition().setX(old_pos.getX());
		target.getPosition().setY(old_pos.getY());

		target.getStatistics().setCurrentLife(old_stat.getCurrentLife());
		target.getStatistics().setAttack(old_stat.getAttack());
		target.getStatistics().setDefense(old_stat.getDefense());
		//target.getStatistics().setCritique(oldStat.getCritique());
		//target.getStatistics().setEsquive(oldStat.getEsquive());

		target.setMoveField(old_field_move);
	}
    state::UnityArmy& Move_Action::getTarget (){
		UnityArmy& ref_u=target;
		return ref_u;
	}
    state::Position& Move_Action::getDestination (){
		Position& ref_pos=new_pos;
		return ref_pos;
	}
}
