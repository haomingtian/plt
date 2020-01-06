#include "DeepAI.h"
#include "engine.h"
#include "state.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "ai.h"

using namespace ai;
using namespace std;
using namespace engine;
using namespace state;

void DeepAI::run(engine::Engine& engine, sf::RenderWindow& window){
	if(engine.getActivePlayer()==camp && engine.getState().isEndAction() == false){
		//for (size_t i = 0; i < engine.getState().getUnityArmys().size(); i++){
			//if (engine.getState().getUnityArmys()[i]-> getCamp() == camp){
				//while (engine.getState().getUnityArmys()[4]->getStatut() != MORT && engine.getState().getUnityArmys()[4]->getStatut() != ATTENTE){
		chosenCamp = false;
		//int max_val=-30000;
		//int valeur;
		//std::vector<Action*> listeActions;
		
		scoreOptimal = -30000;
		
		findActionsPossibles(engine.getState(), chosenCamp, engine);
		
		for (size_t i = 0; i < listSimulateActions.size(); i++){
			listSimulateActions[listSimulateActions.size()-i-1]->undo(engine.getState());
			listSimulateActions.pop_back();
		}
		
		cout << "Preparation aux Commands de l'IA optimales..."<< endl;
		sleep(5);
		
		//cout<<"taille liste Actions :"<<listeActions.size()<<endl;
		cout<<"Taille listOptimalActions :"<<listOptimalActions.size()<<endl;
		
		for(size_t i=0; i<listOptimalActions.size(); i++){
			cout<<"ID action "<<i<<" de Coups Optimaux : " << listOptimalActions[i]->getActionID()<<endl;
			if(listOptimalActions[i]->getActionID()==DEP_ACTION){
				DepAction& listActions =static_cast<DepAction&>(*listOptimalActions[i]);
				Movement movement(listActions.getTarget(), listActions.getDestination(),listActions.getPlayer());
				unique_ptr<Command> meilleureCommand(new Movement(movement));
				engine.addCommand(i, move(meilleureCommand));
			}
			else if(listOptimalActions[i]->getActionID()==ATTACK_ACTION){
				AttackAction& listeActionsI=static_cast<AttackAction&>(*listOptimalActions[i]);
				Attack attaque(listeActionsI.getAttacker(), listeActionsI.getTarget(),listeActionsI.getPlayer());
				unique_ptr<Command> meilleureCommand (new Attack(attaque));
				engine.addCommand(i, move(meilleureCommand));
			}
			else if(listOptimalActions[i]->getActionID()==FIN_ACTION){
				FinAction& listActions = static_cast<FinAction&>(*listOptimalActions[i]);
				EndAction endAction(listActions.getTarget(),listActions.getPlayer());
				unique_ptr<Command> meilleureCommand (new EndAction(endAction));
				engine.addCommand(i, move(meilleureCommand));
			}
		}
		engine.update(window);
		sleep(5);
		/*
		for(size_t i=0; i<listeActions.size(); i++){
			
			listeActions[i]->apply(engine.getState());	
			
			valeur = min(engine, profondeur-1);
			if(valeur > max_val){
				max_val= valeur;
				if(listeActions[i]->getActionID()==DepAction){
					DepAction& listeActionsI=static_cast<DepAction&>(*listeActions[i]);
					Deplacement deplacement(listeActionsI.getCible(), listeActionsI.getDestination(),listeActionsI.getJoueur());
					unique_ptr<Command> meilleureCommand(new Deplacement(deplacement));
					engine.addCommand(0, move(meilleureCommand));
				}
				else if(listeActions[i]->getActionID()==ATTAQUE_ACTION){
					Attaque_Action& listeActionsI=static_cast<Attaque_Action&>(*listeActions[i]);
					Attaque attaque(listeActionsI.gstatetaquant(), listeActionsI.getCible(),listeActionsI.getJoueur());
					unique_ptr<Command> meilleureCommand (new Attaque(attaque));
					engine.addCommand(0, move(meilleureCommand));
				}
				else if(listeActions[i]->getActionID()==FINACTIONS_ACTION){
					FinActions_Action& listeActionsI=static_cast<FinActions_Action&>(*listeActions[i]);
					FinActions finactions(listeActionsI.getCible(),listeActionsI.getJoueur());
					unique_ptr<Command> meilleureCommand (new FinActions(finactions));
					engine.addCommand(0, move(meilleureCommand));
				}
				
			}
			listeActions[i]->undo(engine.getState());	
		}*/
		
		//engine.update(window);
	//}
	}
}

