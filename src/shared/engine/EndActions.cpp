#include <string>
#include <iostream> 
#include "EndActions.h"
#include <unistd.h>

using namespace state;
using namespace std;
namespace engine{
	EndActions::EndActions (state::UnityArmy& target, bool player): target(target){
		id=ENDACTIONS;
		player=player;

	}
	void EndActions::execute (state::State& s){
		std::string newChaine;
		Event event(TEXTCHANGED);
		int waitTime = 500000;
	
		if (target.getStatus()!=WAITING && target.getStatus()!=DEAD){
			target.setStatus(WAITING);
			newChaine = target.getName() + " termine son tour";
			cout << "\t\t--- " << newChaine << " ---" << endl;
			event.text = newChaine;
			s.notifyObservers(event, s);
			usleep(waitTime);
			
			event.event_id = ALLCHANGED;
			s.notifyObservers(event, s);
		}
		else if(target.getStatus()==WAITING){
			newChaine = target.getName() + " a deja termine son tour";
			cout << "\t" << newChaine << endl;
			event.text = newChaine;
			s.notifyObservers(event, s);
			usleep(waitTime);
			
			event.event_id= ALLCHANGED;
			s.notifyObservers(event, s);
		}
		
		cout << "\n" ;
			
		}
	Json::Value EndActions::serialize(){

	Json::Value newCmd;	
	newCmd["id"] = id;
	newCmd["player"] = (int)player;
	//newCmd["target"] = target.indice;
	
	return newCmd;
}
}
