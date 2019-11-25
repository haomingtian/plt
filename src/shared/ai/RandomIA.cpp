#include <string>
#include <iostream> 
#include "RandomIA.h"

using namespace std;
using namespace engine;
using namespace state;

namespace ai{
	void RandomIA::run (engine::Engine& eng){
	// L'IA effectue ses actions uniquement si c'est son tour
	if(eng.getPlayerActif()==camp && eng.getState().isEnd() == false){
		int random_action;
		//int random_position;
		//int random_attack;
		bool first_essai = true;
		bool impossible_deplacement = false;
		bool impossible_attack = false;
		for (unsigned int i = 0; i < eng.getState().getUnityArmy().size(); i++ ){
			// Reinitialisations de changement de personnage
			first_essai = true;
			impossible_deplacement = false;
			impossible_attack = false;
			
			if (eng.getState().getUnityArmy()[i]->getCamp() == camp){
				while (eng.getState().getUnityArmy()[i]->getStatus() != DEAD && eng.getState().getUnityArmy()[i]->getStatus() != WAITING){
					if(first_essai == true){
						cout<< "\t\t-> Début du tour de " << eng.getState().getUnityArmy()[i]->getName() << " <-" << endl;
						first_essai = false;
					}
				eng.getState().getUnityArmy()[i]->setStatus(SELECTED);
				//	Action random entre 3 choix : deplacement (0), attaque(1), finActions(2)
				//	Si le personnage vient de tenter une action et qu'elle fut impossible, 
				//	on élimine ce choix pour qu'il ne la retente pas tant que cela reste impossible.
				
				srand(time(NULL));
				if (impossible_deplacement == true && impossible_attack  == true){
					random_action = 2;
				}
				else if (impossible_deplacement == true && impossible_attack  == false){
					random_action = rand()%2+1 ;
				}
				else if (impossible_deplacement == false && impossible_attack  == true){
					random_action = rand()%2;
					if(random_action == 1){
						random_action = 2;
					}
				}
				else{random_action = rand()%3;}
	}
}
}
}
}
}