int DeepAI::functionEvaluation(engine::Engine &engine) {
	int valeur_retour;
	if(engine.getState().isEndAction()){
		if(!engine.getActivePlayer()){
			valeur_retour=1000-engine.getState().getRound();
		}
		else{
			valeur_retour=-1000+engine.getState().getRound();
		}
	}
	else{
		int sommePV=0, sommePVAdverse=0, nbPersoVivant=0, nbPersoVivantAd=0;
		Position pos_mort(-1,-1);
		for(size_t i=0; i<engine.getState().getUnityArmys().size(); i++){
			if(!engine.getState().getUnityArmys()[i]->getPosition().equals(pos_mort)){
				if(engine.getState().getUnityArmys()[i]->getCamp()){
					sommePVAdverse+=engine.getState().getUnityArmys()[i]->getStatistics().getPV();
					nbPersoVivantAd+=1;
				}
				else{
					sommePV+=engine.getState().getUnityArmys()[i]->getStatistics().getPV();
					nbPersoVivant+=1;
				}
			}
		}
		valeur_retour=sommePV-sommePVAdverse+200*nbPersoVivant-200*nbPersoVivantAd;
		cout<<"valeur fonction eval :" << valeur_retour<<endl;
	}
	return valeur_retour;
}

int DeepAI::min(engine::Engine& engine, int profondeur){
	cout<<"entree min - profondeur : "<<profondeur << endl; 
	int minValue = 30000;
	if (profondeur == 0 || engine.getState().isEndAction()==true){
		return functionEvaluation(engine);
	}
	else{
		
		//cout<<"camp choisi : " << campChoisi<<endl;
		chosenCamp=!chosenCamp;
		//std::vector<engine::Action*> listeActions = findActionsPossibles(engine.getState(), campChoisi, engine);
		std::vector<engine::Action*> listeActions;
		cout<<"taille : " <<listeActions.size()<<endl;
		//cout<<"camp choisi : " << campChoisi<<endl;
		int valeur; 
		for(size_t i=0; i<listeActions.size(); i++){
			cout<<"ID action "<<i<<" : " << listeActions[i]->getActionID()<<endl;
			listeActions[i]->apply(engine.getState());
			valeur = max(engine, profondeur-1);
			if(valeur < minValue){
				minValue = valeur;
			}
			listeActions[i]->undo(engine.getState());	
		}
	}
	return minValue;
}


int DeepAI::max(engine::Engine& engine, int profondeur){
	cout<<"entree fonction max - profondeur : "<<profondeur<<endl; 
	sleep(1);
	int maxValue = -30000;
	sleep(1);
	if (profondeur == 0 || engine.getState().isEndAction()==true){
		return functionEvaluation(engine);
	}
	else{
		chosenCamp=!chosenCamp;
		//std::vector<engine::Action*> listeActions = findActionsPossibles(engine.getState(), campChoisi, engine);
		std::vector<engine::Action*> listeActions;
		cout<<"taille : " <<listeActions.size()<<endl;
		int valeur;
		for(size_t i=0; i<listeActions.size(); i++){
			cout<<"ID action "<<i<<" : " << listeActions[i]->getActionID()<<endl;
			listeActions[i]->apply(engine.getState());	
			valeur = min(engine, profondeur-1);
			if(valeur > maxValue){
				maxValue = valeur;
			}
			listeActions[i]->undo(engine.getState());		
		}
	}
	return maxValue;
}

