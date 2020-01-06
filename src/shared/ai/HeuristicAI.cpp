#include "HeuristicAI.h"
#include "engine.h"
#include "state.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "ai.h"

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;


/** Pseudo Code de l'algorithme de recherche de chemin
Initialisation
Sommet source (S)
Sommet destination (D)
Liste des sommets à explorer (E) : sommet source S
Liste des sommets visités (V) : vide

Tant que (la liste E est non vide) et (D n’est pas dans E) Faire
	+ Récupérer le sommet X de coût total F minimum.
	+ Ajouter X à la liste V
	+ Ajouter les successeurs de X (non déjà visités) à la liste E en
   évaluant leur coût total F et en identifiant leur prédécesseur.

	+ Si (un successeur est déjà présent dans E) et
         (nouveau coût est inférieur à l’ancien) Alors
		Changer son coût total
		Changer son prédécesseur
	FinSi
FinFaire*/

void HeuristicAI::run (engine::Engine& engine, sf::RenderWindow& window){

		if(engine.getActivePlayer()==camp && engine.getState().isEndAction() == false){
		
		bool armeeAdverseAneantie = true;
			
		for (size_t i = 0; i < engine.getState().getUnityArmys().size(); i++){
			int action=-1;
			
			if (engine.getState().getUnityArmys()[i]-> getCamp() == camp){
                size_t indiceObjectif=0;
				while (engine.getState().getUnityArmys()[i]->getStatus() != DEAD && engine.getState().getUnityArmys()[i]->getStatus() != WAITING){
					
					engine.getState().getUnityArmys()[i]->setStatus(SELECTED);
                    vector<Position>  objectif;
					vector<Position> listeAttaques = engine.getState().getUnityArmys()[i]-> getLegalAttack(engine.getState());
					armeeAdverseAneantie = true;
					
					// We check that there are still targets
					for (size_t l = 0; l < engine.getState().getUnityArmys().size(); l++){
						if (engine.getState().getUnityArmys()[l]->getCamp() != camp && engine.getState().getUnityArmys()[l]->getStatus() != DEAD){
							armeeAdverseAneantie = false;
							break;
						}
					}
					
					// If the enemy targets are all dead, the character ends his turn to trigger
					// the end of the game
					if (armeeAdverseAneantie){
						action = 2;
					}
					
					// If there are opponents
					else{
						// If the character has less than 5 VP and if he is on a refuge, he ends his turn
						if(engine.getState().getUnityArmys()[i]->getStatistics().getPV()<=5 && (engine.getState().getGrid()[engine.getState().getUnityArmys()[i]->getPosition().getX()][engine.getState().getUnityArmys()[i]->getPosition().getY()]->getName() == "Maison" || engine.getState().getGrid()[engine.getState().getUnityArmys()[i]->getPosition().getX()][engine.getState().getUnityArmys()[i]->getPosition().getY()]->getName() == "Forteresse")){
							action = 2;
						}
						
						else{
							objectif = findObjectif(engine, i);
							// If the position of the objective is occupied, we deduce that it is an enemy
							// attaquer
							if(engine.getState().getGrid()[objectif[indiceObjectif].getX()][objectif[indiceObjectif].getY()]->isOccupated(engine.getState())!=-1){
								bool resTest = false;
								for (size_t k = 0; k < listeAttaques.size(); k++){
									if(objectif[indiceObjectif].equals(listeAttaques[k])){
										resTest = true;
										break;
									}
								}					
								
								// Si la position de l'ennemi est dans le champ d'attaque, on demande une attaque
								if (resTest){
									action = 1;
								}
							}
						}
					}
					// If the goal is to reach a refuge or to get closer to an enemy, we ask for a displacement
					if(action == -1){
						action = 0;
					}
					
					sleep(1);
					
					// 0 : Displacement case
					if (action==0){ 
						if(engine.getState().getUnityArmys()[i]->getMove() != 0){
							int neighborIndex = this->findIndiceNeighbor(engine, i);
							if(neighborIndex!=-1){

                                indiceObjectif=0;

                                vector<Position> chemin=Algorithm(engine, i, objectif[indiceObjectif]);

                                while(chemin.size()==0 && indiceObjectif!=(objectif.size()-1)){
                                    indiceObjectif++;
                                    chemin=Algorithm(engine, i, objectif[indiceObjectif]);
                                }

                                if(chemin.size()!=0){
                                    Movement movement(*engine.getState().getUnityArmys()[i], chemin[chemin.size()-1], camp);
                                    unique_ptr<Command> ptr_movement(new Movement(movement));
                                    engine.addCommand(0, move(ptr_movement));
                                    engine.update(window);
                                }
								else{
									action=2;
								}
							}
							else{action=2;}								
						}
						else{
							action=2;
						}
					}
					
					
					// 1 : Cas de l'attaque
					else if (action == 1){
							// Commande d'attaque
							Attack attaque(*engine.getState().getUnityArmys()[i], *engine.getState().getUnityArmys()[engine.getState().getGrid()[objectif[indiceObjectif].getX()][objectif[indiceObjectif].getY()]->isOccupated(engine.getState())], camp);
							unique_ptr<Command> ptr_attaque (new Attack(attaque));
							engine.addCommand(0, move(ptr_attaque));
							engine.update(window);
							sleep(1);
						}
					
					// 2 : Cas de fin d'actions
					else if (action == 2){
						EndAction finactions(*engine.getState().getUnityArmys()[i], camp);
						unique_ptr<Command> ptr_finactions (new EndAction(finactions));
						engine.addCommand(0, move(ptr_finactions));
						engine.update(window);
						usleep(200000);
					}
					
				}		
			}
		}
	}
}

