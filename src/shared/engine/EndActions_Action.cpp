#include <string>
#include <iostream> 
#include "EndActions_Action.h"
using namespace state;
using namespace std;
namespace engine{
	EndActions_Action::EndActions_Action (state::UnityArmy& target, bool player):target(target){
		player=player;
		id=ENDACTIONS_ACTION;
		old_status=target.getStatus();
		old_code_tuile=target.getCodeTuile();		
	}
	void EndActions_Action::apply (state::State& s){
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
	void EndActions_Action::undo (state::State& s){
		target.setStatus(state::WAITING);
		target.setCodeTuile(old_code_tuile);
	}
	state::UnityArmy& EndActions_Action::getTarget (){
		UnityArmy& ref_u_t=target;
		return ref_u_t;		
	}
}
