#include "engine.h"
#include "state.h"

#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Movement::Movement(state::UnityArmy& target, state::Position& destination, bool newPlayer):target(target), destination(destination){
	id = MOVEMENT;
	player = newPlayer;
}

void Movement::execute (state::State& state){

	bool MovementPossible=false;
	if (target.getStatus()!=WAITING && target.getStatus()!=DEAD){

		if(target.getMove()!=0){
			vector<Position> listePosMouv=target.getLegalMove(state);

			for(size_t j=0; j<listePosMouv.size(); j++){
				if(listePosMouv[j].equals(destination)){
					MovementPossible=true;
					break;
				}
			}

			if(MovementPossible){

				// Deduction du bonus precedent
				Praticable& refTerrainActuel = static_cast<Praticable&>(*state.getGrid()[target.getPosition().getY()][target.getPosition().getX()]);

				target.getStatistics().setAttack(target.getStatistics().getAttack()-refTerrainActuel.getStatistics().getAttack());
				target.getStatistics().setDefense(target.getStatistics().getDefense()-refTerrainActuel.getStatistics().getDefense());
				target.getStatistics().setDodge(target.getStatistics().getDodge()-refTerrainActuel.getStatistics().getDodge());
				target.getStatistics().setCritical(target.getStatistics().getCritical()-refTerrainActuel.getStatistics().getCritical());

				// Modification de Position
				target.getPosition().setX(destination.getX());
				target.getPosition().setY(destination.getY());
				target.setMove(target.getMove()-1);
				cout << target.getName() << " moves on the coordinate box [" << destination.getX() << ", " << destination.getY() << "] with success !" << endl;
				cout << "\t\nHe still has " << target.getMove() << " Movement points." << endl;

				// Nouveau bonus de terrain
				Praticable& refTerrainDestination = static_cast<Praticable&>(*state.getGrid()[destination.getY()][destination.getX()]);


				if (refTerrainDestination.getTypeId() == LAND){
					target.getStatistics().setDodge(target.getStatistics().getDodge()+refTerrainDestination.getStatistics().getDodge());
					cout << "+ He gets a bonus of +" ;
					cout << refTerrainDestination.getStatistics().getDodge() << " in ESQUIVE on this box FORET. +" << endl;

				}
				else if (refTerrainDestination.getTypeId() == HILL){
					target.getStatistics().setDefense(target.getStatistics().getDefense()+refTerrainDestination.getStatistics().getDefense());
					cout << "+ He gets a bonus of +" ;
					cout << refTerrainDestination.getStatistics().getDefense() << " in DEFENSE on this box COLLINE. +" << endl;
				}

			}
			else{
				cerr << "Movement not allowed. " << endl;
			}
		}
		else {
			cout<< "Movement impossible, all movement points were used for this turn." << endl;
		}
	}
	else if (target.getStatus()==WAITING){
		cout << target.getName() << " has completed all his turn of actions he can no longer move." <<endl;
	}
	
	cout << "\n" ;
}
