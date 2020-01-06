#include "ai.h"
#include "engine.h"
#include "state.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;


void RandomAI::run (engine::Engine& engine, sf::RenderWindow& window){
	// L'IA effectue ces actions uniquement si c'est son tour
	if(engine.getActivePlayer()==false){
		int randomAction;
		int randomPosition;
		int randomAttack;
		bool firstTry = true;
		bool movementImpossible = false;
		bool attackImpossible = false;
			
		for (unsigned int i = 0; i < engine.getState().getUnityArmys().size(); i++ ){
			// Reinitialisations de changement de personnage
            movementImpossible = false;
            attackImpossible = false;
            firstTry = true;
			
			// Controle des personnages de l'IA (camp = false)
			if (engine.getState().getUnityArmys()[i]-> getCamp() == camp){
				while (engine.getState().getUnityArmys()[i]->getStatus() != DEAD && engine.getState().getUnityArmys()[i]->getStatus() != WAITING){
					if(firstTry == true){
						cout<< "\t\t-> Début du tour de " << engine.getState().getUnityArmys()[i]->getName() << " <-" << endl;
						firstTry = false;
					}
					
					engine.getState().getUnityArmys()[i]->setStatus(SELECTED);
										
					/* 	Action random entre 3 choix : deplacement (0), attaque(1), finActions(2)
						Si le personnage vient de tenter une action et qu'elle fut impossible, 
						on élimine ce choix pour qu'il ne la retente pas tant que cela reste impossible.
					*/
					srand(time(NULL));
					if (movementImpossible == true && attackImpossible == true){
						randomAction = 2;
					}
					else if (movementImpossible == true && attackImpossible == false){
						randomAction = rand()%2+1 ;
					}
					else if (movementImpossible == false && attackImpossible == true){
						randomAction = rand()%2;
						if(randomAction == 1){
							randomAction = 2;
						}
					}
					else{randomAction = rand()%3;}
														
					// 0 : Cas du deplacement
					if (randomAction == 0 && engine.getState().getUnityArmys()[i]->getMove() != 0){
						std::vector<Position> listePositions = engine.getState().getUnityArmys()[i]-> getLegalMove(engine.getState());
						if (listePositions.size() != 0){
							srand(time(NULL));
							randomPosition = rand()%listePositions.size();
							
							// Commande de deplacement
							Movement movement(*engine.getState().getUnityArmys()[i], listePositions[randomPosition], camp);
							unique_ptr<Command> ptr_movement (new Movement(movement));
							engine.addCommand(0, move(ptr_movement));
							engine.update(window);
							attackImpossible = false;
							sleep(1);
						}
						else{movementImpossible = true;}
					}
					
					// 1 : Cas de l'attaque
					else if (randomAction == 1){
						std::vector<Position> listAttacks = engine.getState().getUnityArmys()[i]-> getLegalAttack(engine.getState());

						if (listAttacks.size() !=0){
							srand(time(NULL));
							randomAttack = rand()%listAttacks.size();
												
							// On recupere l'indice de la cible dans la liste des personnages
							int indiceCible = engine.getState().getGrid()[listAttacks[randomAttack].getX()][listAttacks[randomAttack].getY()]->isOccupated(engine.getState());
							if (indiceCible != -1){
								// Commande d'attaque
								Attack attack(*engine.getState().getUnityArmys()[i], *engine.getState().getUnityArmys()[indiceCible], camp);
								unique_ptr<Command> ptr_attack (new Attack(attack));
								engine.addCommand(0, move(ptr_attack));
                                engine.update(window);
								movementImpossible = false;
								sleep(1);
							}
						}
						else{attackImpossible = true;}
					}
					
					// 2 : Cas de fin d'actions
					else if (randomAction == 2){
						EndAction endAction(*engine.getState().getUnityArmys()[i], camp);
						unique_ptr<Command> ptr_endAction (new EndAction(endAction));
						engine.addCommand(0, move(ptr_endAction));
						engine.update(window);
						sleep(1);
					}
				}		
			}
		}
	}
}
