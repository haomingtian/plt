#include "engine.h"
#include "state.h"
#include "render.h"
#include "../state/State.h"
#include <iostream>
#include <unistd.h>

using namespace state;
using namespace engine;
using namespace render;
using namespace std;

Engine::Engine () : currentState(){
    changeTour = false;
    activePlayer = true;
}

Engine::~Engine (){
}

state::State& Engine::getState(){
	state::State& refState=currentState;
	return refState;
}

void Engine::addCommandPassive (){
	//currentCommands.insert(std::pair<int, std::unique_ptr<Commande>> (currentCommands.size(), ptr_cmd));
}

void Engine::addCommand(int priorite, std::unique_ptr<Command> ptr_cmd){
	currentCommands[priorite]=move(ptr_cmd);
	
}

void Engine::update (sf::RenderWindow& window){
	StateEvent stateEvent(ALLCHANGED);

	map<int, std::unique_ptr<Command>>::iterator it;

	for(size_t i=0; i<currentCommands.size();i++){
		// On n'execute que les commandes du joueur dont c'est le tour
		if (currentCommands[i]->player == activePlayer){
			currentCommands[i]->execute(currentState);
			currentState.notifyObservers(stateEvent, currentState, window);
			sleep(2);
		}
	}
	for(it=currentCommands.begin(); it!=currentCommands.end(); it++){
		currentCommands.erase(it);
	}
}

bool Engine::endOfTourVerification(){
	bool tourChange = true;
	bool partieFinie = true;
	//int countJoueurActif = 0;
	
	for (unsigned int i = 0; i < currentState.getUnityArmys().size(); i++){
		// Si un personage du joueur actif n'est ni mort ni en attente, son tour n'est pas termine
		if (currentState.getUnityArmys()[i]->getCamp() == activePlayer){
			//countJoueurActif = countJoueurActif + 1;
			if (currentState.getUnityArmys()[i]->getStatus() != DEAD ){
				if (currentState.getUnityArmys()[i]->getStatus() != WAITING){
					tourChange = false;
				}
			}
			/*
			else{
				countJoueurActif = countJoueurActif - 1;
			}
			*/			
		}
		
		
		// Si tous les UnityArmys du joueur non actif ne sont pas morts, la partie n'est pas terminee
		else{
			if (currentState.getUnityArmys()[i]->getStatus() != DEAD ){
				partieFinie = false;
			}		
		}
	}
	/*
	if (countJoueurActif == 0){
		partieFinie = true;
	}
	*/
	
	if (partieFinie && tourChange){
		cout << "\tPartie Terminee !" << endl;
		currentState.setEndAction(partieFinie);
		//if (countJoueurActif == 0){							 A MODIFIER}
		if (activePlayer){
			cout << "\tL'armee bleue a gagne !" << endl;
		}
		else {
			cout << "\tL'armee rouge a gagne !" << endl;
		}
		tourChange = false;
	}
		
	else if (tourChange && !partieFinie){
		cout << "\t\t--- Tour Terminé. ---\n" << endl;
		currentState.setRound(currentState.getRound()+1);
	}

    changeTour = tourChange;
	
	return tourChange;

}

void Engine::verificationDebutDeTour(){
	if (changeTour == true){
	
		activePlayer = !activePlayer;
		cout << "\t-> Changement de joueur <-" << endl;
		cout << "\t\t--- Tour " << currentState.getRound() << " ---\n" << endl;
		
		for (unsigned int i = 0; i < currentState.getUnityArmys().size(); i++){
		
			// UnityArmys du joueur qui termine son tour et qui ne sont pas morts
			if (currentState.getUnityArmys()[i]->getCamp() != activePlayer && currentState.getUnityArmys()[i]->getStatus() != DEAD){
				// Reinitialisation du statut
				currentState.getUnityArmys()[i]->setStatus(AVAILABLE);
				
				//Reinitialisation des points de mouvement
				if (currentState.getUnityArmys()[i]->getType() != CAVLRY){
					currentState.getUnityArmys()[i]->setMove(3);
				}
				else {
					currentState.getUnityArmys()[i]->setMove(5);
				}	
			}
			
			// Regain de PV pour les UnityArmys sur des maisons et fortersse en debut de tour
			else if (currentState.getUnityArmys()[i]->getCamp() == activePlayer) {
				Praticable& refTerrainP = static_cast<Praticable&>(*currentState.getGrid()[currentState.getUnityArmys()[i]->getPosition().getY()][currentState.getUnityArmys()[i]->getPosition().getX()]);
				
				if(refTerrainP.getTypeId() == GRASS || refTerrainP.getTypeId() == GRASS){
					currentState.getUnityArmys()[i]->getStatistics().setPV(currentState.getUnityArmys()[i]->getStatistics().getPV() + refTerrainP.getStatistics().getPV());
					// Affichage
					cout << "+ " << currentState.getUnityArmys()[i]->getName() << " récupère " ;
					cout << refTerrainP.getStatistics().getPV() << " PV.";
					cout << " (" << currentState.getUnityArmys()[i]->getStatistics().getPV() << " PV au total). +" << endl;
				}
			}
		}
		
		changeTour = !changeTour;
	}
}