void HeuristicAI::runRollback (engine::Engine& engine, sf::RenderWindow& window){

    if(engine.getActivePlayer()==camp && engine.getState().isEndAction() == false){

        bool armeeAdverseAneantie = true;

        for (size_t i = 0; i < engine.getState().getUnityArmys().size(); i++){
            int action=-1;

            if (engine.getState().getUnityArmys()[i]-> getCamp() == camp){
                size_t indiceObjectif=0;
                while (engine.getState().getUnityArmys()[i]->getStatus() != DEAD && engine.getState().getUnityArmys()[i]->getStatus() != WAITING){
                    engine.getState().getUnityArmys()[i]->setStatus(SELECTED);
                    vector<Position> objectif;
                    vector<Position> listeAttaques = engine.getState().getUnityArmys()[i]-> getLegalAttack(engine.getState());
                    armeeAdverseAneantie = true;

                    // On vérifie qu'il reste des cibles
                    for (size_t l = 0; l < engine.getState().getUnityArmys().size(); l++){
                        if (engine.getState().getUnityArmys()[l]->getCamp() != camp && engine.getState().getUnityArmys()[l]->getStatus() != DEAD){
                            armeeAdverseAneantie = false;
                            break;
                        }
                    }

                    // Si les cibles adverses sont toutes mortes, le personnage termine son tour pour déclencher
                    // la fin de partie
                    if (armeeAdverseAneantie){
                        action = 2;
                    }

                    // If there are opponents
                    else{
                        // If the character has less than 5 VP and if he is on a refuge, he ends his turn
                        if(engine.getState().getUnityArmys()[i]->getStatistics().getPV()<=5 && (engine.getState().getGrid()[engine.getState().getUnityArmys()[i]->getPosition().getX()][engine.getState().getUnityArmys()[i]->getPosition().getY()]->getName() == "Maison" || engine.getState().getGrid()[engine.getState().getUnityArmys()[i]->getPosition().getX()][engine.getState().getUnityArmys()[i]->getPosition().getY()]->getName() == "Forteresse")){
                            action = 2;
                        }
                        else{
                            objectif = findObjectif(engine, i);
                            // If the position of the objective is occupied, we deduce that it is an enemy
                            // attaquer
                            if(engine.getState().getGrid()[objectif[indiceObjectif].getX()][objectif[indiceObjectif].getY()]->isOccupated(engine.getState())!=-1){

                                bool resTest = false;
                                for (size_t k = 0; k < listeAttaques.size(); k++){
                                    if(objectif[indiceObjectif].equals(listeAttaques[k])){
                                        resTest = true;
                                        break;
                                    }
                                }

                                // Si la position de l'ennemi est dans le champ d'attaque, on demande une attaque
                                if (resTest){
                                    action = 1;
                                }
                            }
                        }
                    }
                    // Si l'objectif est d'atteindre un refuge ou de se rapprocher d'un ennemi, on demande un 							deplacement
                    if(action == -1){
                        action = 0;
                    }

                    sleep(1);

                    // 0 : Cas du deplacement
                    if (action==0){
                        if(engine.getState().getUnityArmys()[i]->getMove() != 0){
                            int indiceVoisin=this->findIndiceNeighbor(engine, i);
                            if(indiceVoisin!=-1){

                                indiceObjectif=0;

                                vector<Position> chemin=Algorithm(engine, i, objectif[indiceObjectif]);
                                while(chemin.size()==0 && indiceObjectif!=(objectif.size()-1)){
                                    indiceObjectif++;
                                    chemin=Algorithm(engine, i, objectif[indiceObjectif]);
                                }
                                if(chemin.size()!=0){
                                    DepAction deplacement(*engine.getState().getUnityArmys()[i], chemin[chemin.size()-1], camp);
                                    DepAction* ptr_deplacement (new DepAction(deplacement));
                                    engine.addAction(move(ptr_deplacement));
                                    engine.updateAction(window, move(ptr_deplacement));
                                    engine.update(window);
                                }
                                else{
                                    action=2;
                                }
                            }
                            else{action=2;}
                        }
                        else{
                            action=2;
                        }
                    }

                        // 1 : Cas de l'attaque
                    else if (action == 1){
                        // Commande d'attaque
                        AttackAction attaque(*engine.getState().getUnityArmys()[i], *engine.getState().getUnityArmys()[engine.getState().getGrid()[objectif[indiceObjectif].getX()][objectif[indiceObjectif].getY()]->isOccupated(engine.getState())], camp);
                        AttackAction* ptr_attaque (new AttackAction(attaque));
                        engine.addAction(move(ptr_attaque));
                        engine.updateAction(window, move(ptr_attaque));
                        engine.update(window);
                        sleep(1);
                    }

                        // 2 : Cas de fin d'actions
                    else if (action == 2){
                        FinAction finactions(*engine.getState().getUnityArmys()[i], camp);
                        FinAction* ptr_finactions (new FinAction(finactions));
                        engine.addAction(move(ptr_finactions));
                        engine.updateAction(window, move(ptr_finactions));
                        engine.update(window);
                        usleep(200000);
                    }

                }
            }
        }
    }
}

