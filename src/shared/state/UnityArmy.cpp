#include <iostream> 
#include "UnityArmy.h" 
using namespace std;
namespace state {
UnityArmy ::UnityArmy(ArmyTypeId id, std::string n_name, bool n_camp){
	type_id=id;
	name=n_name;
	camp=n_camp;
	//currentlife=10;
	if(id==ARCHER){
		move_field=1;
		statistics.setAttack(100);
		statistics.setDefense(100);
		statistics.setCurrentLife(100);
	}
	else if(id==CAVLRY){
		move_field=1;
		statistics.setAttack(100);
		statistics.setDefense(100);
		statistics.setCurrentLife(100);
	}
	else if(id==INGENEER){
		move_field=1;
		statistics.setAttack(100);
		statistics.setDefense(100);
		statistics.setCurrentLife(100);
	}
	else if(id==INFANTRY){
		move_field=1;
		statistics.setAttack(100);
		statistics.setDefense(100);
		statistics.setCurrentLife(100);		
	}	
}

ArmyTypeId UnityArmy::getType (){
	return type_id;
}
/*int UnityArmy::getCurrentlife (){
	return currentlife;
}
void UnityArmy::setCurrentlife (int n_currentlife){
	currentlife=n_currentlife;	
}
std::string UnityArmy::getName (){
	return name;
}*/
/*int UnityArmy::getAttack (){
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
}*/
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