bool Engine::getActivePlayer()
{
    return activePlayer;
}

void Engine::managerCursor(sf::Event newEvent, sf::RenderWindow &window, unsigned int largeur_map_cases,
                           unsigned int longueur_map_cases)
{
    StateEvent stateEvent(ALLCHANGED);

    /*  CURSEUR  */

    // Appui d'une flèche directionnelle ou de Enter sans selection 
    // (moteur.getEtat().verifStatut()!=-1)
    if(newEvent.type==sf::Event::KeyPressed && (currentState.verifyStatus()==-1)){

        int changementX = 0, changementY = 0;
        size_t xCurs=currentState.getCursor()->getPosition().getX();
        size_t yCurs=currentState.getCursor()->getPosition().getY();
        int numeroPerso = currentState.getGrid()[xCurs][yCurs]->isOccupated(currentState);

        // Fleches directionnelles (deplacement du curseur)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(xCurs!=largeur_map_cases-1){changementX = 1;}
            else{changementX = -xCurs;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(xCurs!=0){changementX = -1;}
            else{changementX = largeur_map_cases-1 -xCurs;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(yCurs!=0){changementY = -1;}
            else{changementY = longueur_map_cases-1 -yCurs;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(yCurs!=longueur_map_cases-1){changementY = 1;}
            else{changementY = -yCurs;}
        }

            // Enter (selection)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            std::string newChaine;
            if(numeroPerso != -1){
                // Selection du personnage
                if(currentState.getUnityArmys()[numeroPerso]->getCamp() && currentState.getUnityArmys()[numeroPerso]->getStatus() != WAITING && currentState.getUnityArmys()[numeroPerso]->getStatus() != DEAD){

                    currentState.getCursor()->setCodeTuile(3);

                    newChaine = "Round start for " + currentState.getUnityArmys()[numeroPerso]->getName();
                    cout<< "\t\t->" << newChaine << " <-" << endl;

                    currentState.getUnityArmys()[numeroPerso]->setStatus(SELECTED);
                    stateEvent.eventId = PLAYERCHANGED;

                    auto unity = currentState.getUnityArmys()[numeroPerso].get();

                    char buffer[256];
                    sprintf(buffer, "\n:\t%d\n:\t%d\n:\t%d\n:\t%d\n:\t%d",
                            unity->getStatistics().getPV(),
                            unity->getStatistics().getAttack(),
                            unity->getStatistics().getDefense(),
                            unity->getStatistics().getDodge(),
                            unity->getStatistics().getCritical());

                    stateEvent.text = unity->getName();
                    stateEvent.infos = std::string(buffer);
                    currentState.notifyObservers(stateEvent, currentState, window);
                }
                else if (currentState.getUnityArmys()[numeroPerso]->getStatus() == WAITING){
                    newChaine = "Ce personnage a deja termine son tour";
                    cout << "\t\t" << newChaine << endl;
                }
                else{	newChaine = "Ce personnage appartient a l'adversaire !";
                    cout<< newChaine <<endl;}
            }

                // Affichage du type de terrain							
            else{	newChaine = "Ce terrain est de type " + currentState.getGrid()[yCurs][xCurs]->getName();
                cout << newChaine << endl;
            }
            stateEvent.text = newChaine;
            stateEvent.eventId = TEXTCHANGED;
            currentState.notifyObservers(stateEvent, currentState, window);
        }

        // Déplacement du curseur
        if (changementX != 0 || changementY !=0){
            Position nextPosCurs(xCurs+changementX, yCurs+changementY);
            currentState.getCursor()->move(nextPosCurs);
            currentState.notifyObservers(stateEvent, currentState, window);

            std::string newChaine;
            int resTest = currentState.getGrid()[nextPosCurs.getX()][nextPosCurs.getY()]->isOccupated(currentState);

            if (resTest != -1){newChaine = currentState.getUnityArmys()[resTest]->getName();}
            else{newChaine = currentState.getGrid()[nextPosCurs.getY()][nextPosCurs.getX()]->getName();}
            stateEvent.text = newChaine;
            stateEvent.eventId = TEXTCHANGED;
            currentState.notifyObservers(stateEvent, currentState, window);

            changementX = 0;
            changementY = 0;
        }
    }

        // Declenchement d'un attaque
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (currentState.verifyStatus()!=-1)){

        cout<< "\tAttaque en préparation" << endl;

        int attacker=currentState.verifyStatus();
        int champDroit=currentState.getUnityArmys()[attacker]->getAttack();
        int champGauche=champDroit;
        int champHaut=champDroit;
        int champBas=champDroit;
        int target=-1;

        // Changement de couleur du curseur
        currentState.getCursor()->setCodeTuile(1);
        currentState.notifyObservers(stateEvent, currentState, window);

        // Actions
        while((target==-1) || (target==attacker)){

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                size_t xCurs=currentState.getCursor()->getPosition().getX();
                size_t yCurs=currentState.getCursor()->getPosition().getY();

                if(xCurs!=largeur_map_cases-1 && champDroit!=0){
                    Position nextPosCurs(xCurs+1, yCurs);
                    currentState.getCursor()->move(nextPosCurs);
                    champDroit=champDroit-1;
                    champGauche++;
                    currentState.notifyObservers(stateEvent, currentState, window);
                    usleep(200000);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                size_t xCurs=currentState.getCursor()->getPosition().getX();
                size_t yCurs=currentState.getCursor()->getPosition().getY();

                if(xCurs!=0 && champGauche!=0){
                    Position nextPosCurs(xCurs-1, yCurs);
                    currentState.getCursor()->move(nextPosCurs);
                    champGauche=champGauche-1;
                    champDroit++;
                    currentState.notifyObservers(stateEvent, currentState, window);
                    usleep(200000);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                size_t xCurs=currentState.getCursor()->getPosition().getX();
                size_t yCurs=currentState.getCursor()->getPosition().getY();

                if(yCurs!=longueur_map_cases-1 && champBas!=0){
                    Position nextPosCurs(xCurs, yCurs+1);
                    currentState.getCursor()->move(nextPosCurs);
                    champBas=champBas-1;
                    champHaut++;
                    currentState.notifyObservers(stateEvent, currentState, window);
                    usleep(200000);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                size_t xCurs=currentState.getCursor()->getPosition().getX();
                size_t yCurs=currentState.getCursor()->getPosition().getY();
                if(yCurs!=0 && champHaut!=0){
                    Position nextPosCurs(xCurs, yCurs-1);
                    currentState.getCursor()->move(nextPosCurs);
                    champHaut=champHaut-1;
                    champBas++;
                    currentState.notifyObservers(stateEvent, currentState, window);
                    usleep(200000);
                }
            }

                // Annulation de l'attaque avec N
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
                target=-2;
                cout<< "\tAttaque annulée" << endl;
                currentState.getCursor()->setCodeTuile(3);
                currentState.notifyObservers(stateEvent, currentState, window);

                if(!currentState.getCursor()->getPosition().equals(currentState.getUnityArmys()[attacker]->getPosition())){
                    Position nextPosCurs(currentState.getUnityArmys()[attacker]->getPosition().getX(), currentState.getUnityArmys()[attacker]->getPosition().getY());
                    currentState.getCursor()->move(nextPosCurs);

                    currentState.notifyObservers(stateEvent, currentState, window);
                }
            }

                // Validation de l'attaque avec Enter
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                target=currentState.getGrid()[currentState.getCursor()->getPosition().getX()][currentState.getCursor()->getPosition().getY()]->isOccupated(currentState);
            }
        }

        // Validation de l'attaque
        if(target>=0){
            Attack attaque(*currentState.getUnityArmys()[attacker], *currentState.getUnityArmys()[target], currentState.getUnityArmys()[attacker]->getCamp());
            unique_ptr<Command> ptr_attaque (new Attack(attaque));
            addCommand(0, move(ptr_attaque));

            currentState.getCursor()->setCodeTuile(2);
            currentState.notifyObservers(stateEvent, currentState, window);
            update(window);
            currentState.getCursor()->setCodeTuile(0);
            currentState.notifyObservers(stateEvent, currentState, window);
        }
    }

        // Actions avec personnage selectionne (moteur.getEtat().verifStatut()!=-1)
    else if(newEvent.type==sf::Event::KeyPressed && (currentState.verifyStatus()!=-1)){

        int changementX = 0, changementY = 0;
        int numeroPerso=currentState.verifyStatus();
        size_t xPerso=currentState.getUnityArmys()[numeroPerso]->getPosition().getX();
        size_t yPerso=currentState.getUnityArmys()[numeroPerso]->getPosition().getY();

        // Fleches directionnelles (deplacement du curseur et du personnage)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(xPerso!=largeur_map_cases-1){changementX = 1;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(xPerso!=0){changementX = -1;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(yPerso!=0){changementY = -1;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(yPerso!=longueur_map_cases-1){changementY = 1;}
        }

            // Touche Z : Fin de tour d'actions
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            EndAction finaction(*currentState.getUnityArmys()[numeroPerso], currentState.getUnityArmys()[numeroPerso]->getCamp());
            unique_ptr<Command> ptr_finaction (new EndAction(finaction));
            addCommand(0, move(ptr_finaction));
            currentState.getCursor()->setCodeTuile(0);
            update(window);
        }

        // Deplacement du curseur et du personnage selectionne
        if (changementX != 0 || changementY != 0){
            Position nextPos(xPerso+changementX, yPerso+changementY);
            Movement deplacement(*currentState.getUnityArmys()[numeroPerso], nextPos, activePlayer);
            unique_ptr<Command> ptr_deplacement (new Movement(deplacement));
            addCommand(0, move(ptr_deplacement));

            currentState.getCursor()->move(nextPos);
            update(window);

            changementX = 0;
            changementY = 0;
        }
    }
}