vector<Position> HeuristicAI::Algorithm(engine::Engine& engine, int i, state::Position posDestination){
	int isPresentV=-1;
	int isPresentPos2=-1;
	Position posSource=engine.getState().getUnityArmys()[i]->getPosition();
	Sommet *old, *old2, *old3, *old4;
	Sommet source(nullptr);
	source.setPosition(posSource);
	source.setDistanceSource(0);
	
	int indiceOccupe=engine.getState().getGrid()[posDestination.getX()][posDestination.getY()]->isOccupated(engine.getState());
	if(indiceOccupe!=-1){
		vector<Position> posnextCible=engine.getState().getUnityArmys()[indiceOccupe]->getLegalMove(engine.getState());
		vector<int> dist;
		for(size_t j=0; j<posnextCible.size(); j++){
			dist.push_back(posnextCible[j].distance(posSource));
		}
		posDestination=posnextCible[indiceMinimum(dist)];
	}

	int indiceMin=-1;
	
	size_t tailleV=0;
	size_t tailleE=1;
	Sommet destination(0);
	Sommet* V2=new Sommet[tailleV];
	
	vector<int> listeCout;
	Sommet* E2=new Sommet[tailleE];
	E2[0]=source;
	Position positionAjoutee(0, 0);
	
	int isPresentPos=-1;
	
	//Tant que la liste E est non vide et D n’est pas dans E
	while(tailleE!=0 && isPresentPos==-1){
	
		if(listeCout.size()!=0){
			while(listeCout.size()!=0){
				listeCout.pop_back();
			}
		}

		for(size_t i=0; i<tailleE; i++){
			if(!E2[i].getPredecesseur()){
				// Distance du sommet X à Source
				E2[i].setDistanceSource(E2[i].getPosition().distance(source.getPosition()));
			}
			else{
				// Distance du sommet X à Source
				E2[i].setDistanceSource(1+E2[i].getPredecesseur()->getDistanceSource());			
			}
			
			// Distance du sommet X à Destination
			E2[i].setDistanceDestination(E2[i].getPosition().distance(posDestination));	

			if(E2[i].getCoutTotal()>0){
				listeCout.push_back(E2[i].getCoutTotal());
			}	
		}
		
		// Récupérer le sommet X d'indice indiceMin de coût total minimum
		indiceMin=indiceMinimum(listeCout);

		old=V2;
		tailleV=tailleV+1;
		V2=new Sommet[tailleV];
		
		for(size_t t=0; t<tailleV-1; t++){
			V2[t]=old[t];
		}
		
		// Ajouter X à la liste V (sommets visités)
		V2[tailleV-1]=E2[indiceMin];
				
		//Retirer X à la liste E
		old2=E2;
		tailleE=tailleE-1; 
		E2=new Sommet[tailleE];
		size_t indice=indiceMin;
		for(size_t t=0; t<indice; t++){
				E2[t]=old2[t];		
		}
		for(size_t m=indice; m<tailleE; m++){
				E2[m]=old2[m+1];		
		}
		
		// On parcourt les abscisses puis les ordonnees de la grille
		for(int abscisse = V2[tailleV-1].getPosition().getX() - 1; abscisse <=  V2[tailleV-1].getPosition().getX() + 1; abscisse++){
			for(int ordonnee =  V2[tailleV-1].getPosition().getY() - 1; ordonnee <=  V2[tailleV-1].getPosition().getY() + 1; ordonnee++){
				// On teste les cases autour de la position			
				if(abs(abscisse- V2[tailleV-1].getPosition().getX())+abs(ordonnee- V2[tailleV-1].getPosition().getY())<=1 && abscisse>=0 && ordonnee>=0 && 	abs(abscisse)<engine.getState().getGrid().size() && abs(ordonnee)<engine.getState().getGrid()[abscisse].size()){
					if(engine.getState().getGrid()[abscisse][ordonnee]->isPraticable()){
						if(engine.getState().getGrid()[abscisse][ordonnee]->isOccupated(engine.getState())==-1){
							positionAjoutee.setX(abscisse);
							positionAjoutee.setY(ordonnee);
							if(!positionAjoutee.equals(V2[tailleV-1].getPosition())){
								Sommet voisin(&V2[tailleV-1]);
								voisin.setPosition(positionAjoutee);
								isPresentV=-1;
								for(size_t q=0; q<tailleV; q++){
									if(V2[q].getPosition().equals(positionAjoutee)){
										isPresentV=q;
									}
								}

								isPresentPos2=-1;
								for(size_t q=0; q<tailleE; q++){
									if(E2[q].getPosition().equals(positionAjoutee)){
										isPresentPos2=q;
										
									}
								}

								if(isPresentV==-1 && isPresentPos2==-1){
									if(posDestination.equals(positionAjoutee)){
										destination=voisin;
									}

									old3=E2;

									tailleE=tailleE+1;
									E2=new Sommet[tailleE];
									for(size_t t=0; t<tailleE-1; t++){
										E2[t]=old3[t];
									}
									
									E2[tailleE-1]=voisin;				
								}
								// Si un successeur est déjà présent dans E
								else if(isPresentPos2!=-1){
									// Distance du sommet X à Source
									voisin.setDistanceSource(1+voisin.getPredecesseur()->getDistanceSource());
									// Distance du sommet X à Destination
voisin.setDistanceDestination(voisin.getPosition().distance(posDestination));
	
									// Si nouveau coût est inférieur à l’ancien
									if(voisin.getCoutTotal()<E2[isPresentPos2].getCoutTotal()){
										old4=E2;
										size_t indice2=isPresentPos2;
										for(size_t t=0; t<indice2; t++){
												E2[t]=old4[t];		
										}
										
										E2[indice2]=voisin;
										for(size_t t=indice2+1; t<tailleE; t++){
												E2[t]=old4[t];		
										}
									}									
								}
							}					
						}
					}
				}
			}
		}
	}
	
	delete[] E2;
	delete[] V2;
	Sommet* finger=&destination;
	vector<Position> chemin;
	chemin.push_back(finger->getPosition());

	if(finger->getPredecesseur()){
		while(finger->getPredecesseur() && !finger->getPredecesseur()->getPosition().equals(source.getPosition())){			
			finger=finger->getPredecesseur();
			chemin.push_back(finger->getPosition());
		}
	}
	
	else{
		chemin.pop_back();
	}
	
	return chemin;
}

	
int HeuristicAI::isPresentSom(vector<Sommet> listeSommet, Sommet sommet){
	int isPresent=-1;
	for(size_t i=0; i<listeSommet.size(); i++){
		if(listeSommet[i].getPosition().equals(sommet.getPosition())){
			isPresent=i;
			break;
		}
	}
	return isPresent;
}

