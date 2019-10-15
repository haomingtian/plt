#include <iostream> 
#include "UnityArmy.h" 
using namespace std;
namespace state {
UnityArmy ::UnityArmy(ArmyTypeId id, std::string n_name, bool n_camp){
	type_id=id;
	name=n_name;
	camp=n_camp;
	currentlife=10;
	if(id==ARCHER){
		move_field=1;
		pattack=100;
		pdefense=100;
	}
	else if(id==CAVLRY){
		move_field=2;
		pattack=150;
		pdefense=150;
	}
	else if(id==INGENEER){
		move_field=2;
		pattack=200;
		pdefense=200;
	}
	else if(id==INFANTRY){
		move_field=1;
		pattack=250;
		pdefense=250;		
	}	
}

ArmyTypeId UnityArmy::getType (){
	return type_id;
}
int UnityArmy::getCurrentlife (){
	return currentlife;
}
void UnityArmy::setCurrentlife (int n_currentlife){
	currentlife=n_currentlife;	
}
std::string UnityArmy::getName (){
	return name;
}
int UnityArmy::getAttack (){
	return pattack;
}
void UnityArmy::setAttack (int n_pattack){
	pattack=n_pattack;
}
int UnityArmy::getDefense (){
	return pdefense;
}
void UnityArmy::setDefense (int n_pdefense){
	pdefense=n_pdefense;
}
bool UnityArmy::getCamp (){
	return camp;
}
int UnityArmy::getMoveField (){
	return move_field;
}
void UnityArmy::setMoveField (int n_move_field){
	move_field=n_move_field;
}
}