void Engine::updateAction (sf::RenderWindow& window, Action* action){
    StateEvent stateEvent(ALLCHANGED);

    action->apply(currentState);
    currentState.notifyObservers(stateEvent, currentState, window);

}

void Engine::undo (sf::RenderWindow& window, Action* action){
    StateEvent stateEvent(ALLCHANGED);

    action->undo(currentState);
    currentState.notifyObservers(stateEvent, currentState, window);
}

void Engine::manageCursorRollback(sf::Event newEvent, sf::RenderWindow& window, unsigned int largeur_map_cases, unsigned int longueur_map_cases){

    StateEvent stateEvent(ALLCHANGED);

    /*  CURSEUR  */

    // ROLLBACK
    //
    //
    if (newEvent.type==sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        cout << "ROLLBACK ! : " << listTimePlayedActions.size() << " actions a annuler" << endl;
        if (listTimePlayedActions.size()>0){
            for(int i = listTimePlayedActions.size()-1; i >= 0; i--){
                undo(window, move(listTimePlayedActions[i]));

                cout << "Annulation " << i << " effectuee" << endl;
                usleep(750000);
                listTimePlayedActions.pop_back();
            }
        }

        // Test pour changement de couleur du curseur si le rollback est declenché alors qu'un personnage est selectionne et n'a effectue aucune action
        bool persoSelectionne = false;
        for (size_t i = 0; i<currentState.getUnityArmys().size(); i++){
            if (currentState.getUnityArmys()[i]->getStatus() == state::SELECTED){
                persoSelectionne = true;
                break;
            }
        }
        if(!persoSelectionne){
            currentState.getCursor()->setCodeTuile(0);
        }
        currentState.notifyObservers(stateEvent, currentState, window);
        cout << "FIN DU ROLLBACK" << endl;
    }

        // Appui d'une flèche directionnelle ou de Enter sans selection
        // (moteur.getEtat().verifStatut()!=-1)
    else if(newEvent.type==sf::Event::KeyPressed && (currentState.verifyStatus()==-1)){

        int changementX = 0, changementY = 0;
        size_t xCurs=currentState.getCursor()->getPosition().getX();
        size_t yCurs=currentState.getCursor()->getPosition().getY();
        int numeroPerso = currentState.getGrid()[xCurs][yCurs]->isOccupated(currentState);


        // Fleches directionnelles (deplacement du curseur)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(xCurs!=largeur_map_cases-1){changementX = 1;}
            else{changementX = -xCurs;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(xCurs!=0){changementX = -1;}
            else{changementX = largeur_map_cases-1 -xCurs;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(yCurs!=0){changementY = -1;}
            else{changementY = longueur_map_cases-1 -yCurs;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(yCurs!=longueur_map_cases-1){changementY = 1;}
            else{changementY = -yCurs;}
        }

            // Enter (selection)
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            std::string newChaine;
            if(numeroPerso != -1){
                // Selection du personnage
                if(currentState.getUnityArmys()[numeroPerso]->getCamp() && currentState.getUnityArmys()[numeroPerso]->getStatus() != WAITING && currentState.getUnityArmys()[numeroPerso]->getStatus() != DEAD){

                    currentState.getCursor()->setCodeTuile(3);

                    newChaine = "Debut du tour de " + currentState.getUnityArmys()[numeroPerso]->getName();
                    cout<< "\t\t->" << newChaine << " <-" << endl;

                    currentState.getUnityArmys()[numeroPerso]->setStatus(SELECTED);
                    currentState.notifyObservers(stateEvent, currentState, window);
                }
                else if (currentState.getUnityArmys()[numeroPerso]->getStatus() == WAITING){
                    newChaine = "Ce personnage a deja termine son tour";
                    cout << "\t\t" << newChaine << endl;
                }
                else{	newChaine = "Ce personnage appartient a l'adversaire !";
                    cout<< newChaine <<endl;}
            }

                // Affichage du type de terrain
            else{	newChaine = "Ce terrain est de type " + currentState.getGrid()[yCurs][xCurs]->getName();
                cout << newChaine << endl;
            }
            stateEvent.text = newChaine;
            stateEvent.eventId = TEXTCHANGED;
            currentState.notifyObservers(stateEvent, currentState, window);
        }

        // Déplacement du curseur
        if (changementX != 0 || changementY !=0){
            Position nextPosCurs(xCurs+changementX, yCurs+changementY);
            currentState.getCursor()->move(nextPosCurs);
            currentState.notifyObservers(stateEvent, currentState, window);

            std::string newChaine;
            int resTest = currentState.getGrid()[nextPosCurs.getX()][nextPosCurs.getY()]->isOccupated(currentState);

            if (resTest != -1){newChaine = currentState.getUnityArmys()[resTest]->getName();}
            else{newChaine = currentState.getGrid()[nextPosCurs.getX()][nextPosCurs.getY()]->getName();}
            stateEvent.text = newChaine;
            stateEvent.eventId = TEXTCHANGED;
            currentState.notifyObservers(stateEvent, currentState, window);

            changementX = 0;
            changementY = 0;
        }
    }

        // Declenchement d'un attaque
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (currentState.verifyStatus()!=-1)){

        cout<< "\tAttaque en préparation" << endl;

        int attacker=currentState.verifyStatus();
        int champDroit=currentState.getUnityArmys()[attacker]->getAttack();
        int champGauche=champDroit;
        int champHaut=champDroit;
        int champBas=champDroit;
        int target=-1;

        // Changement de couleur du curseur
        currentState.getCursor()->setCodeTuile(1);
        currentState.notifyObservers(stateEvent, currentState, window);

        // Actions
        while((target==-1) || (target==attacker)){

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                size_t xCurs=currentState.getCursor()->getPosition().getX();
                size_t yCurs=currentState.getCursor()->getPosition().getY();

                if(xCurs!=largeur_map_cases-1 && champDroit!=0){
                    Position nextPosCurs(xCurs+1, yCurs);
                    currentState.getCursor()->move(nextPosCurs);
                    champDroit=champDroit-1;
                    champGauche++;
                    currentState.notifyObservers(stateEvent, currentState, window);
                    usleep(200000);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                size_t xCurs=currentState.getCursor()->getPosition().getX();
                size_t yCurs=currentState.getCursor()->getPosition().getY();

                if(xCurs!=0 && champGauche!=0){
                    Position nextPosCurs(xCurs-1, yCurs);
                    currentState.getCursor()->move(nextPosCurs);
                    champGauche=champGauche-1;
                    champDroit++;
                    currentState.notifyObservers(stateEvent, currentState, window);
                    usleep(200000);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                size_t xCurs=currentState.getCursor()->getPosition().getX();
                size_t yCurs=currentState.getCursor()->getPosition().getY();

                if(yCurs!=longueur_map_cases-1 && champBas!=0){
                    Position nextPosCurs(xCurs, yCurs+1);
                    currentState.getCursor()->move(nextPosCurs);
                    champBas=champBas-1;
                    champHaut++;
                    currentState.notifyObservers(stateEvent, currentState, window);
                    usleep(200000);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                size_t xCurs=currentState.getCursor()->getPosition().getX();
                size_t yCurs=currentState.getCursor()->getPosition().getY();
                if(yCurs!=0 && champHaut!=0){
                    Position nextPosCurs(xCurs, yCurs-1);
                    currentState.getCursor()->move(nextPosCurs);
                    champHaut=champHaut-1;
                    champBas++;
                    currentState.notifyObservers(stateEvent, currentState, window);
                    usleep(200000);
                }
            }

                // Annulation de l'attaque avec N
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
                target=-2;
                cout<< "\tAttaque annulée" << endl;
                currentState.getCursor()->setCodeTuile(3);
                currentState.notifyObservers(stateEvent, currentState, window);

                if(!currentState.getCursor()->getPosition().equals(currentState.getUnityArmys()[attacker]->getPosition())){
                    Position nextPosCurs(currentState.getUnityArmys()[attacker]->getPosition().getX(), currentState.getUnityArmys()[attacker]->getPosition().getY());
                    currentState.getCursor()->move(nextPosCurs);

                    currentState.notifyObservers(stateEvent, currentState, window);
                }
            }

                // Validation de l'attaque avec Enter
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                target=currentState.getGrid()[currentState.getCursor()->getPosition().getX()][currentState.getCursor()->getPosition().getY()]->isOccupated(currentState);
            }
        }

        // Validation de l'attaque
        if(target>=0){
            AttackAction attack(*currentState.getUnityArmys()[attacker], *currentState.getUnityArmys()[target], currentState.getUnityArmys()[attacker]->getCamp());
            AttackAction* ptr_attack (new AttackAction(attack));
            listTimePlayedActions.push_back(move(ptr_attack));
            updateAction(window, move(ptr_attack));

            currentState.getCursor()->setCodeTuile(2);
            currentState.notifyObservers(stateEvent, currentState, window);
            update(window);
            currentState.getCursor()->setCodeTuile(0);
            currentState.notifyObservers(stateEvent, currentState, window);
        }
    }

        // Actions avec personnage selectionne (moteur.getEtat().verifStatut()!=-1)
    else if(newEvent.type==sf::Event::KeyPressed && (currentState.verifyStatus()!=-1)){

        int changementX = 0, changementY = 0;
        int numeroPerso=currentState.verifyStatus();
        size_t xPerso=currentState.getUnityArmys()[numeroPerso]->getPosition().getX();
        size_t yPerso=currentState.getUnityArmys()[numeroPerso]->getPosition().getY();

        // Fleches directionnelles (deplacement du curseur et du personnage)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(xPerso!=largeur_map_cases-1){changementX = 1;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(xPerso!=0){changementX = -1;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(yPerso!=0){changementY = -1;}
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(yPerso!=longueur_map_cases-1){changementY = 1;}
        }

            // Touche Z : Fin de tour d'actions
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){

            FinAction finaction(*currentState.getUnityArmys()[numeroPerso], currentState.getUnityArmys()[numeroPerso]->getCamp());
            FinAction* ptr_finaction(new FinAction(finaction));
            listTimePlayedActions.push_back(move(ptr_finaction));

            updateAction(window, move(ptr_finaction));
            currentState.getCursor()->setCodeTuile(0);
            update(window);
        }

        // Deplacement du curseur et du personnage selectionne
        if (changementX != 0 || changementY != 0){
            Position nextPos(xPerso+changementX, yPerso+changementY);
            DepAction deplacement(*currentState.getUnityArmys()[numeroPerso], nextPos, activePlayer);
            DepAction* ptr_deplacement (new DepAction(deplacement));
            listTimePlayedActions.push_back(move(ptr_deplacement));


            currentState.getCursor()->move(nextPos);
            updateAction(window, move(ptr_deplacement));
            update(window);

            changementX = 0;
            changementY = 0;
        }
    }
}

void Engine::addAction(Action* newAction){
    listTimePlayedActions.push_back(move(newAction));
}