int HeuristicAI::isPresentPos(vector<Sommet> listeSommet, state::Position position){
	int isPresent=-1;
	for(size_t i=0; i<listeSommet.size(); i++){
		if(listeSommet[i].getPosition().equals(position)){
			isPresent=i;
			break;
		}
	}
	return isPresent;
}

int HeuristicAI::indiceMinimum(std::vector<int> liste){
	int indiceMin=-1;
	if(liste.size()!=0){//liste non vide
		indiceMin=0;
		int min=liste[0];
		for(size_t i=1; i<liste.size(); i++){
			if(liste[i]<min){
				min=liste[i];
				indiceMin=i;
			}
		}
	}
	return indiceMin;
}

int HeuristicAI::findIndiceNeighbor(engine::Engine& engine, int personnage){
	
	vector<int> listeDistance;
	vector<int> indicePerso;
	int indiceMinDistance;
	int indiceVoisin;
	for(size_t i=0; i<engine.getState().getUnityArmys().size(); i++){
		if(engine.getState().getUnityArmys()[i]->getCamp()!=engine.getState().getUnityArmys()[personnage]->getCamp() &&engine.getState().getUnityArmys()[i]->getStatus()!=DEAD){
			listeDistance.push_back(engine.getState().getUnityArmys()[personnage]->getPosition().distance(engine.getState().getUnityArmys()[i]->getPosition()));
			indicePerso.push_back(i);
		}
	}
	if(listeDistance.size()!=0){
		indiceMinDistance=this->indiceMinimum(listeDistance);
		indiceVoisin= indicePerso[indiceMinDistance];
	}
	else{
		indiceVoisin=-1;
	}
	return indiceVoisin;
}

