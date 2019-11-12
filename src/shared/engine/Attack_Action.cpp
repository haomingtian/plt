#include <string>
#include <iostream> 
#include "Attack_Action.h"

using namespace state;
namespace engine{
	Attack_Action::Attack_Action (state::UnityArmy& attacker, state::UnityArmy& target, bool player):attacker(attacker),target(target){
		player=player;
		id=ATTACK_ACTION;
		hit_back= false;
		old_statistiques_attacker=attacker.getStatistics();
		old_statistiques_target=target.getStatistics();
		old_status_attacker=attacker.getStatus();
		old_status_target=target.getStatus();
		old_position_attacker=attacker.getPosition();
		old_position_target=target.getPosition();
	}
	state::UnityArmy& Attack_Action::getCible (){
		UnityArmy& ref_u_t=target;
		return ref_u_t;
	}
	state::UnityArmy& Attack_Action::getAttaquant (){
		UnityArmy& ref_u_a=attacker;
		return ref_u_a;
	}
	void Attack_Action::undo (state::State& s){
		attacker.getStatistics().setCurrentLife(old_statistiques_attacker.getCurrentLife());
		attacker.getStatistics().setAttack(old_statistiques_attacker.getAttack());
		attacker.getStatistics().setDefense(old_statistiques_attacker.getDefense());
		
		target.getStatistics().setCurrentLife(old_statistiques_target.getCurrentLife());
		target.getStatistics().setAttack(old_statistiques_target.getAttack());
		attacker.getStatistics().setDefense(old_statistiques_target.getDefense());
		
		attacker.getPosition().setX(old_position_attacker.getX());
	    attacker.getPosition().setY(old_position_attacker.getY());
	    target.getPosition().setX(old_position_target.getX());
	    target.getPosition().setY(old_position_target.getY());
	    
	    attacker.setStatus(state::AVAILABLE);
		target.setStatus(old_status_target);
	}
	void Attack_Action::apply (state::State& s){
		//A remplir apres calcul
	}
}