void DeepAI::findActionsPossibles(state::State& state, bool inChosenCamp, engine::Engine& engine){
	
	std::vector<engine::Action*> listeActions;
	std::vector<state::Position> listeAttaques;
	std::vector<state::Position> listePositions;
	// Test "1v1" : Archer bleu contre guerrier rouge
	int indicePersonnage = 7;
	if (inChosenCamp == true){indicePersonnage = 0;}
	
	//for (size_t indicePersonnage = 0; indicePersonnage < state.getUnityArmys().size(); indicePersonnage++){
		// Parcours des personnages du camp choisi (false=IA)
		if(state.getUnityArmys()[indicePersonnage]->getCamp() == inChosenCamp && state.getUnityArmys()[indicePersonnage]->getStatus()!= state::DEAD && state.getUnityArmys()[indicePersonnage]->getStatus()!= state::WAITING){
			// Ajout des attaques possibles
			listeAttaques = state.getUnityArmys()[indicePersonnage]->getLegalAttack(state);
			for (size_t i = 0; i < listeAttaques.size(); i++){
				engine::AttackAction attackPossible(*state.getUnityArmys()[indicePersonnage], *state.getUnityArmys()[state.getGrid()[listeAttaques[i].getX()][listeAttaques[i].getY()]->isOccupated(state)], state.getUnityArmys()[indicePersonnage]->getCamp());
				Action* ptr_attaque_action = new AttackAction(attackPossible);
				listeActions.push_back(ptr_attaque_action);
			}
			
			// Ajout des déplacements possibles
			vector<Position> objectif = findObjectif(engine, indicePersonnage);
			vector<Position> chemin=Algorithm(engine, indicePersonnage, objectif[0]);
			if(state.getUnityArmys()[indicePersonnage]->getMove()!=0){
				//listePositions = state.getUnityArmys()[indicePersonnage]->getLegalMove(state);
				//for (size_t i = 0; i < listePositions.size(); i++){
				engine::DepAction deplacementPossible(*state.getUnityArmys()[indicePersonnage], chemin[chemin.size()-1], state.getUnityArmys()[indicePersonnage]->getCamp());
				Action* ptr_DepAction = new DepAction(deplacementPossible);
				listeActions.push_back(ptr_DepAction);
				//}
			}
			else{
			
				// Ajout de la fin du tour d'actions
				engine::FinAction finAction(*state.getUnityArmys()[indicePersonnage], state.getUnityArmys()[indicePersonnage]->getCamp());
				Action* ptr_fin_action = new FinAction(finAction);
				listeActions.push_back(ptr_fin_action);	
			}
			
			cout << "Nombre d'actions possibles : " <<listeActions.size() << endl;
			
			// SIMULATIONS
			for(size_t i = 0; i < listeActions.size(); i++){
				listeActions[i]->apply(state);
				
				if (inChosenCamp == false){
					listSimulateActions.push_back(move(listeActions[i]));
					cout << "Coup effectue par l'IA : " << listSimulateActions.size() << endl;
				}
				else{
					nbSimulatePlayerActions++;
					listSimulateActions.push_back(move(listeActions[i]));
				}
				findActionsPossibles(state, chosenCamp, engine);
			}
		}
		
		// Le perso est en attente
		else{
			// Si c'est le tour de l'IA est fini on simule le tour du joueur
			if(inChosenCamp == false){
                chosenCamp = true;
				state.getUnityArmys()[indicePersonnage]->setStatus(state::AVAILABLE);
				cout << "XX changement de joueur simule XX : " << chosenCamp << endl;
				findActionsPossibles(state, chosenCamp, engine);
			}
			// Si c'est le tour du joueur est terminé
			else{
				int newScore = functionEvaluation(engine);
				if (newScore > scoreOptimal){
					scoreOptimal = newScore;
					cout << "changement de score !! : "<< scoreOptimal << endl;
					cout << "Le joueur a simulé ce nombre d'actions : " << nbSimulatePlayerActions << endl;
					listOptimalActions = listSimulateActions;
					for (int j = 0; j <= nbSimulatePlayerActions-1; j++){
						listOptimalActions.pop_back();
					}
					
					cout << "Taille coup optimaux :" << listOptimalActions.size() << endl;
					sleep(4);
				}
				
				cout << "Taille avant annulations : " << listSimulateActions.size() << endl;
				// On annule les coups du joueurs
				/*for(size_t j = 0; j<=nbActionsJoueurSimulees-1; j++){
					cout << "Coup annulé" << endl;
					listSimulateActions[listSimulateActions.size()-1]->undo(state);
					listSimulateActions.pop_back();
				}*/
                nbSimulatePlayerActions--;
				
				// On annule le dernier coup de l'IA
				listSimulateActions[listSimulateActions.size()-1]->undo(state);
				listSimulateActions.pop_back();
				
				// Si il n'y a pas eu de nouveau coup
				if(nbSimulatePlayerActions == 0){
					listSimulateActions[listSimulateActions.size()-1]->undo(state);
					listSimulateActions.pop_back();
				}
				
				cout << "Taille après annulations joueur: " << listSimulateActions.size() << endl;
				chosenCamp = false;
			}
		}
	//}
	//return listeActions;
}

