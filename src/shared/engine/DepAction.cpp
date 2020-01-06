#include "engine.h"
#include "state.h"

#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

DepAction::DepAction (state::UnityArmy& target, state::Position& destination, bool player) : target(target) {
	actionId = DEP_ACTION;
	newPosition = destination;
	oldPosition = target.getPosition();
	oldStatistics = target.getStatistics();
	oldMove = target.getMove();
	this->player = player;
}

state::Position& DepAction::getDestination(){
	Position& refPos=newPosition;
	return refPos;
}

state::UnityArmy& DepAction::getTarget(){
    UnityArmy& refPerso = target;
	return refPerso;
}

void DepAction::apply (state::State& state){
	//cout<<"depAction"<<endl;
	bool deplacementPossible = false;
	if (target.getStatus()!=WAITING && target.getStatus()!=DEAD){

		if(target.getMove()!=0){
			vector<Position> listePosMouv=target.getLegalMove(state);
			
			for(size_t j=0; j<listePosMouv.size(); j++){			
				if(listePosMouv[j].equals(newPosition)){
					deplacementPossible=true;
					break;
				}			
			}
			
			if(deplacementPossible){
				
				// Deduction du bonus precedent
				Praticable& refTerrainActuel = static_cast<Praticable&>(*state.getGrid()[target.getPosition().getY()][target.getPosition().getX()]);
				
				target.getStatistics().setAttack(target.getStatistics().getAttack()-refTerrainActuel.getStatistics().getAttack());
				target.getStatistics().setDefense(target.getStatistics().getDefense()-refTerrainActuel.getStatistics().getDefense());
				target.getStatistics().setDodge(target.getStatistics().getDodge()-refTerrainActuel.getStatistics().getDodge());
				target.getStatistics().setCritical(target.getStatistics().getCritical()-refTerrainActuel.getStatistics().getCritical());
				
				// Modification de Position
				target.getPosition().setX(newPosition.getX());
				target.getPosition().setY(newPosition.getY());
				target.setMove(target.getMove()-1);
				cout << target.getName() << " moves on the coordinate box [" << newPosition.getX() << ", " << newPosition.getY() << "] avec succès !" << endl;
				cout << "\tIl lui reste " << target.getMove() << " points de deplacement." << endl;
				
				// Nouveau bonus de terrain
				Praticable& refTerrainDestination = static_cast<Praticable&>(*state.getGrid()[newPosition.getY()][newPosition.getX()]);
				
								
				if (refTerrainDestination.getTypeId() == GRASS){
					target.getStatistics().setDodge(target.getStatistics().getDodge()+refTerrainDestination.getStatistics().getDodge());
					cout << "+ Il obtient un bonus de +" ;
					cout << refTerrainDestination.getStatistics().getDodge() << " en Dodge sur cette case FORET. +" << endl;
					
				}
				else if (refTerrainDestination.getTypeId() == HILL){
					target.getStatistics().setDefense(target.getStatistics().getDefense()+refTerrainDestination.getStatistics().getDefense());
					cout << "+ He gets a bonus of +" ;
					cout << refTerrainDestination.getStatistics().getDefense() << " en DEFENSE sur cette case COLLINE. +" << endl;
				}
				
			}
			else{
				cerr << "Unauthorized removal " << endl;
			}
		}
		else {
			cout<< "Movement impossible, all points of " << target.getName() << " of movement were used for this turn." << endl;
		}
	}
	else if (target.getStatus()==WAITING){
		cout << target.getName() << " has completed all his turn of actions he can no longer move." <<endl;
	}
	
	cout << "\n" ;
}

void DepAction::undo (state::State& state){
	target.setStatus(state::AVAILABLE);
	target.getPosition().setX(oldPosition.getX());
	target.getPosition().setY(oldPosition.getY());

	target.getStatistics().setPV(oldStatistics.getPV());
	target.getStatistics().setAttack(oldStatistics.getAttack());
	target.getStatistics().setDefense(oldStatistics.getDefense());
	target.getStatistics().setCritical(oldStatistics.getCritical());
	target.getStatistics().setDodge(oldStatistics.getDodge());

	target.setMove(oldMove);
}