int HeuristicAI::indiceMaximum(std::vector<int> liste){
	int indiceMax=-1;
	if(liste.size()!=0){//liste non vide
		indiceMax=0;
		int max=liste[0];
		for(size_t i=1; i<liste.size(); i++){
			if(liste[i]>max){
				max=liste[i];
				indiceMax=i;
			}
		}
	}
	return indiceMax;
}

vector<Position> HeuristicAI::findRefuge(engine::Engine& engine, int personnage){
    Position positionRefuge;
    std::vector<Position> listeRefuges, listeRefugesClasses;
    std::vector<int> listeDistances;
    for(size_t j = 0; j<engine.getState().getGrid().size(); j++){
        for(size_t i = 0; i<engine.getState().getGrid()[0].size(); i++){
            //Search for unoccupied shelters (houses or fortresses)
            if ((engine.getState().getGrid()[i][j]->getName() == "Grass" || engine.getState().getGrid()[i][j]->getName() == "Hill") && engine.getState().getGrid()[i][j]->isOccupated(engine.getState()) == -1){
                positionRefuge = engine.getState().getGrid()[i][j]->getPosition();
                listeRefuges.push_back(positionRefuge);
            }
        }
    }

    if(listeRefuges.size()!=0){
        for(size_t k = 0; k < listeRefuges.size(); k++){
            listeDistances.push_back(engine.getState().getUnityArmys()[personnage]->getPosition().distance(listeRefuges[k]));
        }
        //int minDistance=indiceMinimum(listeDistances);
        int listeDistancesProv;
        while(listeDistances.size()!=0){
            listeRefugesClasses.push_back(listeRefuges[indiceMinimum(listeDistances)]);
            listeDistancesProv=listeDistances[indiceMinimum(listeDistances)];
            listeDistances[indiceMinimum(listeDistances)]=listeDistances.back();
            listeDistances.back()=listeDistancesProv;
            listeDistances.pop_back();
        }

    }
    else{
        positionRefuge.setX(-1);
        positionRefuge.setY(-1);
        listeRefugesClasses.push_back(positionRefuge);
    }
    return listeRefugesClasses;
}