vector<Position> DeepAI::Algorithm(engine::Engine& engine, int i, state::Position posDestination){
	vector<Position> chemin;
	bool chgtCible=false;
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
		if(posnextCible.size()!=0){
			vector<int> dist;
			for(size_t j=0; j<posnextCible.size(); j++){
				dist.push_back(posnextCible[j].distance(posSource));
			}
			posDestination=posnextCible[minimumIndex(dist)];
		}
		else{// cible non accessible
			chgtCible=true;
		}
	}
	if(chgtCible){
		return chemin;
	}
	else{
	
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
		indiceMin=minimumIndex(listeCout);

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
}

	
int DeepAI::isPresentSommet(vector<Sommet> listeSommet, Sommet sommet){
	int isPresent=-1;
	for(size_t i=0; i<listeSommet.size(); i++){
		if(listeSommet[i].getPosition().equals(sommet.getPosition())){
			isPresent=i;
			break;
		}
	}
	return isPresent;
}

int DeepAI::isPresentPos(vector<Sommet> listeSommet, state::Position position){
	int isPresent=-1;
	for(size_t i=0; i<listeSommet.size(); i++){
		if(listeSommet[i].getPosition().equals(position)){
			isPresent=i;
			break;
		}
	}
	return isPresent;
}

int DeepAI::minimumIndex(std::vector<int> indices) {
	int indiceMin=-1;
	if(indices.size()!=0){//liste non vide
		indiceMin=0;
		int min=indices[0];
		for(size_t i=1; i<indices.size(); i++){
			if(indices[i]<min){
				min=indices[i];
				indiceMin=i;
			}
		}
	}
	return indiceMin;
}

int DeepAI::findNeighborIndex(engine::Engine &engine, int character) {
	
	vector<int> listeDistance;
	vector<int> indicePerso;
	int indiceMinDistance;
	int indiceVoisin;
	for(size_t i=0; i<engine.getState().getUnityArmys().size(); i++){
		if(engine.getState().getUnityArmys()[i]->getCamp()!=engine.getState().getUnityArmys()[character]->getCamp() &&engine.getState().getUnityArmys()[i]->getStatus()!=DEAD){
			listeDistance.push_back(engine.getState().getUnityArmys()[character]->getPosition().distance(engine.getState().getUnityArmys()[i]->getPosition()));
			indicePerso.push_back(i);
		}
	}
	if(listeDistance.size()!=0){
		indiceMinDistance=this->minimumIndex(listeDistance);
		indiceVoisin= indicePerso[indiceMinDistance];
	}
	else{
		indiceVoisin=-1;
	}
	return indiceVoisin;
}

int DeepAI::maximumIndex(std::vector<int> indices) {
	int indiceMax=-1;
	if(indices.size()!=0){//liste non vide
		indiceMax=0;
		int max=indices[0];
		for(size_t i=1; i<indices.size(); i++){
			if(indices[i]>max){
				max=indices[i];
				indiceMax=i;
			}
		}
	}
	return indiceMax;
}

vector<Position> DeepAI::findRefuge(engine::Engine& engine, int personnage){
	Position positionRefuge;
	std::vector<Position> listeRefuges, listeRefugesClasses;
	std::vector<int> listeDistances;
	for(size_t j = 0; j<engine.getState().getGrid().size(); j++){
		for(size_t i = 0; i<engine.getState().getGrid()[0].size(); i++){
			// Recherche des refuges (maisons ou forteresses) non occupées
			if ((engine.getState().getGrid()[i][j]->getName() == "Maison" || engine.getState().getGrid()[i][j]->getName() == "Forteresse") && engine.getState().getGrid()[i][j]->isOccupated(engine.getState()) == -1){
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
			listeRefugesClasses.push_back(listeRefuges[minimumIndex(listeDistances)]);
			listeDistancesProv=listeDistances[minimumIndex(listeDistances)];
			listeDistances[minimumIndex(listeDistances)]=listeDistances.back();
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

std::vector<state::Position> DeepAI::findObjectif(engine::Engine& engine, int indicePerso){
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
	vector<Position> listePosition;		
	int indiceMaxScore, indiceCible;
			
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
			
			listeScores.push_back(score);
			listeIndice.push_back(i);
		}
	}
	int listeScoresProv, listeIndiceProv;
	while(listeScores.size()!=0){	
	//On veut attaquer la cible la plus faible									
		indiceMaxScore=maximumIndex(listeScores);
		indiceCible=listeIndice[indiceMaxScore];
		listePosition.push_back(engine.getState().getUnityArmys()[indiceCible]->getPosition());	

		listeScoresProv=listeScores[indiceMaxScore];
		listeIndiceProv=listeIndice[indiceMaxScore];
		listeScores[indiceMaxScore]=listeScores.back();
		listeIndice[indiceMaxScore]=listeIndice.back();
		listeScores.back()=listeScoresProv;
		listeIndice.back()=listeIndiceProv;
		listeScores.pop_back();
		listeIndice.pop_back();
	}
		
	return listePosition;
}