std ::vector<state::Position> HeuristicAI::findObjectif(engine::Engine& engine, int indicePerso){
	// Cas de la fuite : si un personnage possède moins de 5 PV, il cherche un refuge
    vector<Position> listeRefuges;
    if(engine.getState().getUnityArmys()[indicePerso]->getStatistics().getPV()<=5){
        listeRefuges = findRefuge(engine, indicePerso);
        if (listeRefuges[0].getX()!=-1 && listeRefuges[0].getY()!=-1){
            return listeRefuges;
        }
    }
	
	// Cas de l'attaque	
	vector<int> listePV, listeIndice, listeScores;
	int bonus_attaque=-1;
	int score = 0;
    vector<Position> listPosition;
    int maxScoreIndex, targetIndex;

	for (size_t i = 0; i < engine.getState().getUnityArmys().size(); i++){
		// Personnages adverses non morts
		if (engine.getState().getUnityArmys()[i]-> getCamp() != camp && engine.getState().getUnityArmys()[i]->getStatus() != DEAD){
			
			std:: string nomArme_attaquant = engine.getState().getUnityArmys()[indicePerso]->getArmorName();
			std:: string nomArme_cible = engine.getState().getUnityArmys()[i]->getArmorName();
			score = 0;
				
			if(nomArme_cible==nomArme_attaquant){
				bonus_attaque=0;
			}
			else if(nomArme_attaquant=="Arc" || nomArme_cible=="Arc"){
				bonus_attaque=0;
			}
			else if((nomArme_attaquant=="Hache" && nomArme_cible=="Lance")|| (nomArme_attaquant=="Lance" && nomArme_cible=="Epee") || (nomArme_attaquant=="Epee" && nomArme_cible=="Hache")){
				bonus_attaque=2*5;
			}
			else if ((nomArme_cible=="Hache" && nomArme_attaquant=="Lance")|| (nomArme_cible=="Lance" && nomArme_attaquant=="Epee") || (nomArme_cible=="Epee" && nomArme_attaquant=="Hache")){
				bonus_attaque=2*(-5);
			}
								
			// Prise en compte du taux de coup critique, de l'attaque et du bonus d'attaque
			score = score + bonus_attaque + engine.getState().getUnityArmys()[indicePerso]->getStatistics().getAttack() + engine.getState().getUnityArmys()[indicePerso]->getStatistics().getCritical();
								
			// Prise en compte de l'esquive, des PV et de la defense de l'adversaire
			score = score - (engine.getState().getUnityArmys()[i]->getStatistics().getDodge() + engine.getState().getUnityArmys()[i]->getStatistics().getDefense() + engine.getState().getUnityArmys()[i]->getStatistics().getPV());
				
			// Prise en compte de la distance à l'adversaire
			score = score - (engine.getState().getUnityArmys()[indicePerso]->getPosition().distance(engine.getState().getUnityArmys()[i]->getPosition()));
				
			//cout << nomArme_cible << " : " << score << endl;
				
			listeScores.push_back(score);
			listeIndice.push_back(i);
		}
	}

    int listeScoresProv, listeIndiceProv;
    while(listeScores.size()!=0){
        //On veut attaquer la cible la plus faible
        maxScoreIndex=indiceMaximum(listeScores);
        targetIndex=listeIndice[maxScoreIndex];
        listPosition.push_back(engine.getState().getUnityArmys()[targetIndex]->getPosition());

        listeScoresProv=listeScores[maxScoreIndex];
        listeIndiceProv=listeIndice[maxScoreIndex];
        listeScores[maxScoreIndex]=listeScores.back();
        listeIndice[maxScoreIndex]=listeIndice.back();
        listeScores.back()=listeScoresProv;
        listeIndice.back()=listeIndiceProv;
        listeScores.pop_back();
        listeIndice.pop_back();
    }

    return listPosition;
}


